#include <bits/stdc++.h>

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
    for (auto &[key, value] : freq) {
        if (value > max_count)
            max_count = value;
            mode = key;
    }
}

int main() {
    auto t1 = thread(calculate_mean), t2 = thread(calculate_median), t3 = thread(calculate_mode);

    t1.join();
    t2.join();
    t3.join();
    
}