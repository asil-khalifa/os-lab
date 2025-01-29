// Question 2: Mean, Median, and Mode using Threads (C++)
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <unordered_map>
#include <chrono>

using namespace std;

vector<int> numbers;
float mean;
float median;
int mode;

void calculate_mean() {
    long sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    mean = static_cast<float>(sum) / numbers.size();
}

void calculate_median() {
    sort(numbers.begin(), numbers.end());
    int n = numbers.size();
    if (n % 2 == 0) {
        median = (numbers[n / 2 - 1] + numbers[n / 2]) / 2.0;
    } else {
        median = numbers[n / 2];
    }
}

void calculate_mode() {
    unordered_map<int, int> freq;
    for (int num : numbers) {
        freq[num]++;
    }

    int max_count = 0;
    for (const auto& [key, value] : freq) {
        if (value > max_count) {
            max_count = value;
            mode = key;
        }
    }
}

void sequential_calculation() {
    calculate_mean();
    calculate_median();
    calculate_mode();
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    numbers.resize(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    // Sequential execution
    auto start_seq = chrono::high_resolution_clock::now();
    sequential_calculation();
    auto end_seq = chrono::high_resolution_clock::now();
    chrono::duration<double> seq_time = end_seq - start_seq;

    // Parallel execution
    thread mean_thread(calculate_mean);
    thread median_thread(calculate_median);
    thread mode_thread(calculate_mode);

    auto start_par = chrono::high_resolution_clock::now();
    mean_thread.join();
    median_thread.join();
    mode_thread.join();
    auto end_par = chrono::high_resolution_clock::now();
    chrono::duration<double> par_time = end_par - start_par;

    // Print results
    cout << "\nSequential Execution:\n";
    cout << "Mean: " << mean << "\n";
    cout << "Median: " << median << "\n";
    cout << "Mode: " << mode << "\n";
    cout << "Execution Time: " << seq_time.count() << " seconds\n";

    cout << "\nParallel Execution:\n";
    cout << "Mean: " << mean << "\n";
    cout << "Median: " << median << "\n";
    cout << "Mode: " << mode << "\n";
    cout << "Execution Time: " << par_time.count() << " seconds\n";

    return 0;
}
