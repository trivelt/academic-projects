#!/bin/bash
# Maciej Michalec, grupa 2

for i in $(seq 1 9); do
    for j in $(seq 1 9); do
        echo -n $(( i * j )) 
        echo -n -e "\t"
    done
    echo ""
done

