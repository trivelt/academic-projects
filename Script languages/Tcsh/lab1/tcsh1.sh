#!/bin/tcsh
# Maciej Michalec, grupa 2

set help = "\n== Pierwszy skrypt tcsh z zajec PJS ==\n\
Skrypt wyswietla login uzytkownika oraz jego imie i nazwisko \n\
jezeli jest w stanie dotrzec do tej informacji. \n\
\n\
Opcje:\n\
  -h: wyswietlenie TEJ pomocy\n\
  -q: natychmiastowe zakonczenie pracy skryptu\n"



set help_flag = 0
set quit_flag = 0
set invalid_arg = 0

foreach arg ( $* )
    switch ( "$arg" )
    case "-h":
        set help_flag = 1
        breaksw
    case "-q":
        set quit_flag = 1
        breaksw
    default:
        set invalid_arg = 1
    endsw
end

if ( "$help_flag" == 1 ) then
    echo $help
    exit 0
else if ( "$invalid_arg" == 1 ) then
    echo Invalid parameter
    echo $help
    exit 1
else if ( "$quit_flag" == 1 ) then
    exit 0
endif

echo "Login:" $USER

if ( "`which getent`" != "" ) then
    set user_record = (`getent passwd $USER`)
    set user_gecos_field = (`echo "$user_record" | cut -d ':' -f 5`)
    set user_full_name = (`echo "$user_gecos_field" | cut -d ',' -f 1`)
    echo "Name: " $user_full_name
endif
