#ifndef SIMPLEX_HPP
#define SIMPLEX_HPP
#include <vector>
#include <iostream>
#include "./Point.h"
using namespace std;

class Simplex {
    public:
        static const int NUM_FACES = 6;
        static const int NUM_VERTEX = 4;
    private:
        double height;
        double width;
        vector<vector<Point> > faces;
        vector<Point> normals;

    public:
        Simplex() {};
        Simplex(string);
        void Draw(int, int, int, int, int, int, int, int, bool);
    friend class Board;
};

Simplex :: Simplex(string path) {
    faces.resize(NUM_FACES, vector<Point>(NUM_VERTEX, Point()));
    normals.resize(NUM_FACES, Point());
    freopen(path.c_str(), "r", stdin);
    string s;
    cin >> s;
    cin >> height >> width;
    for (int i = 0; i < NUM_FACES; ++i) {
        for (int j = 0; j < NUM_VERTEX; ++j) {
                double x, y, z;
                cin >> x >> y >> z;
                faces[i][j] = Point(x, y, z);
        }
    }
    cin >> s;
    for (int i = 0; i < NUM_FACES; ++i) {
        double x, y, z;
        cin >> x >> y >> z;
        normals[i] = Point(x, y, z);
    }   
}

void Simplex :: Draw(int rotate_x, int rotate_y, int rotate_z, int element, int n, int m, int NUM_ROWS, int NUM_COLS, bool is_real) {
    vector<float> textures_coord = {1, 1, 1, 0, 0, 0, 0, 1};
    for (size_t i = 0; i < NUM_FACES; ++i) {
        glPushMatrix();
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            if (is_real) {
                // if element in right place - color changes to green
                if (element == n*NUM_COLS + m + 1) {
                    glColor3ub(119, 221, 119);
                }
                glBindTexture(GL_TEXTURE_2D, element);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            glRotatef(rotate_x, 1, 0, 0);
            glRotatef(rotate_y, 0, 1, 0);
            glRotatef(rotate_z, 0, 0, 1);
            double tx, ty;
            if (NUM_COLS % 2 == 0) {
                tx = ((NUM_COLS - 1)/2.0  - m) * width;
            } else {
                tx = (NUM_COLS/2  - m) * width;
            }
            if (NUM_ROWS % 2 == 0) {
                ty = ((NUM_ROWS - 1)/2.0 - n) * height;
            } else {
                ty = (NUM_ROWS/2 - n) * height;
            }
            glTranslatef(tx, ty, 0);
            float* face = new float[3 * faces[i].size()];
            int l = 0;
            for (int j = 0; j < NUM_VERTEX; ++j) {
                face[l++] = faces[i][j].GetX();
                face[l++] = faces[i][j].GetY();
                face[l++] = faces[i][j].GetZ();
            }
            if (is_real) {
                glNormal3f(normals[i].GetX(), normals[i].GetY(), normals[i].GetZ());
                glVertexPointer(3, GL_FLOAT, 0, face);
                glTexCoordPointer(2, GL_FLOAT, 0, textures_coord.data());
                glDrawArrays(GL_POLYGON, 0, 4);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            } else {
                glColor3ub(element, 0, element);
                glVertexPointer(3, GL_FLOAT, 0, face);
                glDrawArrays(GL_POLYGON, 0, 4);
            }
            // glColor3f(0, 0, 0);
            // glRasterPos3f(-0.5, 0.5, 0);       
            // glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
            glColor3ub(255, 255, 255);
            glDisableClientState(GL_VERTEX_ARRAY);
            delete[] face;
        }
        glPopMatrix();
    }
}

#endif