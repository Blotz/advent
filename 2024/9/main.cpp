#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

struct Block {
    int start;
    int size;
};

inline void print(const vector<int> &disk) {
    long long int total = 0; // long long because it doesnt fit in int
    for (int i=0; i<disk.size(); i++) {
        total += i*disk[i];
    }
    cout << total << endl;
}

inline void print(const vector<Block> &disk) {
    long long int total = 0;  // ditto
    for (int i=0; i<disk.size(); i++) {
        int file_start = disk[i].start;
        int file_size = disk[i].size;
        // for (int j=file_start; j<file_start+file_size; j++) {
        //     total += i*j;
        // }

        // use the formula for the sum of an arithmetic series
        total += ((long) i * file_size * (2*file_start + file_size - 1)) / 2;
    }
    cout << total << endl;
}


inline void task1(vector<int> &disk) {
    int n;
    int p = disk.size();
    for (int i=0; i<disk.size(); i++) {  // loop over each empty space
        if (disk[i] != -1) { continue; }
        n = -1;
        while (n == -1) {  // get the last non free number
            n = disk.back();
            disk.pop_back();
        }
        disk[i] = n;  // move to front
    }
}


inline void task2(vector<Block> &empty_blocks, vector<Block> &file_blocks) {
    for (int i=file_blocks.size()-1; i>=0; i--) {  // get each block from max to min
        int file_start = file_blocks[i].start;
        int file_size = file_blocks[i].size;

        for (int j=0; j<empty_blocks.size(); j++) {  // check against each empty block
            int empty_start = empty_blocks[j].start;
            int empty_size = empty_blocks[j].size;

            if (empty_start >= file_start) {  // stop checking. files only go left
                break;
            }
            if (file_size <= empty_size) {  // if the file fits, move it.
                file_blocks[i].start = empty_start;
                empty_blocks[j].start = empty_start + file_size;
                empty_blocks[j].size = empty_size - file_size;

                // we dont care about the empty space left by the file 
                // because files can only move left. there is no chance
                // that a file will be able to fill that hole.
                
                // cout << "moved " << i << " to " << empty_start << endl;
    
                break;
            }
        }
    }
}

int main() {
    // c time code
    auto t1 = chrono::high_resolution_clock::now();

    // read input
    vector<int> disk{};
    vector<Block> empty_blocks{};
    vector<Block> file_blocks{};
    {
        bool is_empty = false;
        int file_ID = 0;
        int n;
        int value;
        
        fstream fin("input.txt");
        char c;
        while (fin >> c) {
            n = (int) c - '0';
            if (is_empty) {
                value = -1;
                is_empty = false;
                empty_blocks.push_back(Block{
                    (int) disk.size(),
                    n
                });
            } else {
                value = file_ID++;
                is_empty = true;
                file_blocks.push_back(Block{
                    (int) disk.size(),
                    n
                });
            }

            for (int i=0; i<n; i++) 
                disk.push_back(value);
        }
        fin.close();
    }
    // task 1;
    task1(disk);
    print(disk);

    // task 2;
    task2(empty_blocks, file_blocks);
    print(file_blocks);

    // time c code
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1);
    cout << "Execution time: " << duration << endl;
    return 0;
}
