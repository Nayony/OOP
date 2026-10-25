#include "position.h"

Position::Position(int x, int y) : x_(x), y_(y) {
}

int Position::X() const {
    return x_;
}

int Position::Y() const {
    return y_;
}

bool Position::operator==(const Position& other) const {
    return (this->x_ == other.x_ && this->y_ == other.y_);
}