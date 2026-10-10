#include "map.h"
#include <algorithm>
#include <cstdlib>
#include <random>

Map::Map(int _w,int _h,int _count_of_blocked)
    : _width(_w), _height(_h), _count_of_blocked(_count_of_blocked)
    {
    if (_width < MapSettings::MinWidth){
        _width = MapSettings::MinWidth;
    }
    else if(_width > MapSettings::MaxWidth){
        _width = MapSettings::MaxWidth;
    }
    if (_height < MapSettings::MinHeight){
        _height = MapSettings::MinHeight;
    }
    else if(_height > MapSettings::MaxHeight){
        _height = MapSettings::MaxHeight;
    }
    if (_count_of_blocked > std::min(_width,_height) - 1){
        _count_of_blocked = std::min(_width,_height) - 1;
    }
    _grid.assign(_height, std::vector<Cell>(_width, Cell(false,false,1)));
    }

    const std::vector<int> Map::GetSize() const{ return {_width, _height};}
    const std::vector<std::vector<Cell>>& Map::GetGrid() const{ return _grid;}
    std::vector<int> Map::RandomBlockedCells(std::vector<int>& indexes){
        std::vector<int> nums;
        int value;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        for (int i =0;i<_count_of_blocked;i++){
            std::uniform_int_distribution<> distr(0,(int)indexes.size()-1);
            value = indexes[distr(gen)];
            auto pi = std::find(indexes.begin(), indexes.end(), value);
            if (pi != indexes.end()) {
                indexes.erase(pi);
            }
            nums.push_back(value);
        }
        return nums;
    }
    Cell& Map::GetCell(const Position& position) { return _grid[position.Y()][position.X()]; }
    const Cell& Map::GetCell(const Position& position) const { return _grid[position.Y()][position.X()]; }
    // попрощу написать в тройной цикл;
bool Map::IsAvailable(const Position& pos) const {
    if (pos.X() < 0 || pos.Y() < 0 || pos.X() >= _width || pos.Y() >= _height) return false;
    return IsFree(pos) && !IsOccupied(pos);
}

bool Map::HasFreeNeighbor(int x, int y) const {
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            if (IsAvailable({x + dx, y + dy})) return true;
        }
    }
    return false;
}

void Map::FindFreeCell(Robot& robot) {
    const bool from_end = robot.GetType();
    const int step = from_end ? MapSettings::EnemySearchStride : 1;
    const int start_x = from_end ? _width - 1 : 0;
    const int start_y = from_end ? _height - 1 : 0;

    for (int y = start_y; y >= 0 && y < _height; y += step) {
        for (int x = start_x; x >= 0 && x < _width; x += step) {
            if (!IsAvailable({x, y}) || !HasFreeNeighbor(x, y)) continue;

            robot.SetPos(Position(x, y));
            _grid[y][x].SetOccupied(true);
            return;
        }
    }
}

bool Map::IsAreaAvailable(const Position& main) const {
    for (int dy = 0; dy < MapSettings::FactorySize; ++dy)
        for (int dx = 0; dx < MapSettings::FactorySize; ++dx)
            if (!IsAvailable({main.X() - dx, main.Y() - dy})) return false;
    return true;
}

void Map::MarkFactoryArea(const Position& main) {
    for (int dy = 0; dy < MapSettings::FactorySize; ++dy)
        for (int dx = 0; dx < MapSettings::FactorySize; ++dx)
            _grid[main.Y() - dy][main.X() - dx].SetFactory(true);
}

bool Map::CellsForFactory(Factory& factory) {
    const int size = MapSettings::FactorySize;

    for (int y = _height - 1; y >= size - 1; --y) {
        for (int x = _width - 1; x >= size - 1; --x) {
            const Position main(x, y);
            if (!IsAreaAvailable(main)) continue;

            factory.SetPosMain(main);
            MarkFactoryArea(main);
            return true;
        }
    }
    return false;
}

std::optional<Position> Map::FindFreeAround(const Position& anchor, int size, int step) const {
    for (int dy = 0; dy < size; dy += step) {
        for (int dx = 0; dx < size; dx += step) {
            Position pos(anchor.X() + 1 - dx, anchor.Y() + 1 - dy);
            if (IsAvailable(pos)) return pos;
        }
    }
    return std::nullopt;
}

std::optional<Position> Map::FindFreeNear(const Factory& factory) const {
    return FindFreeAround(factory.GetPosMain(), MapSettings::FactoryRingSize, MapSettings::FactoryRingStep);
}

std::optional<Position> Map::FindFreeNear(const Robot& robot) const {
    return FindFreeAround(robot.GetPos(), MapSettings::RobotRingSize, MapSettings::RobotRingStep);
}
    bool Map::IsFree(const Position& position) const{
        if (position.X() < 0 or position.Y() < 0 or position.X() >= _width or position.Y() >= _height){
            return false;
        }
        if (_grid[position.Y()][position.X()].GetCost() == CellSettings::ImpassableCost){
            return false;
        }
        return true;
    }
    bool Map::IsOccupied(const Position& position) const{
        if (_grid[position.Y()][position.X()].GetOccupied() == true){
            return true;
        }
        return false;
    }
    std::vector<std::vector<Cell>> Map::CreateGrid(){
        _grid.assign(_height, std::vector<Cell>(_width, Cell(false,false,1)));

        std::vector<int> all_indexes;
        all_indexes.reserve(_width * _height);
        for (int i = 1; i <= _width * _height; ++i) {
            all_indexes.push_back(i);
        }

        auto blocked = RandomBlockedCells(all_indexes);
        auto costly = RandomBlockedCells(all_indexes);

        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                const int cell_index = i * _width + j + 1;

                if (std::find(blocked.begin(), blocked.end(), cell_index) != blocked.end()) {
                    _grid[i][j] = Cell(false, false, CellSettings::ImpassableCost);
                }
                else if (std::find(costly.begin(), costly.end(), cell_index) != costly.end()) {
                    _grid[i][j] = Cell(false, false, CellSettings::DifficultMoveCost);
                }
                else {
                    _grid[i][j] = Cell(false, false, CellSettings::DefaultMoveCost);
                }
            }
        }

        return _grid;
    }
    int Map::ManhattanDistance(const Position &position1,const Position &position2){
        return std::abs(position1.X() -position2.X()) + std::abs(position1.Y() -position2.Y());
    }

    void Map::SetVisibleToCells(const Player& player){
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                if (ManhattanDistance(Position(x,y),player.GetPos()) <= player.GetVisibleRadius()){
                    _grid[y][x].SetVisible(true);
                    _grid[y][x].SetExplored(true);
                }
                else{
                    _grid[y][x].SetVisible(false);
                }
            }
        }
    }
