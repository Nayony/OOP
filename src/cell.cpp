#include "cell.h"
#include <algorithm>
#include <vector>

Cell::Cell(bool _is_impassable, bool _is_occupied)
    : _is_impassable(_is_impassable), _is_occupied(_is_occupied)
{
}
void Cell::SetOccupied(bool value){
    _is_occupied = value;
}

const bool Cell::GetPassible(){ return _is_impassable;}
const bool Cell::GetOccupied(){ return _is_occupied;}