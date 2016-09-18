#!/bin/bash
# Maciej Michalec, grupa 2

function print_help()
{
cat << EOL

== Pierwszy skrypt bash z zajec PJS == 
Skrypt wyswietla login uzytkownika oraz jego imie i nazwisko 
jezeli jest w stanie dotrzec do tej informacji. 

Opcje: 
 * -h: wyswietlenie TEJ pomocy
 * -q: natychmiastowe zakonczenie pracy skryptu

EOL
}

help_flag=0
quit_flag=0
invalid_arg=0
while getopts ":hq" opt; do
    case "$opt" in
    h)  help_flag=1
        ;;
    q)  quit_flag=1
        ;;
    \?) invalid_arg=1
        ;;
    esac
done

if [ $help_flag -eq 1 ] ; then
    print_help
    exit 0
elif [ $invalid_arg -eq 1 ] ; then
    echo Invalid parameter
    print_help
    exit 1
elif [ $quit_flag -eq 1 ] ; then
    exit 0
fi

echo "Login:" $USER

if [ "`which getent`" != "" ] ; then
    user_record=$(getent passwd $USER)
    user_gecos_field=$(echo "$user_record" | cut -d ':' -f 5)
    user_full_name=$(echo "$user_gecos_field" | cut -d ',' -f 1)
    echo "Name: " $user_full_name
fi
