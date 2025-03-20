#!/bin/bash

if [ -z $1 ]; then
    echo "hello sir, enter arg in cmd line"
    exit
fi

dir=$1

for file in $dir/*; do
    if [ -f $file ]; then
        head -v -n 5 $file
    fi
done