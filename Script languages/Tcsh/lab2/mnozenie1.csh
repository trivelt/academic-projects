#!/bin/tcsh
# Maciej Michalec, grupa 2

foreach i (`seq 1 9`)
    foreach j (`seq 1 9`)
        @ result = $i * $j
        echo -n $result
        echo -n "\t"
    end
    echo ""
end

