#include "cell.h"
#include <algorithm>
#include <vector>

Cell::Cell(bool _is_impassable, bool _is_occupied, bool _is_visible, int _cost)
    : _is_impassable(_is_impassable), _is_occupied(_is_occupied), _is_visible(_is_visible), _explored(false),
    _cost(_cost)

{
}
void Cell::SetOccupied(bool value){
    _is_occupied = value;
}
void Cell::SetVisible(bool value){
    _is_visible = value;
}
void Cell::SetExploed(bool value){
    _explored = value;
}

const bool Cell::GetPassable() const{ return !_is_impassable;}
const bool Cell::GetOccupied() const{ return _is_occupied;}
const bool Cell::GetVisible() const{ return _is_visible;}
const bool Cell::GetExplored() const{ return _explored;}
const int Cell::GetCost() const{ return _cost;}

