#!/bin/bash

if [ -z $1 ]; then
    echo "bruh"
    exit
fi

names=("$@")
sum=0

for name in "${names[@]}"; do   
    len=${#name}
    for ((i=0; i<len; i++)); do
        ch=${name:i:1}
        val=$(printf "%d" "'$ch")
        ((sum+=val))
    done
done

echo $sum