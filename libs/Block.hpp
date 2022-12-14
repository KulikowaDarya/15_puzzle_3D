#ifndef BLOCK_HPP
#define BLOCK_HPP
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#include <GLUT/GLUT.h>
#include <vector>
#include "./Simplex.hpp"
using namespace std;

class Block {
    protected:
        int NUM_ROWS;
        int NUM_COLS;
        int rotate_x;
        int rotate_y;
        int rotate_z;
        Simplex simplex;
        vector<vector<int>> elements;
    public:
        Block() {};
        Block(int, int, int&, string);
        int GetN() {return NUM_ROWS;}
        int GetM() {return NUM_COLS;}
        void ChangeRotateX(int delta) {this->rotate_x += delta;}
        void ChangeRotateY(int delta) {this->rotate_y += delta;}
        void ChangeRotateZ(int delta) {this->rotate_z += delta;}
        int Draw(bool);
};

Block :: Block(int n, int m, int& ind, string simplex_path) {
    rotate_x = -20;
    rotate_y = 0;
    rotate_z = 0;
    NUM_ROWS = n;
    NUM_COLS = m;
    simplex = Simplex(simplex_path);
    elements.resize(NUM_ROWS, vector<int>(NUM_COLS));

    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            elements[i][j] = ind++;
        }
    }
}

int Block :: Draw(bool is_real) {
    int finished = 0;
    for (int n = 0; n < NUM_ROWS; ++n) {
        for (int m = 0; m < NUM_COLS; ++m) {
            if (is_real) {
                if (elements[n][m] == NUM_COLS*NUM_ROWS) {
                    continue;
                }
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }
            finished += simplex.Draw(rotate_x, rotate_y, rotate_z, elements[n][m], n, m, NUM_ROWS, NUM_COLS, is_real);
            if (is_real) {
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
            }
        }
    }
    return finished;
}

#endif