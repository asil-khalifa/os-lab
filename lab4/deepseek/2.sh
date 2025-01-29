#!/bin/bash

# Sample dataset
echo -e "5\n3\n8\n7\n3\n5\n5\n9" > numbers.txt
numbers=($(cat numbers.txt))

# Sequential Calculations
start_seq=$(date +%s.%N)

# Mean
sum=0
count=0
for num in "${numbers[@]}"; do
    sum=$((sum + num))
    ((count++))
done
mean_seq=$(echo "scale=2; $sum / $count" | bc)

# Median
IFS=$'\n' sorted=($(sort -n <<<"${numbers[*]}"))
unset IFS
n=${#sorted[@]}
if (( n % 2 == 0 )); then
    mid=$((n/2))
    median_seq=$(echo "scale=2; (${sorted[mid-1]} + ${sorted[mid]}) / 2" | bc)
else
    median_seq=${sorted[n/2]}
fi

# Mode
declare -A freq_seq
max_freq_seq=0
mode_seq=()
for num in "${numbers[@]}"; do
    ((freq_seq[$num]++))
    current_freq=${freq_seq[$num]}
    if (( current_freq > max_freq_seq )); then
        max_freq_seq=$current_freq
        mode_seq=($num)
    elif (( current_freq == max_freq_seq )); then
        mode_seq+=($num)
    fi
done
if (( max_freq_seq == 1 && ${#numbers[@]} > 1 )); then
    mode_seq_str="No mode"
else
    mode_seq_str="${mode_seq[@]}"
fi

end_seq=$(date +%s.%N)
echo "Sequential Mean: $mean_seq"
echo "Sequential Median: $median_seq"
echo "Sequential Mode: $mode_seq_str"
echo "Sequential Time: $(echo "$end_seq - $start_seq" | bc) seconds"

# Parallel Calculations
start_par=$(date +%s.%N)
temp_dir=$(mktemp -d)

# Mean
(
    sum=0
    count=0
    for num in "${numbers[@]}"; do
        sum=$((sum + num))
        ((count++))
    done
    echo "scale=2; $sum / $count" | bc > "$temp_dir/mean"
) &

# Median
(
    IFS=$'\n' sorted=($(sort -n <<<"${numbers[*]}"))
    unset IFS
    n=${#sorted[@]}
    if (( n % 2 == 0 )); then
        mid=$((n/2))
        echo "scale=2; (${sorted[mid-1]} + ${sorted[mid]}) / 2" | bc > "$temp_dir/median"
    else
        echo "${sorted[n/2]}" > "$temp_dir/median"
    fi
) &

# Mode
(
    declare -A freq
    max_freq=0
    mode=()
    for num in "${numbers[@]}"; do
        ((freq[$num]++))
        current_freq=${freq[$num]}
        if (( current_freq > max_freq )); then
            max_freq=$current_freq
            mode=($num)
        elif (( current_freq == max_freq )); then
            mode+=($num)
        fi
    done
    if (( max_freq == 1 && ${#numbers[@]} > 1 )); then
        echo "No mode" > "$temp_dir/mode"
    else
        echo "${mode[@]}" > "$temp_dir/mode"
    fi
) &

wait
echo -e "\nParallel Mean: $(cat $temp_dir/mean)"
echo "Parallel Median: $(cat $temp_dir/median)"
echo "Parallel Mode: $(cat $temp_dir/mode)"
echo "Parallel Time: $(echo "$(date +%s.%N) - $start_par" | bc) seconds"
rm -rf "$temp_dir"