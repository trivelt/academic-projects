#!/bin/bash
# Maciej Michalec, grupa 2

function print_table {
    numbers=$(seq $1 1 $2) 
    for i in $numbers; do
        for j in $(seq $1 $2); do
            if [ $3 = "+" ]; then
                echo -n $(( i + j ))                 
            elif [ $3 = "\*" ]; then
                echo -n $(( i * j )) 
            elif [ $3 = "-" ]; then
                echo -n $(( i - j )) 
            elif [ $3 = '\' ]; then
                echo -n $(( i \ j )) 
            elif [ $3 = '%' ]; then
                echo -n $(( i % j )) 
            fi
            echo -n -e "\t"
        done
        echo ""
    done
}

function print_reverted_table {
    numbers=$(seq $1 -1 $2)
    for i in $numbers; do
        for j in $(seq $1 -1 $2); do
            if [ $3 = "+" ]; then
                echo -n $(( i + j ))                 
            elif [ $3 = "\*" ]; then
                echo -n $(( i * j )) 
            elif [ $3 = "-" ]; then
                echo -n $(( i - j )) 
            elif [ $3 = '\' ]; then
                echo -n $(( i \ j )) 
            elif [ $3 = '%' ]; then
                echo -n $(( i % j )) 
            fi
            echo -n -e "\t"
        done
        echo ""
    done
}

if [ $# -lt 3 ]; then
    echo 'Za malo argumentow. Podaj dwie liczby i znak operatora matematycznego (+, -, *, / lub %) poprzedzony backslashem, a znak mnozenia dodatkowo otoczony cudzyslowem'
    exit 1
fi

numbers=()
isOperator=0
operator=""

for arg in $1 $2 $3; do
    if [[ "$arg" =~ ^[0-9]+$ ]]; then
        echo liczba    	
        numbers+=("$arg")
    elif [ "$arg" = '+' -o "$arg" = '-' -o "$arg" = '\*' -o "$arg" = '/' -o "$arg" = '%' ]; then
        echo znak
        isOperator=1
        operator="$arg"
    fi
done

if [ ${#numbers[@]} -ne 2 ] || [ $isOperator -ne  1 ]; then
    echo Bledne argumenty
    exit 1
fi

if [ ${numbers[0]} -gt ${numbers[1]} ]; then
    print_reverted_table ${numbers[0]} ${numbers[1]} $operator
else
    print_table ${numbers[0]} ${numbers[1]} $operator
fi

exit 0
