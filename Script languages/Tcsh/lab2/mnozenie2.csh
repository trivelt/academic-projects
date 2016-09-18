#!/bin/tcsh
# Maciej Michalec, grupa 2

if ( $# < 2 ) then
    echo Za malo argumentow. Podaj co najmniej dwie liczby
    exit 1
endif

foreach arg ( $1 $2 )
    echo $arg | grep -q -E '^[0-9]+$'
    if ( $? != 0) then
        echo Pierwsze dwa parametry musza byc liczbami
        exit 1
    endif
end

if ( $1 > $2 ) then
    foreach i (`seq $1 -1 $2`)
        foreach j (`seq $1 -1 $2`)
            @ result = $i * $j
            echo -n $result
            echo -n "\t"
        end
        echo ""
    end
else
    foreach i (`seq $1 $2`)
        foreach j (`seq $1 $2`)
            @ result = $i * $j
            echo -n $result
            echo -n "\t"
        end
        echo ""
    end
endif

exit 0
