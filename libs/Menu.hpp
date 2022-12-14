#ifndef MENU_HPP
#define MENU_HPP
#include "./Simplex.hpp"
#include "./Block.hpp"
using namespace std;

class Menu: protected Block {
    public:
        Menu() {};
        Menu(int);
};

Menu :: Menu(int ind=1) {
    NUM_ROWS = 3;
    NUM_COLS = 1;
    elements.resize(NUM_ROWS, vector<int>(NUM_COLS));

    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            elements[i][j] = ind++;
        }
    }
}

#endif