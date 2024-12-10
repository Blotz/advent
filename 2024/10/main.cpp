#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

static int dirs[4][2] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

void print_grid(vector<vector<int>> grid) {
    for (int i=0; i < grid.size(); i++) {
        for (int j=0; j < grid[i].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

bool is_inbound(int x, int y, int max_x, int max_y) {
    return x >= 0 && x < max_x && y >= 0 && y < max_y;
}

int task1_trail(vector<vector<int>> &grid, int x, int y) {
    int current = grid[y][x];
    if (current == 9) {
        // janky hack to stop us counting endings more than once
        grid[y][x] = 0;  
        return 1;
    }

    int count = 0;

    for (int i=0; i < 4; i++) {
        int new_x = x + dirs[i][1];
        int new_y = y + dirs[i][0];

        if (!is_inbound(new_x, new_y, grid[0].size(), grid.size())) { continue; }
        if (grid[new_y][new_x] != current+1) { continue; }
        count += task1_trail(grid, new_x, new_y);
        // optional speedup 
        grid[y][x] = 0;
    }

    return count;
}

int task2_trail(vector<vector<int>> &grid, int x, int y) {
    int current = grid[y][x];
    // base case
    if (current == 9) { return 1; }

    int count = 0;

    for (int i=0; i < 4; i++) {
        int new_x = x + dirs[i][1];
        int new_y = y + dirs[i][0];

        if (!is_inbound(new_x, new_y, grid[0].size(), grid.size())) { continue; }
        if (grid[new_y][new_x] != current+1) { continue; }

        count += task2_trail(grid, new_x, new_y);
    }

    return count;
}

int main() {
    // c time code
    auto t1 = chrono::high_resolution_clock::now();

    // puzzel input
    vector<vector<int>> grid{};

    {
        vector<int> row{};
        
        fstream fin("input.txt", ios::in);
        char c;
        while(fin >> noskipws >> c) {
            if (c == '\n') {
                grid.push_back(row);
                row.clear();
            } else {
                row.push_back(c-'0');
            }
        }
        fin.close();
    }

    // algorithm
    // print_grid(grid);
    int task1 = 0;
    int task2 = 0;
    vector<vector<int>> _grid;

    for (int y=0; y < grid.size(); y++) {
        for (int x=0; x < grid[y].size(); x++) {
            if (grid[y][x] == 0) {
                // we need to copy because we edit grid with
                // because of our hack. :P
                _grid = grid;
                task1 += task1_trail(_grid, x, y);
                task2 += task2_trail(grid, x, y);
            }
        }
    }

    cout << "Task 1: " << task1 << endl;
    cout << "Task 2: " << task2 << endl;
    

    // time c code
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1);
    cout << "Execution time: " << duration << endl;
    return 0;
}
