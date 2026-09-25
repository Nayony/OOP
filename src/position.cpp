#include "position.h"

Position::Position(int x, int y) : x_(x), y_(y) {
}

int Position::X() const {
    return x_;
}

int Position::Y() const {
    return y_;
}
