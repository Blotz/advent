#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
    // c time code
    auto t1 = chrono::high_resolution_clock::now();

    {
        fstream fin("input.txt", ios::in);

        fin.close();
    }

    // time c code
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1);
    cout << "Execution time: " << duration << endl;
    return 0;
}
