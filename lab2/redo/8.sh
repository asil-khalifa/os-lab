#!/bin/bash
if [ "$#" -eq 0 ]; then
echo "Enter the name in cmd line"
exit
fi

sum=0

for name in "$@"; do

for ((i=0; i<"${#name}"; i++)); do
chr="${name:i:1}"
val=$(printf "%d" "'$chr")

((sum+=val))
done
done
echo "$sum"

