#ifndef BOARD_HPP
#define BOARD_HPP
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <GLUT/GLUT.h>
#include <vector>
#include <fstream>
#include <random>
#include "./Simplex.hpp"
using namespace std;

class Board {
    public:
        static const int NUM_ROWS = 4;
        static const int NUM_COLS = 4;
    private:
        int rotate_x;
        int rotate_y;
        int rotate_z;
        Simplex simplex;
        vector<vector<int>> elements;
    public:
        Board();
        void ChangeRotateX(int delta) {this->rotate_x += delta;}
        void ChangeRotateY(int delta) {this->rotate_y += delta;}
        void ChangeRotateZ(int delta) {this->rotate_z += delta;}
        void Draw(bool);
        void Move(int color);
};

 Board :: Board() {
    rotate_x = -10;
    rotate_y = 0;
    rotate_z = 0;
    elements.resize(NUM_ROWS, vector<int>(NUM_COLS));

    int ind = 1;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            elements[i][j] = ind++;
        }
    }
    pair<int, int> empty = {NUM_ROWS-1, NUM_COLS-1};
    vector<int> di = {1, -1, 0, 0};
    vector<int> dj = {0,  0, 1, -1};
    for (int i = 0; i < 10; ++i) {
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

void Board :: Draw(bool is_real) {
    for (int n = 0; n < NUM_ROWS; ++n) {
        for (int m = 0; m < NUM_COLS; ++m) {
            if (is_real) {
                if (elements[n][m] == NUM_ROWS * NUM_COLS) {
                    continue;
                }
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }
            float tx = -NUM_ROWS/2.0 + 0.5 + m;
            float ty =  NUM_COLS/2.0 - 0.5 - n;
            simplex.Draw(rotate_x, rotate_y, rotate_z, tx, ty, elements[n][m], is_real);
            if (is_real) {
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
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