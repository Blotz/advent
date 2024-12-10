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

int follow_trail(vector<vector<int>> &grid, int x, int y) {
    int current = grid[y][x];
    if (current == 9) {
        return 1;
    }

    int count = 0;

    for (int i=0; i < 4; i++) {
        int new_x = x + dirs[i][1];
        int new_y = y + dirs[i][0];

        if (is_inbound(new_x, new_y, grid[0].size(), grid.size())) {
            if (grid[new_y][new_x] == current+1) {
                count += follow_trail(grid, new_x, new_y);
            }
        }
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
    int total = 0;
    int count;


    for (int y=0; y < grid.size(); y++) {
        for (int x=0; x < grid[y].size(); x++) {
            if (grid[y][x] == 0) {
                count = follow_trail(grid, x, y);
                cout << count << endl;
                total += count;
            }
        }
    }

    cout << "Total: " << total << endl;
    

    // time c code
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1);
    cout << "Execution time: " << duration << endl;
    return 0;
}
