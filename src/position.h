
#ifndef POSITION
#define POSITION
class Position {
public:
    Position(int x, int y) : x_(x), y_(y) {}

    int X() const {}
    int Y() const {}

private:
    int x_;
    int y_;
};

#endif