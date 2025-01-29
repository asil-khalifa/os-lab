#!/bin/bash
if [ -z "$1" ]; then
echo "bruh"
exit
fi
name="$1"
sum=0
for ((i=0; i<"${#name}"; i++)); do
ch="${name:i:1}"
val=$(printf "%d" "'$ch")
((sum+=val))
echo "adding $val"
done
echo "Grand Total: $sum"
