#!/bin/bash
echo "Enter: "
read n
test=$n
comp=0
pow=${#n}
for((;n != 0; )) do
((comp+=(n%10)**pow))
((n/=10))
done
if [ $comp -eq $test ]; then
echo "Armstrong"
else
echo "Not Armstrong"
fi

