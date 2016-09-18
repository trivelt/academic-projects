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

if [ $# -lt 3 ]; then
    echo 'Za malo argumentow. Podaj dwa adresy IP oraz liste oddzielonych przecinkami portow'
    exit 1
fi

rx='([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])'

for arg in "$1" "$2"; do
    if ! [[ "$arg" =~ ^$rx\.$rx\.$rx\.$rx$ ]]; then
        echo "IP $arg is not valid"
        exit 1
    fi    
done 

rx='[0-9]+(,[0-9]+)*'
if ! [[ "$3" =~ ^$rx$ ]]; then
    echo "List of ports is not valid"
    exit 1
fi

ports=$(echo "$3" | tr "," " ")
for port in $ports; do
    if [[ $port -gt 65535 ]]; then
        echo "Port number $port is not valid"
        exit 1
    fi
done
ports=($ports)

# storing names of services assigned to the specified ports
services=()
for port in ${ports[@]}; do
    found="None"
    while read line; do
        if [[ "$line" == *"$port/tcp"* ]]; then
            foundList=($line)
            portAndName=${foundList[1]}
            if [[ $portAndName == "$port/tcp" ]]; then
                found=${foundList[0]}
            fi
        fi
    done < /etc/services
    services+=($found)
done


firstIp="$1"
secondIp="$2"
if [[ $(ip2dec "$firstIp") -gt $(ip2dec "$secondIp") ]]; then
    firstIp="$secondIp"
    secondIp="$1"    
fi

echo "Checking ports $3 for addresses in range $firstIp - $secondIp"
firstIpDec=$(ip2dec $firstIp)
secondIpDec=$(ip2dec $secondIp)

seq $firstIpDec $secondIpDec | \
while read ip; do
    ipNumb=$(dec2ip $ip)
    echo $ipNumb
    counter=0
    for port in ${ports[@]}; do
        echo -e -n "\t$port"
        serviceName=${services[counter]}
        if [[ $serviceName != "None" ]]; then
            echo -n " ($serviceName)"
        fi
        echo -e -n " - "

        nc -z $ipNumb $port
        if (( $? == 0)); then
            echo open
        else
            echo closed
        fi
    counter=$[counter+1]
    done
done

exit 0

