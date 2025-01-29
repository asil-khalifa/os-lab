#!/bin/bash

if [ -z "$1" ]; then
echo "Enter the dir name along with command"
exit
fi

dir="$1"
if [ ! -d "$dir" ]; then
echo "Not a dir!"
exit
fi

for file in "$dir"/*; do
if [ -f "$file" ]; then
head -v -n 5 "$file"
fi
done

