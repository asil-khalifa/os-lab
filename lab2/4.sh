echo "enter array: "
read -a arr
sum=0
for i in "${arr[@]}"; do
((sum+=i))
done
echo "$sum"
