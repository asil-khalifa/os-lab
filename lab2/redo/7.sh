#!/bin/bash
if [ "$#" -eq 0 ]; then
echo "You must enter the no.s along with cmd"
exit
fi

nums=("$@")
for num in "${nums[@]}"; do
if ((num%3==0)); then
echo "$num"
fi
done

