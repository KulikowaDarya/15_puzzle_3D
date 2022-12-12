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
        void Draw();
        void FakeDraw();
        void Move(int color);
};

 Board :: Board() {
    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 0;
    elements.resize(NUM_ROWS, vector<int>(NUM_COLS));

    int ind = 1;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            elements[i][j] = ind++;
        }
    }
    
    random_device rd;
    mt19937 g(rd());
    for (int i = 0; i < NUM_ROWS; ++i) {
        shuffle(elements[i].begin(), elements[i].end()-1, g);
    }
}

void Board :: Draw() {
    vector<float> textures_coord = {1, 1, 1, 0, 0, 0, 0, 1};
    int tx = 0, ty = 0;
    glTranslatef(0, 0, -7);
    for (int n = 0; n < NUM_ROWS; ++n) {
        for (int m = 0; m < NUM_COLS; ++m) {
            if (elements[n][m] == NUM_ROWS * NUM_COLS) {
                continue;
            }
            tx = m;
            ty = n;
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            for (size_t i = 0; i < simplex.NUM_FACES; ++i) {
                glPushMatrix();
                {
                    glBindTexture(GL_TEXTURE_2D, elements[n][m]);
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    glRotatef(rotate_x, 1, 0, 0);
                    glRotatef(rotate_y, 0, 1, 0);
                    glRotatef(rotate_z, 0, 0, 1);
                    glTranslatef(-NUM_ROWS/2.0 + 0.5 + tx, NUM_COLS/2.0 - 0.5 - ty, 0);
                    float* face = new float[3 * simplex.faces[i].size()];
                    int l = 0;
                    for (int j = 0; j < simplex.NUM_VERTEX; ++j) {
                        face[l++] = simplex.faces[i][j].GetX();
                        face[l++] = simplex.faces[i][j].GetY();
                        face[l++] = simplex.faces[i][j].GetZ();
                    }
                    glNormal3f(simplex.normals[i].GetX(), simplex.normals[i].GetY(), simplex.normals[i].GetZ());
                    glVertexPointer(3, GL_FLOAT, 0, face);
                    glTexCoordPointer(2, GL_FLOAT, 0, textures_coord.data());
                    glDrawArrays(GL_POLYGON, 0, 4);
                    glDisableClientState(GL_VERTEX_ARRAY);
                    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                    delete[] face;
                }
                glPopMatrix();
            }
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
        }
    }
}

void Board :: FakeDraw() {
    int tx = 0, ty = 0;
    glTranslatef(0, 0, -7);
    for (int n = 0; n < NUM_ROWS; ++n) {
        for (int m = 0; m < NUM_COLS; ++m) {
            tx = m;
            ty = n;
            for (size_t i = 0; i < simplex.NUM_FACES; ++i) {
                glPushMatrix();
                {
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glRotatef(rotate_x, 1, 0, 0);
                    glRotatef(rotate_y, 0, 1, 0);
                    glRotatef(rotate_z, 0, 0, 1);
                    glTranslatef(-NUM_ROWS/2.0 + 0.5 + tx, NUM_COLS/2.0 - 0.5 - ty, 0);
                    float* face = new float[3 * simplex.faces[i].size()];
                    int l = 0;
                    for (int j = 0; j < simplex.NUM_VERTEX; ++j) {
                        face[l++] = simplex.faces[i][j].GetX();
                        face[l++] = simplex.faces[i][j].GetY();
                        face[l++] = simplex.faces[i][j].GetZ();
                    }
                    glColor3ub(elements[n][m], 0, elements[n][m]);
                    glVertexPointer(3, GL_FLOAT, 0, face);
                    glDrawArrays(GL_POLYGON, 0, 4);
                    glDisableClientState(GL_VERTEX_ARRAY);
                    delete[] face;
                }
                glPopMatrix();
            }
        }
    }
    glColor3ub(255, 255, 255);
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