#include "cell.h"
#include <algorithm>
#include <vector>

Cell::Cell()
    : _is_impassable(false)
{
}

Cell::Cell(bool _is_impassable)
    : _is_impassable(_is_impassable)
{
}

const bool Cell::GetPassible(){ return _is_impassable;}