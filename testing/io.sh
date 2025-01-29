#!/bin/bash
echo "Enter name"
read filename
if [ -e $filename ]; then
echo "$filename exists"
else
echo "Bruh what you upto"
fi
