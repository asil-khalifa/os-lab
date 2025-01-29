#!/bin/bash
echo "Enter:"
read n
prime=1
for ((i=2; i<n; i++)) do
if [ $((n%i)) -eq 0 ]; then
prime=0
break
fi
done
if [ $prime -eq 1 ]; then
echo "$n is prime"
else
echo "$n is not prime"
fi

