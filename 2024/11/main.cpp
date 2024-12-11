#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <cmath>

using namespace std;

unordered_map<int, long long int> cache{};

inline int hash_pair(long int a, int b) {
    return a << 16 | b;
}

long long int count_rocks(long int stone, int n) {
    // Base case
    if (n == 0) {
        return 1;
    }

    if (cache.contains(hash_pair(stone, n))) {
        return cache[hash_pair(stone, n)];
    }

    // Rule 1
    if (stone == 0) {
        cout << "Rule 1" << endl;
        cache[hash_pair(stone, n)] = count_rocks(1, n-1);
        return cache[hash_pair(stone, n)];
    }
    // Rule 2
    int num_digits = (int) log10(stone) + 1;
    if (num_digits % 2 == 0) {
        cout << "Rule 2" << endl;
        int d = (int) pow(10, num_digits/2);
        int a = stone / d;
        int b = stone % d;
        cache[hash_pair(stone, n)] = count_rocks(a, n-1) + count_rocks(b, n-1);
        return cache[hash_pair(stone, n)];
    }

    // Rule 3
    cout << "Rule 3" << endl;
    cache[hash_pair(stone, n)] = count_rocks(stone*2024, n-1);
    return cache[hash_pair(stone, n)];
}

int main() {
    // c time code
    auto t1 = chrono::high_resolution_clock::now();
    long long int total = 0;
    {
        fstream fin("input.txt", ios::in);
        // split on whitespace
        string word;
        while (fin >> word) {
            cout << word << endl;
            total += count_rocks(stoi(word), 75);
        }
        fin.close();
    }
    cout << total << endl;

    // time c code
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1);
    cout << "Execution time: " << duration << endl;
    return 0;
}
