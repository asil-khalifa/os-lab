#!/bin/bash
if [ -z "$1" ]; then
echo "Enter smth please!"
exit
fi

num="$1"
if ((num%2==0)); then
echo "Even Steven"
else
echo "Odd Todd"
fi

