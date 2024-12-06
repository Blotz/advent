#include <iostream>
#include <fstream>
#include <unordered_set>
#include <chrono>

using namespace std;

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

static int dirs[4][2] = {
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
void print_grid(char **grid, int grid_x, int grid_y) {
    for (int i = 0; i < grid_y; ++i) {
        for (int j = 0; j < grid_x; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    // read file width & height
    ifstream fin("input.txt");
    string unused;
    getline(fin, unused);
    int grid_x = unused.length();
    
    int grid_y = 1;
    while (getline(fin, unused)) {
        ++grid_y;
    }

    // reset file
    fin.clear();
    fin.seekg(0, ios::beg);

    // load data into grid
    char **grid = new char*[grid_y];

    int orig_x, orig_y;
    char c;

    for (int i = 0; i < grid_y; ++i) {
        grid[i] = new char[grid_x];
        for (int j = 0; j < grid_x; ++j) {
            fin >> noskipws >> c;
            if (c == '\n') {
                fin >> noskipws >> c;
            }
            grid[i][j] = c;
            if (c == '^') {
                orig_x = j;
                orig_y = i;
            }
        }
    }
    // print_grid(grid, grid_x, grid_y);

    // follow the path
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
        
        next_x = x + dirs[d][1];
        next_y = y + dirs[d][0];

        if (!is_inbounds(next_x, next_y, grid_x, grid_y)) {
            break;
        } else if (grid[next_y][next_x] == '#') {
            ++d;
        } else {
            x = next_x;
            y = next_y;
        }
    }
    // print places visited
    cout << "Visited: " << visited.size() << endl;

    // iterate over visited
    int loops = 0;
    int block_x, block_y;
    int steps;
    unordered_set<int> directional_visited = unordered_set<int>();

    for (auto it = visited.begin(); it != visited.end(); ++it) {
        // reverse the hash teehee
        block_x = (*it) >> 8;
        block_y = (*it) & 0xFF;

        x = orig_x;
        y = orig_y;
        d = NORTH;
        directional_visited.clear();

        while (true) {
            next_x = x + dirs[d][1];
            next_y = y + dirs[d][0];

            if (!is_inbounds(next_x, next_y, grid_x, grid_y)) {
                break;
            } else if (grid[next_y][next_x] == '#') {
                ++d;
                if (directional_visited.contains(simple_hash(x, y, d))) {
                    ++loops;
                    break;
                }
                directional_visited.insert(simple_hash(x, y, d));
            } else if (next_x == block_x && next_y == block_y) {
                ++d;
                if (directional_visited.contains(simple_hash(x, y, d))) {
                    ++loops;
                    break;
                }
                directional_visited.insert(simple_hash(x, y, d));
            } else {
                x = next_x;
                y = next_y;
                ++steps;
            }
        }
    }
    cout << "Causes loops: " << loops << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << "ms" << endl;

    for (int i = 0; i < grid_y; ++i) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
