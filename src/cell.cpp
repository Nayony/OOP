#include "cell.h"


Cell::Cell(bool _is_occupied, bool _is_visible, int _cost)
    : _is_occupied(_is_occupied), _is_visible(_is_visible), _explored(false),
    _cost(_cost), _factory(false)

{
}
bool Cell::FindStatus(StatusType type){
    auto pi = std::find(_statuses.begin(),_statuses.end(),type);
    if (pi != _statuses.end()){
        return true;
    }
    return false;
}
void Cell::EraseStatus(StatusType type){
    if (FindStatus(type)){
        auto pi = std::find(_statuses.begin(),_statuses.end(),type);
        _statuses.erase(pi);
    }
}
void Cell::AddStatus(StatusType type){

    _statuses.push_back(type);
}
void Cell::SetOccupied(bool value){
    _is_occupied = value;
}
void Cell::SetCost(int value){
    _cost = value;
}
void Cell::SetVisible(bool value){
    _is_visible = value;
}
void Cell::SetExplored(bool value){
    _explored = value;
}
void Cell::SetFactory(bool value){
    _factory = value;
    SetCost(-1);
}

const bool Cell::GetOccupied() const{ return _is_occupied;}
const bool Cell::GetVisible() const{ return _is_visible;}
const bool Cell::GetExplored() const{ return _explored;}
const bool Cell::GetFactory() const{ return _factory;}
const int Cell::GetCost() const{ return _cost;}
const std::vector<StatusType> Cell::GetStatuses() const{ return _statuses;}
const int Cell::GetStatusesCount() const{ return _statuses.size();}

