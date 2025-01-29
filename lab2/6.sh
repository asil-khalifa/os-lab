#!/bin/bash
if [ -z "$1" ]; then
echo "Please Enter"
exit
fi

if [ ! -d "$1" ]; then
echo "Not a valid dir"
exit
fi

for file in "$1"/*; do
if [ -f "$file" ]; then
head -n 5 -v "$file"
fi
done

