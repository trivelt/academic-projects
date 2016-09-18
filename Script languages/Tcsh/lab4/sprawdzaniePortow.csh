#!/bin/tcsh
# Maciej Michalec, grupa 2
set nonomatch=1

if ( $# < 3 ) then
    echo Za malo argumentow. Podaj dwa adresy IP oraz liste oddzielonych przecinkami portow
    exit 1
endif

foreach arg ( $1 $2 )
    csh checkIp.csh $arg
    if ( $? != 0 ) then
        echo "IP $arg is not valid"
        exit 1
    endif
end

set rx='[0-9]+(,[0-9]+)*'
echo "$3" | grep -q -E ^"$rx"$
if ( $? != 0 ) then
    echo "List of ports is not valid"
    exit 1
endif

set ports = `echo "$3" | tr "," " "`
foreach port ($ports)
    if ( $port > 65535 ) then
        echo "Port number $port is not valid"
        exit 1        
    endif
end

set services = ()
foreach port ($ports)
    set found = "None"
    foreach line ("`cat /etc/services`")
        set result = `echo $line | grep -c "$port/tcp"`
        if ( $result != 0 ) then
            set foundList = ($line)
            set portAndName = $foundList[2]
            if ( $portAndName == "$port/tcp" ) then
                set found = $foundList[1]
            endif
        endif
    end
    set services = ($services $found)
end

set firstIp = "$1"
set secondIp = "$2"

set ip1Parts = ($firstIp:as/./ /)
set ip2Parts = ($secondIp:as/./ /)

@ ip1Dec = ($ip1Parts[1] * 16777216 + $ip1Parts[2] * 65536 + $ip1Parts[3] * 256 + $ip1Parts[4])
@ ip2Dec = ($ip2Parts[1] * 16777216 + $ip2Parts[2] * 65536 + $ip2Parts[3] * 256 + $ip2Parts[4])

if ($ip1Dec > $ip2Dec) then
    set firstIp = "$2"
    set secondIp = "$1"
    set tmp = "$ip1Dec"
    set ip1Dec = "$ip2Dec"
    set ip2Dec = "$tmp"
endif

echo "Checking ports $3 for addresses in range $firstIp - $secondIp"

foreach ip (`seq $ip1Dec $ip2Dec`)
    @ part1 = ($ip / 16777216)
    @ part2 = ($ip % 16777216 / 65536)
    @ part3 = ($ip % 65536 / 256)
    @ part4 = ($ip % 256)
    set IpAddr = $part1.$part2.$part3.$part4
    set counter = 1
    echo $IpAddr
    foreach port ($ports)
        printf "\t$port"
        set serviceName = $services[$counter]
        if ( $serviceName != "None" ) then
            printf "($serviceName)"
        endif
        printf " - "
        
        nc -z $IpAddr $port
        if ( $? == 0) then
            printf "open\n"
        else
            printf "closed\n"
        endif
        

        @ counter += 1
    end
end

exit 0

