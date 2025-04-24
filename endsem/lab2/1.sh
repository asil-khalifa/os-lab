#!/bin/bash

if [ -z $1 ]; then
    echo "bruh"
    exit
fi

arr=${@}

for word in $arr; do
    sum=0
    for ((i=0; i<${#word}; i++)); do
        ch=${word:i:1}
        val=$(printf "%d" "'$ch")
        ((sum+=val))
    done
    echo $sum

done

