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

struct area {
    char type;
    char explored_type;
    int perimeter;
    int area;
    int corners;
};

struct edge {
    char type;
    Direction dir;
    int turns;
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
}

void search(int x, int y, grid &puzzle, area &ret) {
    // edge case. we hit the boarder.
    if (!is_inbounds(x, y, puzzle[0].size(), puzzle.size())) {
        ret.perimeter++; 
        return;
    }
    // previously explored area
    if (puzzle[y][x] == ret.explored_type) {
        return;
    }
    // new area
    if (puzzle[y][x] != ret.type) {
        ret.perimeter++; 
        return;
    }

    ret.area++;
    // overwrite explored areas to stop re exploring
    puzzle[y][x] = ret.explored_type;

    // really i could try count of area corners here too
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
            && (puzzle[l_y][l_x] == ret.type || puzzle[l_y][l_x] == ret.explored_type));
        bool f_free = (
            is_inbounds(f_x, f_y, puzzle[0].size(), puzzle.size()) 
            && (puzzle[f_y][f_x] == ret.type || puzzle[f_y][f_x] == ret.explored_type));
        bool c_free = (
            is_inbounds(c_x, c_y, puzzle[0].size(), puzzle.size()) 
            && (puzzle[c_y][c_x] == ret.type || puzzle[c_y][c_x] == ret.explored_type));
        
        if (!c_free && f_free && l_free) {
            ret.corners++;
        }
        if (!f_free && !l_free) {
            ret.corners++;
        }
    }

    for (int i = 0; i < 4; i++) {
        search(x + direction[i][1], y + direction[i][0], puzzle, ret);
    }
}

area explore(int x, int y, grid &puzzle) {
    area a{};
    a.type = puzzle[y][x];
    a.explored_type = a.type + 32;  // lowercase
    a.area = 0;
    a.perimeter = 0;
    a.corners = 0;

    search(x, y, puzzle, a);
    return a;
}

int follow_edge(int x, int y, grid &puzzle) {
    char type = puzzle[y][x];
    int turns = 0;
    Direction d = EAST;
    int _x = x;
    int _y = y;
    int max_x = puzzle[0].size();
    int max_y = puzzle.size();

    while (turns < 4 || !(_x == x && _y == y && d == EAST)) {
        // cout << _x << " " << _y << " " << d << endl;
        int forward_x = _x + direction[d][1];
        int forward_y = _y + direction[d][0];

        int corner_dx = _x + direction[modulo(d-1, 4)][1] + direction[d][1];
        int corner_dy = _y + direction[modulo(d-1, 4)][0] + direction[d][0];

        // logic
        bool forward_free = is_inbounds(forward_x, forward_y, max_x, max_y) && puzzle[forward_y][forward_x] == type;
        bool corner_free = is_inbounds(corner_dx, corner_dy, max_x, max_y) && puzzle[corner_dy][corner_dx] == type;
        if (corner_free && forward_free) {
            _x = corner_dx;
            _y = corner_dy;
            --d;
            turns++;
            continue;
        }

        if (forward_free) {
            _x = forward_x;
            _y = forward_y;
            continue;
        }
        // else turn right
        ++d;
        turns++;

    };

    return turns;
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

    // print
    // print_grid(puzzle);
    // cout << endl;

    // int x = 0;
    // int y = 0;

    // area a = explore(x, y, puzzle);
    // int turns = follow_edge(x, y, puzzle);

    // cout << "type: " << a.type << " area: " << a.area << " perimeter: " << a.perimeter << " turns: " << turns << endl;
    print_grid(puzzle);

    int total_task1 = 0;
    int total_task2 = 0;
    for (int y=0; y<puzzle.size(); y++) {
        for (int x=0; x<puzzle[0].size(); x++) {
            // lowercase
            if (puzzle[y][x] >= 97) { continue; }

            area a = explore(x, y, puzzle);
            // Stupid code doesnt work because of edge case
            // where an area is completely surrounded by another area
            // int turns = follow_edge(x, y, puzzle);

            cout << "type: " << a.type << " area: " << a.area << " perimeter: " << a.perimeter << " turns: " << a.corners << endl;

            total_task1 += a.perimeter*a.area;
            total_task2 += a.area * a.corners;
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
