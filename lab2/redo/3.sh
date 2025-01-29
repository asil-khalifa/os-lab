#!/bin/bash
if [ -z "$1" ]; then
echo "Enter no. tho!"
exit
fi

num="$1"
prime=1
for ((i=2; i<num; i++)); do
if ((num%i == 0)); then
((prime=0))
break
fi
done

if ((prime==1)); then
echo "Prime"
else
echo "Not Prime"
fi

