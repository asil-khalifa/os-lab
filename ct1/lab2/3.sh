#!/bin/bash

if [ -z $1 ]; then
echo "bruh"
exit
fi
n=$1

if ((n == 1)); then
echo "Neither Prime nor composite"
exit
fi

for ((i=2; i<n; i++)); do
if [ $((n%i)) -eq 0 ]; then
echo "Not a Prime"
exit
fi
done

echo "Prime"