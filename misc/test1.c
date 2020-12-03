#include <iostream>
using namespace std;
class Point {
public:
    Point(int xx, int yy);
    Point(Point &p);
    Point();
    int GetX() { return X;}
    int GetY() { return Y;}
private:
    int X, Y;
};
Point::Point(int xx, int yy) {
    X = xx;
    Y = yy;
}
Point::Point(Point &p) {
    X = p.X;
    Y = p.Y;
}
Point::Point() {
    X = 0;
    Y = 0;
}
int main() {
    Point A;
    Point B(1, 2);
    Point C(B);
    cout << A.GetX();
    return 0;
}
