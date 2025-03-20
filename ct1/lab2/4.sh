#!/bin/bash

echo "Enter array: "
read -a arr

s=0

for num in "${arr[@]}"; do
((s+=num))
done
echo "$s"