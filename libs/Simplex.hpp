#include <vector>
#include <fstream>
#include "./Point.h"
using namespace std;

#ifndef SIMPLEX_H
#define SIMPLEX_H

class Simplex {
    public:
        static const int NUM_FACES = 6;
        static const int NUM_VERTEX = 4;
    private:
        vector<vector<Point>> faces;
        vector<Point> normals;
    public:
        Simplex();
    friend class Board;
};

Simplex :: Simplex() {
    faces.resize(NUM_FACES, vector<Point>(NUM_VERTEX, Point()));
    normals.resize(NUM_FACES, Point());
    freopen("./simplex.txt", "r", stdin);
    string s;
    cin >> s;
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

#endif