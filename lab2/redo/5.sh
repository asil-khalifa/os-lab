#!/bin/bash
read -p "Enter the number: " n

num=n
digs=0
for ((;num!=0;num/=10)); do
((digs++))
done

num=n
sum=0

for((;num!=0;num/=10)); do
((sum+=(num%10)**digs))
done

num=n
if ((num == sum)); then
echo "Armstrong Number"
else
echo "Not an armstrong Number"
fi

