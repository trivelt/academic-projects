#!/bin/bash
# Maciej Michalec, grupa 2

function ip2dec {
    local a b c d ip=$@
    IFS=. read -r a b c d <<< "$ip"
    printf '%d\n' "$((a * 256 ** 3 + b * 256 ** 2 + c * 256 + d))"
}

function dec2ip {
    local ip dec=$@
    for e in {3..0}
    do
        ((octet = dec / (256 ** e) ))
        ((dec -= octet * 256 ** e))
        ip+=$delim$octet
        delim=.
    done
    printf '%s\n' "$ip"
}

if [ $# -lt 2 ]; then
    echo 'Za malo argumentow. Podaj dwa adresy IP'
    exit 1
fi

rx='([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])'

for arg in "$@"; do
    if ! [[ "$arg" =~ ^$rx\.$rx\.$rx\.$rx$ ]]; then
        echo "IP $arg is not valid"
        exit 1
    fi    
done 

firstIp="$1"
secondIp="$2"
if [[ $(ip2dec "$firstIp") -gt $(ip2dec "$secondIp") ]]; then
    firstIp="$secondIp"
    secondIp="$1"    
fi

echo "Ping in range $1 - $2"
firstIpDec=$(ip2dec $firstIp)
secondIpDec=$(ip2dec $secondIp)


seq $firstIpDec $secondIpDec | \
while read ip; do
    ipNumb=$(dec2ip $ip)
    ping $ipNumb -c 1 -w 1 > /dev/null
    if (( $? == 0 )); then
        echo -e "$ipNumb\tOK"
    else
        echo -e "$ipNumb\tWRONG"
    fi
done

exit 0
