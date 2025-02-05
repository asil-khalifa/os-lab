#include <bits/stdc++.h>
#include <ranges>

using namespace std;
int maxDifference(string s)
{
    unordered_map<char, int> store;
    for (auto ch : s)
    {
        store[ch]++;
    }

    int odd = INT_MIN, even = INT_MAX;
    for (auto &[key, val] : store)
    {
        if (key & 1)
            odd = ranges::max(odd, val);
        else
            even = ranges::min(even, val);
    }
    return odd - even;
}

int main()
{
    maxDifference("abcabcab");

}