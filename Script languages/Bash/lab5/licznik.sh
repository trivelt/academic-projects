#!/bin/bash
# Maciej Michalec, grupa 2

PORT=7777
IP="localhost"
SERVER_MODE=0
CLIENT_MODE=0
CONFIG_FILE="${HOME}/.licznik.rc"
CONFIG_DIR="${HOME}/.liczniki"

safe_exit()
{
    exit 0
}
 
trap safe_exit SIGINT

while getopts ":i:p:f:cs" opt; do
    case "${opt}" in
        i)
            IP_OPTION=1
            IP=${OPTARG}
            ;;
        p)
            PORT_OPTION=1
            PORT=${OPTARG}
            ;;
        f)
            CONFIG_FILE=${OPTARG}
            ;;
        c)
            CLIENT_MODE=1
            ;;
        s)
            SERVER_MODE=1
            ;;
        *)
            echo 'Wrong parameters' 
            exit 1
            ;;
    esac
done

if [ $SERVER_MODE = 1 ] && [ $CLIENT_MODE = 1 ]; then
    echo Opcje sa sprzeczne. Odmawiam, koniec dzialania
    exit 1
fi

if [ $SERVER_MODE = 0 ] && [ $CLIENT_MODE = 0 ]; then
    SERVER_MODE=1
fi


if [ -f $CONFIG_FILE ]; then
    while read line; do    
        case "$line" in
            PORT*)
                if [ -z ${PORT_OPTION+x} ]; then
                    lineList=($line)
                    PORT=${lineList[1]}
                    PORT_OPTION=1
                fi
                ;;
            IP*)
                if [ -z ${IP_OPTION+x} ]; then
                    lineList=($line)
                    IP=${lineList[1]}
                    IP_OPTION=1
                fi
                ;;
        esac
    done < $CONFIG_FILE
else
    echo Ostrzezenie: Plik konfiguracyjny $CONFIG_FILE nie istnieje
fi

if [ $SERVER_MODE = 1 ]; then
   if ! [ -d $CONFIG_DIR ]; then
        mkdir -p $CONFIG_DIR
    fi

   if ! [ -f $CONFIG_DIR/$PORT ]; then 
        echo 0 > $CONFIG_DIR/$PORT
    fi

    echo "Nasluchiwanie na $IP:$PORT"
    while true; do
        if [ -z ${IP_OPTION+x} ]; then
            nc -l $PORT < $CONFIG_DIR/$PORT
            result=$?
        else
            nc -l $IP $PORT < $CONFIG_DIR/$PORT 1>/dev/null 2>/dev/null
            result=$?
        fi

        if [ $result -eq 1 ]; then
            echo "Nie mozna uruchomic serwera na $IP:$PORT"
            exit 1
        fi

        CURRENT_COUNTER_VALUE=`cat $CONFIG_DIR/$PORT`
        echo  "Wysylam odpowiedz=$CURRENT_COUNTER_VALUE"
        CURRENT_COUNTER_VALUE=$((CURRENT_COUNTER_VALUE + 1))
        echo $CURRENT_COUNTER_VALUE > $CONFIG_DIR/$PORT
   done

elif [ $CLIENT_MODE = 1 ]; then
    echo "Laczenie z adresem $IP:$PORT"
    echo "PING" | nc -q 1 $IP $PORT
    if [ $? -eq 1 ]; then
        echo "Blad przy probie polaczenia z adresem $IP:$PORT"
        exit 1
    fi
fi

exit 0

