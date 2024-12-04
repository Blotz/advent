#include <iostream>
#include <fstream>

bool matchesNext(std::istream &stream, const std::string &str) {
    std::streampos original_pos = stream.tellg(); // Save the current position
    char c;
    for (char expected : str) {
        if (!(stream >> std::noskipws >> c) || c != expected) {
            // If reading fails or character doesn't match, restore position and return false
            stream.clear(); // Clear any error flags
            stream.seekg(original_pos);
            return false;
        }
    }
    // Restore position to original for non-destructive check
    stream.clear(); // Clear any error flags
    stream.seekg(original_pos);
    return true;
}

int main() {
    char c;
    char d1, d2;
    int total = 0;
    std::fstream file("input.txt", std::ios::in);

    d1 = '0';
    // d2 = '0';  // technically not needed
    while (file >> std::noskipws >> c) {
        // match digits
        if ((int) c >= 48 && (int) c <= 57) {
            if (d1 == '0') {
                d1 = c;
            }
            d2 = c;
        }
        // match string
        if (c == 'o') {
            if (matchesNext(file, "ne")) {
                if (d1 == '0') {
                    d1 = '1';
                }
                d2 = '1';
            }
        }
        if (c == 't') {
            if (matchesNext(file, "wo")) {
                if (d1 == '0') {
                    d1 = '2';
                }
                d2 = '2';
            }
        }
        if (c == 't') {
            if (matchesNext(file, "hree")) {
                if (d1 == '0') {
                    d1 = '3';
                }
                d2 = '3';
            }
        }
        if (c == 'f') {
            if (matchesNext(file, "our")) {
                if (d1 == '0') {
                    d1 = '4';
                }
                d2 = '4';
            }
        }
        if (c == 'f') {
            if (matchesNext(file, "ive")) {
                if (d1 == '0') {
                    d1 = '5';
                }
                d2 = '5';
            }
        }
        if (c == 's') {
            if (matchesNext(file, "ix")) {
                if (d1 == '0') {
                    d1 = '6';
                }
                d2 = '6';
            }
        }
        if (c == 's') {
            if (matchesNext(file, "even")) {
                if (d1 == '0') {
                    d1 = '7';
                }
                d2 = '7';
            }
        }
        if (c == 'e') {
            if (matchesNext(file, "ight")) {
                if (d1 == '0') {
                    d1 = '8';
                }
                d2 = '8';
            }
        }
        if (c == 'n') {
            if (matchesNext(file, "ine")) {
                if (d1 == '0') {
                    d1 = '9';
                }
                d2 = '9';
            }
        }
        // match newline
        if (c == '\n') {
            d1 = '0';
            // d2 = '0';
            int n = stoi(std::string(1, d1) + std::string(1, d2));
            total += n;
        }
    }

    std::cout << total << std::endl;

    return 0;
}

