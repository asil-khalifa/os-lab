#!/bin/bash

# Function to calculate the mean
calculate_mean() {
  arr=("$@")
  sum=0
  for num in "${arr[@]}"; do
    sum=$((sum + num))
  done
  mean=$(echo "$sum / ${#arr[@]}" | bc -l)
  echo "Mean: $mean"
}

# Function to calculate the median
calculate_median() {
  arr=($(echo "$@" | tr " " "\n" | sort -n))
  len=${#arr[@]}
  if ((len % 2 == 1)); then
    median=${arr[len / 2]}
  else
    mid1=${arr[len / 2]}
    mid2=${arr[len / 2 - 1]}
    median=$(echo "($mid1 + $mid2) / 2" | bc -l)
  fi
  echo "Median: $median"
}

# Function to calculate the mode
calculate_mode() {
  declare -A freq
  for num in "$@"; do
    freq[$num]=$((freq[$num] + 1))
  done
  max_freq=0
  for num in "${!freq[@]}"; do
    if ((freq[$num] > max_freq)); then
      max_freq=${freq[$num]}
      mode=$num
    fi
  done
  echo "Mode: $mode"
}

# Input array
numbers=(1 2 2 3 4 4 4 5 6)

# Parallel execution
start_parallel=$(date +%s.%N)
calculate_mean "${numbers[@]}" &
calculate_median "${numbers[@]}" &
calculate_mode "${numbers[@]}" &
wait
end_parallel=$(date +%s.%N)

echo "Execution time (Parallel): $(echo "$end_parallel - $start_parallel" | bc) seconds"

# Sequential execution
start_sequential=$(date +%s.%N)
calculate_mean "${numbers[@]}"
calculate_median "${numbers[@]}"
calculate_mode "${numbers[@]}"
end_sequential=$(date +%s.%N)

echo "Execution time (Sequential): $(echo "$end_sequential - $start_sequential" | bc) seconds"
