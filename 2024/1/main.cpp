
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <chrono>


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::unordered_map<int, int> rhs;
    int lhs[1000];

    std::fstream file("input.dat", std::ios::in);
    int idx = 0;
    while (file.good()) {
        // 1234 1234
        int a, b;
        file >> a >> b;

        // add b to rhs counter
        rhs[b]++;
        // add a to lhs array
        lhs[idx++] = a;
    }
    file.close();

    int result = 0;
    for (int i = 0; i < 1000; i++) {
        result += lhs[i] * rhs[lhs[i]];
    }

    std::cout << result << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Execution time: " << duration << "us" << std::endl;

    return 0;
}