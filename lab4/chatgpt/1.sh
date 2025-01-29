#!/bin/bash

# Function to multiply a row of matrix A with all columns of matrix B
multiply_row() {
  row=$1
  cols_b=$2
  output_file=$3

  for ((j = 0; j < cols_b; j++)); do
    sum=0
    for ((k = 0; k < cols_b; k++)); do
      sum=$((sum + ${matrixA[row * cols_a + k]} * ${matrixB[k * cols_b + j]}))
    done
    result[row * cols_b + j]=$sum
  done

  echo "${result[@]}" >> "$output_file"
}

# Input matrices
matrixA=(1 2 3 4 5 6)
matrixB=(7 8 9 10 11 12)
rows_a=2
cols_a=3
rows_b=3
cols_b=2

if [ "$cols_a" -ne "$rows_b" ]; then
  echo "Matrix multiplication not possible (columns of A != rows of B)"
  exit 1
fi

# Parallel execution
output_file="result_parallel.txt"
: > "$output_file" # Clear the file
start_parallel=$(date +%s.%N)
for ((i = 0; i < rows_a; i++)); do
  multiply_row "$i" "$cols_b" "$output_file" &
done
wait
end_parallel=$(date +%s.%N)

echo "Result (Parallel):"
cat "$output_file"
echo "Execution time (Parallel): $(echo "$end_parallel - $start_parallel" | bc) seconds"

# Sequential execution
output_file="result_sequential.txt"
: > "$output_file" # Clear the file
start_sequential=$(date +%s.%N)
for ((i = 0; i < rows_a; i++)); do
  multiply_row "$i" "$cols_b" "$output_file"
done
end_sequential=$(date +%s.%N)

echo "Result (Sequential):"
cat "$output_file"
echo "Execution time (Sequential): $(echo "$end_sequential - $start_sequential" | bc) seconds"
