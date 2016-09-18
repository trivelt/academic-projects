#!/bin/bash
# Maciej Michalec, grupa 2

function print_multiplication_table {
    numbers=$(seq $1 1 $2) 
    for i in $numbers; do
        for j in $(seq $1 $2); do
            echo -n $(( i * j )) 
            echo -n -e "\t"
        done
        echo ""
    done
}

function print_reverted_multiplication_table {
    numbers=$(seq $1 -1 $2)
    for i in $numbers; do
        for j in $(seq $1 -1 $2); do
            echo -n $(( i * j )) 
            echo -n -e "\t"
        done
        echo ""
    done
}

if [ $# -lt 2 ]; then
    echo Za malo argumentow. Podaj co najmniej dwie liczby
    exit 1
fi

for arg in $1 $2; do
    if ! [[ "$arg" =~ ^[0-9]+$ ]]; then
        echo Pierwsze dwa parametry musza byc liczbami
        exit 1
    fi
done

if [ $1 -gt $2 ]; then
    print_reverted_multiplication_table $1 $2
else
    print_multiplication_table $1 $2   
fi

exit 0
