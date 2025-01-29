#!/bin/bash
#read -p "Enter n: " n
if [ -z "$1" ]; then
echo "broo"
exit
fi

n="$1"
echo "$((n*(n+1)/2))"
