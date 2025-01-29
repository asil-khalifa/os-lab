#!/bin/bash

# Generate sample matrices
echo -e "1 2 3\n4 5 6\n7 8 9" > matrixA.txt
echo -e "9 8 7\n6 5 4\n3 2 1" > matrixB.txt

# Read matrix dimensions
rows_A=$(wc -l < matrixA.txt)
cols_A=$(($(head -1 matrixA.txt | tr ' ' '\n' | wc -l)))
rows_B=$(wc -l < matrixB.txt)
cols_B=$(($(head -1 matrixB.txt | tr ' ' '\n' | wc -l)))

if [ $cols_A -ne $rows_B ]; then
    echo "Matrices cannot be multiplied."
    exit 1
fi

# Sequential Multiplication
start_seq=$(date +%s.%N)
result=()
for ((i=1; i<=rows_A; i++)); do
    a_row=$(sed -n "${i}p" matrixA.txt)
    row=()
    for ((j=1; j<=cols_B; j++)); do
        sum=0
        for ((k=1; k<=cols_A; k++)); do
            a_ik=$(echo $a_row | cut -d ' ' -f $k)
            b_kj=$(sed -n "${k}p" matrixB.txt | cut -d ' ' -f $j)
            sum=$((sum + a_ik * b_kj))
        done
        row+=($sum)
    done
    result+=("${row[*]}")
done
end_seq=$(date +%s.%N)
echo "Sequential Result:"
printf "%s\n" "${result[@]}"
echo "Sequential Time: $(echo "$end_seq - $start_seq" | bc) seconds"

# Parallel Multiplication
start_par=$(date +%s.%N)
num_threads=2
temp_dir=$(mktemp -d)
rows_per_thread=$(( (rows_A + num_threads - 1) / num_threads ))

for ((t=0; t<num_threads; t++)); do
    start_row=$(( t * rows_per_thread + 1 ))
    end_row=$(( (t + 1) * rows_per_thread ))
    ((end_row > rows_A)) && end_row=$rows_A

    (
        for ((i=start_row; i<=end_row; i++)); do
            a_row=$(sed -n "${i}p" matrixA.txt)
            row=()
            for ((j=1; j<=cols_B; j++)); do
                sum=0
                for ((k=1; k<=cols_A; k++)); do
                    a_ik=$(echo $a_row | cut -d ' ' -f $k)
                    b_kj=$(sed -n "${k}p" matrixB.txt | cut -d ' ' -f $j)
                    sum=$((sum + a_ik * b_kj))
                done
                row+=($sum)
            done
            echo "${row[*]}" >> "$temp_dir/result.$t"
        done
    ) &
done

wait
result_par=()
for ((t=0; t<num_threads; t++)); do
    while IFS= read -r line; do
        result_par+=("$line")
    done < "$temp_dir/result.$t"
done
end_par=$(date +%s.%N)
echo -e "\nParallel Result:"
printf "%s\n" "${result_par[@]}"
echo "Parallel Time: $(echo "$end_par - $start_par" | bc) seconds"
rm -rf "$temp_dir"