#pragma GCC optimize "trapv"

#include <iostream>
#include <fstream>
#include <chrono>


using namespace std;
using grid = vector<string>;

static const int direction[4][2] = {
    {-1, 0},// up
    {0, 1}, // right
    {1, 0}, // down
    {0, -1} // left
};

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct region {
    char type;
    char explored_type;
    int perimeter;
    int area;
    int corners;
};

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

Direction operator++(Direction &dir) {
    dir = static_cast<Direction>((dir + 1) % 4);
    return dir;
}

Direction operator--(Direction &dir) {
    dir = static_cast<Direction>(modulo((dir - 1), 4));
    return dir;
}


inline bool is_inbounds(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void print_grid(const grid &puzzle) {
    for (int y=0; y<puzzle.size(); y++) {
        for (int x = 0; x<puzzle[0].size(); x++) {
            cout << puzzle[y][x];
        }
        cout << endl;
    }
    cout << endl;
}

void search(int x, int y, grid &puzzle, region &r) {
    // edge case. we hit the boarder.
    if (!is_inbounds(x, y, puzzle[0].size(), puzzle.size())) {
        r.perimeter++; 
        return;
    }
    // previously explored area
    if (puzzle[y][x] == r.explored_type) {
        return;
    }
    // new area
    if (puzzle[y][x] != r.type) {
        r.perimeter++; 
        return;
    }

    r.area++;
    // overwrite explored areas to stop re exploring
    puzzle[y][x] = r.explored_type;

    // terrible code. i dont care anymore
    // inner corner
    // #.
    // .x
    // outer corner
    // /#
    // #x
    for (int i = 0; i < 4; i++) {
        int l_x = x + direction[modulo(i-1, 4)][1]; // left
        int l_y = y + direction[modulo(i-1, 4)][0]; 
        int f_x = x + direction[i][1]; // forward
        int f_y = y + direction[i][0];
        int c_x = x + direction[i][1] + direction[modulo(i-1, 4)][1]; // corner
        int c_y = y + direction[i][0] + direction[modulo(i-1, 4)][0];

        // logic
        bool l_free = (
            is_inbounds(l_x, l_y, puzzle[0].size(), puzzle.size()) 
            && (puzzle[l_y][l_x] == r.type || puzzle[l_y][l_x] == r.explored_type));
        bool f_free = (
            is_inbounds(f_x, f_y, puzzle[0].size(), puzzle.size()) 
            && (puzzle[f_y][f_x] == r.type || puzzle[f_y][f_x] == r.explored_type));
        bool c_free = (
            is_inbounds(c_x, c_y, puzzle[0].size(), puzzle.size()) 
            && (puzzle[c_y][c_x] == r.type || puzzle[c_y][c_x] == r.explored_type));
        
        if (!c_free && f_free && l_free) {
            r.corners++;
        }
        if (!f_free && !l_free) {
            r.corners++;
        }
    }
    // terrible code finished

    for (int i = 0; i < 4; i++) {
        search(x + direction[i][1], y + direction[i][0], puzzle, r);
    }
}

region explore(int x, int y, grid &puzzle) {
    region r{};
    r.type = puzzle[y][x];
    r.explored_type = r.type + 32;  // lowercase
    r.area = 0;
    r.perimeter = 0;
    r.corners = 0;

    search(x, y, puzzle, r);
    return r;
}

int main() {
    // c time code
    auto t1 = chrono::high_resolution_clock::now();

    grid puzzle;

    {
        fstream fin("input.txt", ios::in);
        string line;
        while (fin >> line) {
            puzzle.push_back(line);
        }

        fin.close();
    }

    // testing
    // print_grid(puzzle);
    // area a = explore(0, 0, puzzle);
    // int turns = follow_edge(0, 0, puzzle);

    print_grid(puzzle);

    int total_task1 = 0;
    int total_task2 = 0;
    for (int y=0; y<puzzle.size(); y++) {
        for (int x=0; x<puzzle[0].size(); x++) {
            // lowercase
            if (puzzle[y][x] >= 97) { continue; }

            region r = explore(x, y, puzzle);
            cout << "type: " << r.type << " area: " << r.area << " perimeter: " << r.perimeter << " turns: " << r.corners << endl;

            total_task1 += r.area * r.perimeter;
            total_task2 += r.area * r.corners;
        }
    }
    
    cout << "Task 1: " << total_task1 << endl;
    cout << "Task 2: " << total_task2 << endl;


    // time c code
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1);
    cout << "Execution time: " << duration << endl;
    return 0;
}
