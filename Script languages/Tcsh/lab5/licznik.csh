#!/bin/tcsh
# Maciej Michalec, grupa 2

set PORT=7777
set IP="localhost"
set SERVER_MODE=0
set CLIENT_MODE=0
set CONFIG_FILE="${HOME}/.licznik.rc"
set CONFIG_DIR="${HOME}/.liczniki"
set IP_OPTION=0
set PORT_OPTION=0

foreach arg ( $* )
    if ( "$arg" == "-i") then
        set IP=$2
        set IP_OPTION=1 
        if ( $# < 2 ) then
            echo Bledne argumenty
            exit 1
        endif
        shift
        shift
    else if ("$arg" == "-p") then
        set PORT=$2
        set PORT_OPTION=1
        if ( $# < 2 ) then
            echo Bledne argumenty
            exit 1
        endif
        shift
        shift
    else if ("$arg" == "-s") then
        set SERVER_MODE=1
        shift
    else if ("$arg" == "-c") then
        set CLIENT_MODE=1
        shift
    endif
end

if ( $SERVER_MODE == 1 && $CLIENT_MODE == 1 ) then
    echo Opcje sa sprzeczne. Odmawiam, koniec dzialania
    exit 1
endif

if ( $SERVER_MODE == 0 && $CLIENT_MODE == 0 ) then
    set SERVER_MODE=1 
endif

ls $CONFIG_FILE >& /dev/null
if ( $? == 0) then 
    foreach line ("`cat $CONFIG_FILE`")
        if ( "$line" =~ "PORT*" ) then
            if ( $PORT_OPTION == 0 ) then
                set lineList = ($line)
                set portFromFile = $lineList[2]
                set PORT=$portFromFile
            endif
        else if ( "$line" =~ "IP*" ) then
            if ( $IP_OPTION == 0 ) then
                set lineList = ($line)
                set ipFromFile = $lineList[2]
                set IP=$ipFromFile
                set IP_OPTION=1
            endif
        endif
    end
endif


if ( $SERVER_MODE == 1 ) then
    ls $CONFIG_DIR >& /dev/null
    if ( $? != 0 ) then
        mkdir -p $CONFIG_DIR
    endif

   ls $CONFIG_DIR/$PORT >& /dev/null
   if ( $? != 0) then 
        echo 0 > $CONFIG_DIR/$PORT
    endif

    echo "Nasluchiwanie na $IP : $PORT"
    while ( 1 )
        if ( $IP_OPTION == 0 ) then
            nc -l $PORT < $CONFIG_DIR/$PORT > /dev/null
            set result=$?
        else
            nc -l $IP $PORT < $CONFIG_DIR/$PORT > /dev/null 
            set result=$?
        endif

        if ( $result != 0 ) then
            echo "Nie mozna uruchomic serwera na $IP : $PORT"
            exit 1
        endif
        
    end

else if ( $CLIENT_MODE == 1 ) then
    echo "Laczenie z adresem $IP : $PORT"
    echo "PING" | nc -q 1 $IP $PORT   
    if ( $? == 1 ) then
        echo "Blad przy probie polaczenia z adresem $IP : $PORT"
        exit 1
    endif
endif

exit 0
