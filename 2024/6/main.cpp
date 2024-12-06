#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_set>
#include <vector>

using namespace std;

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

int dirs[4][2] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

Direction operator++(Direction &dir) {
    dir = static_cast<Direction>((dir + 1) % 4);
    return dir;
}

bool is_inbounds(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int simple_hash(int x, int y, int d) {
    // x and y are at most 255 d is at most 4
    // 8 bits for x, 8 bits for y, 8 bits for d
    return (x << 16) | (y << 8) | d;
}
int simple_hash(int x, int y) {
    // x and y are at most 255 d is at most 4
    // 8 bits for x, 8 bits for y, 8 bits for d
    return (x << 8 | y);
}

void print_grid(vector<vector<int>> &grid, int orig_x, int orig_y) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (i == orig_y && j == orig_x) {
                cout << "^";
            } else if (grid[i][j] == 1) {
                cout << "#";
            } else if (grid[i][j] == 2) {
                cout << "+";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    // read input.txt
    vector<vector<int>> grid;
    int orig_x, orig_y;
    // iterate over characters in the file
    ifstream fin("input.txt", ios::in);
    vector<int> row = vector<int>();
    char c;
    while (fin >> noskipws >> c) {
        if (c == '\n') {
            grid.push_back(row);
            row.clear();
        } else if (c == '^') {
            orig_y = grid.size();
            orig_x = row.size();
            row.push_back(0);
        } else if (c == '#') {
            row.push_back(1);
        } else {
            row.push_back(0);
        }
    }

    // print grid
    // print_grid(grid, orig_x, orig_y);

    // follow the path
    int grid_x = grid.size();
    int grid_y = grid[0].size();
    Direction d;
    int x, y;
    int next_x, next_y;
    unordered_set<int> visited = unordered_set<int>();

    // set initial position
    d = NORTH;
    x = orig_x;
    y = orig_y;

    while (true) {
        visited.insert(simple_hash(x, y));
        
        // grid[y][x] = 2; // mark as visited

        next_x = x + dirs[d][1];
        next_y = y + dirs[d][0];

        if (!is_inbounds(next_x, next_y, grid_x, grid_y)) {
            break;
        } else if (grid[next_y][next_x] == 1) {
            ++d;
        } else {
            x = next_x;
            y = next_y;
        }
    }
    // print places visited
    cout << "Visited: " << visited.size() << endl;
    // print grid
    // print_grid(grid, orig_x, orig_y);

    // iterate over visited
    int loops = 0;
    int block_x, block_y;
    int steps;
    // int max_steps = grid_x*grid_y*4;
    int max_steps = 10000;  // doesnt need to be x*y*4

    for (auto it = visited.begin(); it != visited.end(); ++it) {
        // reverse the hash teehee
        block_x = (*it) >> 8;
        block_y = (*it) & 0xFF;

        x = orig_x;
        y = orig_y;
        d = NORTH;
        steps = 0;

        while (true) {
            if (steps > max_steps) {
                ++loops;
                break;
            }

            next_x = x + dirs[d][1];
            next_y = y + dirs[d][0];

            if (!is_inbounds(next_x, next_y, grid_x, grid_y)) {
                break;
            } else if (grid[next_y][next_x] == 1) {
                ++d;
            } else if (next_x == block_x && next_y == block_y) {
                ++d;
            } else {
                x = next_x;
                y = next_y;
                steps++;
            }
        }
    }
    cout << "Causes loops: " << loops << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << "ms" << endl;

    return 0;
}