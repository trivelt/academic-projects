#!/bin/bash
# Maciej Michalec, grupa 2
source $(dirname $0)/ArrayHelper.sh

function print_help()
{
cat << EOL
Skladnia: ./projektZaliczeniowy.sh [OPCJE] kod1-kod2 (--file=PLIK | TEKST) 
Skrypt, korzystajac z Yandex Translate API, tlumaczy tekst pomiedzy wybranymi jezykami.

1. OPCJE
 * --help        wyswietlenie TEJ pomocy
 * --languages   wyswietlenie listy dostepnych przy tlumaczeniu jezykow wraz z odpowiadajacymi im kodami
 * --file=PLIK   pobiera tekst do tlumaczenia ze wskazanego pliku. Ta opcja moze pojawic sie jedynie 
                 na samym koncu, poprzedzona kodami jezykow. 

2. UZYCIE
Chcac dokonac tlumaczenia pomiedzy wybranym jezykami, nalezy najpierw sprawdzic ich kody, korzystajac z opcji
--languages. Nastepnie nalezy wywolac program w sposob jak na ponizszym przykladzie:

./projektZaliczeniowy.sh pl-en "Witaj, swiecie"

powyzsze wywolanie przetlumaczy tekst "Witaj, swiecie" z jezyka polskiego na angielski.
Jezeli tekst znajduje sie w pliku o nazwie FILE.TXT, to skrypt nalezy wywolac tak:

./projektZaliczeniowy.sh pl-en --file=FILE.txt

W przypadku problemow z translacja, program wypisze na ekran komunikat z trescia 
odpowiedniego kodu bledu. 

EOL
}


CURL_INSTALLED=0
WGET_INSTALLED=0
XMLLINT_INSTALLED=0
if which curl >/dev/null; then
    CURL_INSTALLED=1
fi
if which wget >/dev/null; then
    WGET_INSTALLED=1
fi
if [ $CURL_INSTALLED -eq 0 ] && [ $WGET_INSTALLED -eq 0 ]; then
    echo "Blad: brak odpowiednich bibliotek w systemie. Zainstaluj program 'curl' lub 'wget'"
    exit 1
fi
if which xmllint >/dev/null; then
    XMLLINT_INSTALLED=1
fi
if [ $XMLLINT_INSTALLED -eq 0 ]; then
    echo "Blad: brak odpowiednich bibliotek w systemie. Zainstaluj program 'xmllint'"
    exit 1
fi

KEY="trnsl.1.1.20160222T215739Z.9a88db99ac938902.58b5c247a946caa3b4a36a7ea22f65b1f2ebeba2"
TRANSLATE_QUERY="https://translate.yandex.net/api/v1.5/tr/translate?key="$KEY"&text="
LANGUAGES_QUERY="https://translate.yandex.net/api/v1.5/tr/getLangs?key="$KEY"&ui=pl"
CODES=()
PATTERN="^[a-z]{2}-[a-z]{2}$"
EXPECTED_TEXT=0
TEXT_SET=0
TEXT=0
LANG_1=""
LANG_2=""
PAT="^-f=.+"

if [ $WGET_INSTALLED -eq 1 ]; then
    LANGS=`wget -q -O - "$LANGUAGES_QUERY"`
else
    LANGS=`curl -s "$LANGUAGES_QUERY"`
fi
if [ "$LANGS" = "" ]; then
    echo "Blad: problem przy polaczeniu z serwerem"
    exit 1
fi
all_codes=`xmllint --xpath '//Langs/langs/Item/@key' - <<<"$LANGS"`
IFS=' ' read -ra lang_codes <<< "${all_codes[$i]}"        
for code in "${lang_codes[@]}"; do
    code=${code:5:2}
    CODES+=($code)
done

for arg in "$@"; do
    if [ "$arg" = "--languages" ]; then
        echo "Lista jezykow:"
        for code in "${CODES[@]}"; do
            lang_name=`xmllint --xpath 'string(/Langs/langs/Item[@key="'$code'"]/@value)' - <<<"$LANGS"`
            echo "$code - $lang_name"
        done
        exit 0

    elif [ "$arg" = "--help" ]; then
        print_help
        exit 0
    elif [[ "$arg" =~ $PATTERN ]]; then
        IFS='-' read -ra langs <<< "${arg}"        
        LANG_1=${langs[0]} 
        LANG_2=${langs[1]}
        containsElement $LANG_1 "${CODES[@]}"
        if [ $? -ne 0 ]; then
            echo "Blad: nieprawidlowy kod jezyka: $LANG_1. Uzyj parametru --languages, aby wyswietlic dostepne jezyki."
            exit 1
        fi
        containsElement $LANG_2 "${CODES[@]}"
        if [ $? -ne 0 ]; then
            echo "Blad: nieprawidlowy kod jezyka: $LANG_2. Uzyj parametru --languages, aby wyswietlic dostepne jezyki."
            exit 1
        fi
        EXPECTED_TEXT=1
    elif [ $EXPECTED_TEXT -eq 1 ]; then
        if [[ "$arg" == --file=* ]]; then
            filename=${arg:7}
            if [ ! -f $filename ];then
                echo "Plik nie istnieje"
                exit 1
            fi           
            TEXT=`cat $filename`
        else
            TEXT="$arg"
        fi
        TEXT_SET=1
        break
    else
        echo "Blad: nieprawidlowa skladnia. Uzyj parametru --help, aby uzyskac pomoc."
        exit 1
    fi
done

if [ $TEXT_SET -eq 0 ]; then
    echo "Blad: nieprawidlowa skladnia. Uzyj parametru --help, aby uzyskac pomoc."
    exit 1
fi

FULL_TRANSLATION_QUERY="$TRANSLATE_QUERY""$TEXT""&lang=$LANG_1-$LANG_2&format=plain"
if [ $WGET_INSTALLED -eq 1 ]; then
    TRANSLATION=`wget -q -O - "$FULL_TRANSLATION_QUERY"`
else
    TRANSLATION=`curl -s "$FULL_TRANSLATION_QUERY"`
fi
STATUS_CODE=`xmllint --xpath 'string(//Translation/@code)' - <<<"$TRANSLATION"`
if [ $STATUS_CODE -ne 200 ]; then
    echo -n "Blad przy wykonywaniu zapytania. Kod bledu: $STATUS_CODE ("
    if [ $STATUS_CODE -eq 401 ]; then
        echo "Invalid API key)"
    elif [ $STATUS_CODE -eq 402 ]; then
        echo "Blocked API key)"
    elif [ $STATUS_CODE -eq 403 ]; then
        echo "Exceeded the daily limit on the number of requests)"
    elif [ $STATUS_CODE -eq 404 ]; then
        echo "Exceeded the daily limit on the amount of translated text)"
    fi
fi
TRANSLATED_TEXT=`xmllint --xpath 'string(//Translation/text)' - <<<"$TRANSLATION"`
echo "$TRANSLATED_TEXT"

exit 0
