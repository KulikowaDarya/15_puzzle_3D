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
        Block();
        void ChangeRotateX(int delta) {this->rotate_x += delta;}
        void ChangeRotateY(int delta) {this->rotate_y += delta;}
        void ChangeRotateZ(int delta) {this->rotate_z += delta;}
        void Draw(bool);
};

Block :: Block() {
    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 0;
}

void Block :: Draw(bool is_real) {
    for (int n = 0; n < NUM_ROWS; ++n) {
        for (int m = 0; m < NUM_COLS; ++m) {
            if (is_real) {
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_LIGHTING);
                glEnable(GL_LIGHT0);
            }
            simplex.Draw(rotate_x, rotate_y, rotate_z, elements[n][m], n, m, NUM_ROWS, NUM_COLS, is_real);
            if (is_real) {
                glDisable(GL_TEXTURE_2D);
                glDisable(GL_LIGHTING);
                glDisable(GL_LIGHT0);
            }
        }
    }
}

#endif