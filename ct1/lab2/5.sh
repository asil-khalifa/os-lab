#!/bin/bash

echo "Enter: "
read n
num=$n
digs=0

for((;num!=0;num/=10)); do
    ((digs+=1))
done

num=$n
sum=0

for ((;num!=0;num/=10));do
    ((sum+=(num%10)**digs))
done

if [ $sum -eq $n ]; then
    echo "Armstrong"
else
    echo "Not Armstrong"
fi