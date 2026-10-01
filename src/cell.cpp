#include "cell.h"


Cell::Cell(bool _is_impassable, bool _is_occupied, bool _is_visible, int _cost)
    : _is_impassable(_is_impassable), _is_occupied(_is_occupied), _is_visible(_is_visible), _explored(false),
    _cost(_cost), _factory(false)

{
}
void Cell::SetPassable(bool value){
    _is_impassable = value;
}
void Cell::SetOccupied(bool value){
    _is_occupied = value;
}
void Cell::SetVisible(bool value){
    _is_visible = value;
}
void Cell::SetExplored(bool value){
    _explored = value;
}
void Cell::SetFactory(bool value){
    _factory = value;
    SetPassable(value);
}

const bool Cell::GetPassable() const{ return !_is_impassable;}
const bool Cell::GetOccupied() const{ return _is_occupied;}
const bool Cell::GetVisible() const{ return _is_visible;}
const bool Cell::GetExplored() const{ return _explored;}
const bool Cell::GetFactory() const{ return _factory;}
const int Cell::GetCost() const{ return _cost;}

