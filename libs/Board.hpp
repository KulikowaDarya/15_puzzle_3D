#ifndef BOARD_HPP
#define BOARD_HPP
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <GLUT/GLUT.h>
#include <vector>
#include <fstream>
#include <random>
#include "./Simplex.hpp"
#include "./Block.hpp"
using namespace std;

class Board: public Block {
    public:
        Board() {};
        Board(int&, string);
        void Move(int);
};

 Board :: Board(int& ind, string simplex_path) : Block(4, 4, ind, simplex_path) {
    pair<int, int> empty = {NUM_ROWS-1, NUM_COLS-1};
    vector<int> di = {1, -1, 0, 0};
    vector<int> dj = {0,  0, 1, -1};
    for (int i = 0; i < 20; ++i) {
        for (int k = 0; k < di.size(); ++k) {
            int ii = empty.first + di[k];
            int jj = empty.second + dj[k];
            bool p = rand() % 2;
            if (ii >= 0 && ii < NUM_ROWS && jj >= 0 && jj < NUM_COLS && p) {
                swap(elements[ii][jj], elements[empty.first][empty.second]);
                empty = {ii, jj};
                break;
            }
        }
    }
    
}

void Board :: Move(int color) {
    vector<int> di = {0, -1, 0, 1};
    vector<int> dj = {1, 0, -1, 0};
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            if (color == elements[i][j]) {
                for (int k = 0; k < di.size(); ++k) {
                    int ii = i+di[k];
                    int jj = j+dj[k];
                    if (ii >= 0 and ii < NUM_ROWS and jj >= 0 and jj < NUM_ROWS) {
                        if (elements[ii][jj] == NUM_ROWS * NUM_COLS) {
                            swap(elements[i][j], elements[ii][jj]);
                            cout << color << '\n';
                            return;
                        }
                    }
                }
            }
        }
    }
}

#endif