#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include <chrono>

int get_index(const std::string& name) {
    if (name == "Alice") {
        return 0;
    } else if (name == "Bob") {
        return 1;
    } else if (name == "Carol") {
        return 2;
    } else if (name == "David") {
        return 3;
    } else if (name == "Eric") {
        return 4;
    } else if (name == "Frank") {
        return 5;
    } else if (name == "George") {
        return 6;
    } else if (name == "Mallory") {
        return 7;
    } else {
        return -1;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int happiness_matrix[9][9] = {0};
    int n = 9;

    std::fstream file("input.txt", std::ios::in);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string person, neighbour, loose_or_gain, tmp;
        int happiness;

        // Carol would lose 37 happiness units by sitting next to David.

        ss >> person >> tmp >> loose_or_gain >> happiness >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> neighbour;

        if (loose_or_gain == "lose") {
            happiness = -happiness;
        }
        neighbour.pop_back();

        // std::cout << person << " " << neighbour << " " << happiness << std::endl;
        happiness_matrix[get_index(person)][get_index(neighbour)] = happiness;
    }

    int max_happiness = 0;
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }

    do {
        int happiness = 0;
        for (int i = 0; i < n; i++) {
            happiness += happiness_matrix[v[i]][v[(i + 1) % n]];
            happiness += happiness_matrix[v[(i + 1) % n]][v[i]];
        }
        max_happiness = std::max(max_happiness, happiness);
    } while (std::next_permutation(v.begin(), v.end()));

    std::cout << max_happiness << std::endl;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Execution time: " << duration << "ms" << std::endl;
    return 0;
}

