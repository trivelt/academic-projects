#!/usr/bin/perl
# Maciej Michalec, grupa 2
use Time::Piece;
use File::Basename;
use lib dirname(__FILE__);
use DateParser qw/parse_date/;

$debug = 0;
$verbose = $debug;
$useHoursAsDefault = 1;
$startDate = 0;
$endDate = 0;
@files = ();

foreach my $arg (@ARGV)
{
    if($arg eq "-m" or $arg eq "--minutes")
    {
        print "[DEBUG] Ustawiono minuty jako domyslna jednostke\n" if($debug);
        $useHoursAsDefault=0;
    }
    elsif ($arg =~ "^-s=" or $arg =~ "^--start=")
    {
        $startDate = DateParser::parse_date($arg, "poczatkowa");
        print "[DEBUG] Ustawiono poczatkowa date=$startDate\n" if($debug);
    }
    elsif ($arg =~ "^-e=" or $arg =~ "^--end=")
    {
        $endDate = DateParser::parse_date($arg, "koncowa");
        print "[DEBUG] Ustawiono koncowa date=$endDate\n" if($debug)
    }
    elsif ($arg eq "-h" or $arg eq "--help")
    {
        print "Skladnia: ./projektZaliczeniowy.pl [OPCJE] PLIK_1 [OPCJE] [PLIK_2] ... [OPCJE]\n\
Program pozwalajacy na sumowanie czasu spedzanego przy okreslonych czynnosciach. Przetwarza pliki, ktore zawieraja liste dat oraz powiazanych z nimi liczb oznaczajacych czas. Program umozliwia sumowanie calosci pliku lub tylko dat znajdujacych sie w wybranym przez uzytkownika przedziale czasowym. 

1. OPCJE
  -h, --help\t\t\tNiniejsza pomoc
  -s=[DATA], --start=[DATA]\tData poczatkowa okresu sumowania. Format: yyyy-mm-dd (rok-miesiac-dzien) 
  -e=[DATA], --end=[DATA]\tData koncowa okresu sumowania. Format taki jak przy dacie poczatkowej
  -m, --minutes\t\t\tJesli podana te flage, to czas bez podanych jednostek traktowany jest jako wyrazony w minutach. W przeciwnym razie, domyslna jednostka sa godziny 
  -v, --verbose\t\t\tTryb gadatliwy, informuje o znalezionych blednych liniach w przetwarzanych plikach

2. STRUKTURA PLIKU
Linie zaczynajace sie od znaku "  . '#' . " oznaczaja komentarz i nie sa brane pod uwage przy parsowaniu pliku. Linia rozpoczynajaca sie od znaku ! jest wyswietlanym przy podsumowaniu opisem zawartosci pliku (np. czynnosci, na ktora poswiecony czas jest sumowany). Jesli w pliku pojawia sie kilka linii z takim opisem, to program wyswietla jedynie ostatnia. Wszystkie inne poprawne linie powinny zaczynac sie od daty wyrazonej w formacie yyyy-mm-dd (rok-miesiac-dzien), a nastepnie czasu, oddzielonego od daty spacja. Pozniej, po kolejnej spacji, moga pojawiac sie dowolne ciagi znakow, ktorych program i tak nie interpretuje. Przyklad pliku:

# Komentarz, nie brany pod uwage
!czytanie plikow pomocy
2015-03-14 1.5h
2015-02-09 20m 
bledna linia
2016-04-30 2:30h dalszy tekst
2016-05-02 5
2016-05-04 2,5

jak widac na powyzszym przykladzie, czas moze byc wyrazony na rozne sposoby: jako godziny lub minuty z czescia dziesietna albo jako godziny oddzielone od minut dwukropkiem (lub minuty od sekund). Opis czasu moze zawierac jednostke ('h' jako godzina, 'm' jako minuta), ktora jest bezwzglednie interpretowana przez program w zadany sposob lub moze nie zawierac jednostki. Program wykorzystuje wtedy jednostke domyslna, ktora sa godziny, lub minuty gdy uzytkownik uruchomil go z opcja -m.\n";
        exit 0;
    }
    elsif ($arg eq "-v" or $arg eq "--verbose")
    {
        print "[DEBUG] Wlaczono tryb VERBOSE\n" if($debug);
        $verbose = 1;
    }
    else
    {
        if(! -e $arg)
        {
            print "Ostrzezenie: plik $arg nie istnieje\n";
            next;
        }
        print "[DEBUG] Dodano plik $arg do listy\n" if($debug);
        @files = (@files, $arg);
    }
}

if($startDate != 0 and $endDate != 0 and $startDate > $endDate)
{
    print "Blad: Data poczatkowa jest wieksza od daty koncowej\n";
    exit 1;
}

$numberOfFiles=@files;
if ($numberOfFiles == 0)
{
    print "Nie podano zadnego istniejacego pliku. Sprawdz pomoc, wywolujac program z opcja -h lub --help\n";
    exit 1;
}

foreach my $file(@files)
{
    print "=== $file ===\n";
    $typeOfActivity = "";
    my $totalTime = 0;
    open(FILE, $file) || cannot_read($file);
    @text = <FILE>;
    foreach my $line(@text)
    {
        if($line =~ "^#")
        {
            next;
        }
        elsif($line =~ "^!")
        {
            chomp($typeOfActivity = substr $line, 1);
            next;
        }
        @splittedLine = split(" ", $line);
        $numberOfElements = @splittedLine;
        if($numberOfElements < 2)
        {
            print "Bledna linia: $line" if($verbose);
            next;
        }
        $dateString = ${splittedLine[0]};
        $spentTime = ${splittedLine[1]};
        my $dateObject = eval {
            Time::Piece->strptime($dateString, "%Y-%m-%d")
            };
        if(! $dateObject)
        {
            print "Bledna data w linii: $line" if($verbose);
            next;
        } 
        if($startDate != 0 and $dateObject < $startDate)
        {
            print "[DEBUG] Pomijam linie z data $dateString jako starsza niz data poczatkowa\n" if($debug);
            next;
        }
        if($endDate != 0 and $dateObject > $endDate)
        {
            print "[DEBUG] Pomijam linie z data $dateString jako starsza niz data koncowa\n" if($debug);
            next;
        }

        if($spentTime =~ /^\d+[.,]?\d*[hm]?$/)
        {
            print "Parsowanie czasu $spentTime z czescia dziesietna" if($debug);
            $spentTime =~ s/,/./;
            if($spentTime =~ "m" or ($useHoursAsDefault == 0 and $spentTime !~ "h"))
            {
                print " - minuty" if($debug);
                $spentTime = substr($spentTime, 0, -1) if($spentTime =~ "m");
                $totalTime += $spentTime;
            }
            else
            {
                print " - godziny" if($debug);
                $spentTime = substr($spentTime, 0, -1) if($spentTime =~ "h");
                $spentTime *= 60;
                $totalTime += $spentTime;
            }
        }
        elsif($spentTime =~ /^\d+:\d+[hm]?$/)
        {
            print "Parsowanie czasu $spentTime z dwukropkiem" if($debug);
            if($spentTime =~ "m" or ($useHoursAsDefault == 0 and $spentTime !~ "h"))
            {
                print " - minuty" if($debug);
                $spentTime = substr($spentTime, 0, -1) if($spentTime =~ "m");
                @parts = split(":", $spentTime);
                $minutes = ${parts[0]};
                $seconds = ${parts[1]};
                $minutes += $seconds / 60.0;
                $totalTime += $minutes;
            }
            else
            {
                print " - godziny" if($debug);
                $spentTime = substr($spentTime, 0, -1) if($spentTime =~ "h");
                @parts = split(":", $spentTime);
                $hours = ${parts[0]};
                $minutes = ${parts[1]};
                $minutes += $hours * 60;
                $totalTime += $minutes;
            }
        }
        else
        {
            print "Bledny czas w linii: $line" if($verbose);
            next;
        }
        print " (total: $totalTime)\n" if($debug);
    }

    if($typeOfActivity ne "")
    {
        print "Rodzaj aktywnosci: $typeOfActivity\n";
    }
    $hours = int($totalTime / 60);
    $minutes = $totalTime - 60*$hours;
    $minutes = sprintf("%.2f", $minutes);
    print "Spedzony czas: $hours godzin $minutes minut\n\n";
}

sub cannot_read {
    print "Cannot read file " . @_[0] . "\n" if($debug);
}
