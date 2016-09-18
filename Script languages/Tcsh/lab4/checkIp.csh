#!/bin/tcsh
# Maciej Michalec, grupa 2

set rx='([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])'

echo $1 | grep -q -E ^"$rx"."$rx"."$rx"."$rx"$
if ( $? != 0 ) then
    exit 1
endif

exit 0
