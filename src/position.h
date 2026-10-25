
#ifndef POSITION
#define POSITION
class Position {
public:
    Position(int x, int y);
    bool operator==(const Position& other) const;
    int X() const;
    int Y() const;

private:
    int x_;
    int y_;
};

#endif
