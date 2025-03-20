#!/bin/bash
if [ -z $1 ]; then
    echo "keep number as arg"
    exit
fi

n="$1"
if [ $((n%2)) -ne 1 ]; then
    echo "even"
else
    echo "odd"
fi