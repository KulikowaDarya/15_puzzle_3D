#ifndef POINT_H
#define POINT_H
class Point {
    private:
        double x;
        double y;
        double z;
    public:
        Point() {x=0; y=0; z=0;}
        Point(double xx, double yy, double zz) {x=xx; y=yy; z=zz;}
        double GetX() {return x;}
        double GetY() {return y;}
        double GetZ() {return z;}
        void SetX(double x) {this->x = x;}
        void SetY(double y) {this->y = y;}
        void SetZ(double z) {this->z = z;}
};
#endif
