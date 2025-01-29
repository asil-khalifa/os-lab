#!/bin/bash
read -p "Enter array: " -a arr
sum=0

for num in "${arr[@]}"; do
((sum+=num))
done
echo "Sum= $sum"

