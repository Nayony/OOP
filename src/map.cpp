#include "map.h"

using namespace std;
Map::Map(int _w,int _h,int _cnt_of_impassable)
    : _width(_w), _height(_h), _count_of_impassable(_cnt_of_impassable)
    {
    if (_width < 12){
        _width = 12;
    }
    else if(_width > 16){
        _width = 16;
    }
    if (_height < 12){
        _height = 12;
    }
    else if(_height > 16){
        _height = 16;
    }
    if (_count_of_impassable > min(_width,_height) - 1){
        _count_of_impassable = min(_width,_height) - 1;
    }
    _grid.assign(_height, vector<Cell>(_width, Cell(false,false,false,1)));
    }
    const vector<int> Map::CalculateCellSize(vector<int> window_size) const{
        int cell_width = (window_size[0]) / _width;
        int cell_height = (window_size[1]) / _height;
        return vector<int>{cell_width, cell_height};
    }
    const vector<int> Map::GetSize() const{ return {_width, _height};}
    vector<vector<Cell>>& Map::GetGrid() { return _grid;}
    const vector<vector<Cell>>& Map::GetGrid() const{ return _grid;}
    Position Map::ChangeIndexType(int index){
        int row = index / _width;
        int col = index % _width;
        return Position(col, row);
    }
    vector <int> Map::RandomBlockedCells(vector<int>& indexes){
        vector<int> nums;
        int value;
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> distr(1,_width*_height);
        for (int i =0;i<_count_of_impassable;i++){
            value = distr(gen);
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
    void Map::FindFreeCell(Robot& robot) {
        bool from_end = robot.GetType();
        int step = from_end ? -2 : 1;
        int x0 = from_end ? _width - 1 : 0;
        int y0 = from_end ? _height - 1 : 0;
        for (int y = y0; y >= 0 && y < _height; y += step) {
            for (int x = x0; x >= 0 && x < _width; x += step) {
                if (!_grid[y][x].GetPassable() || _grid[y][x].GetOccupied()) continue;
                for (int i = y - 1; i <= y + 1; ++i) {
                    for (int j = x - 1; j <= x + 1; ++j) {
                        if (i < 0 || i >= _height || j < 0 || j >= _width) continue;
                        if (i == y && j == x) continue; 
                        if (_grid[i][j].GetPassable() && !_grid[i][j].GetOccupied()) {
                            robot.SetPos(Position(x, y));
                            _grid[y][x].SetOccupied(true);
                            return;
                        }
                    }
                }
            }
        }
    }
    void Map::CellsForFactory(Factory &factory){
        bool res = true;
        for (int y = _height - 1; y >= 0; y -=1) {
            for (int x = _width - 1; x >= 0; x -= 1) {
                if((IsFree({x,y}) && IsOccupied({x,y}) == false) && ((IsFree({x+1,y}) && IsOccupied({x+1,y}) == false))){
                res = true;
                for(int i = y; i >= y-1; --i){
                    for(int j = x-1; j <= x; ++j){
                        if(!(IsFree({j,i}) && IsOccupied({j,i}) == false)){
                            res = false;
                            break;
                }
                            }
                        }
                        if (res == true) {
                            factory.SetPosMain({x,y});
                            _grid[y][x].SetFactory(true);
                            _grid[y-1][x].SetFactory(true);
                            _grid[y-1][x-1].SetFactory(true);
                            _grid[y][x-1].SetFactory(true);
                            //cout << " столбец " << x << " cтрока " << y;
                            break;
                        }
            }
        }
        if (res == true) {break;}
    }
}
    bool Map::IsFree(const Position& position) const{
        if (position.X() < 0 or position.Y() < 0 or position.X() >= _width or position.Y() >= _height){
            return false;
        }
        if (_grid[position.Y()][position.X()].GetPassable() == false){
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
    vector<vector<Cell>> Map::CreateGrid(){
        _grid.assign(_height, vector<Cell>(_width, Cell(false,false,false,1)));

        vector<int> all_indexes;
        all_indexes.reserve(_width * _height);
        for (int i = 1; i <= _width * _height; ++i) {
            all_indexes.push_back(i);
        }

        auto blocked = RandomBlockedCells(all_indexes);
        auto costly = RandomBlockedCells(all_indexes);

        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                const int cell_index = i * _width + j + 1;

                if (find(blocked.begin(), blocked.end(), cell_index) != blocked.end()) {
                    _grid[i][j] = Cell(true, false, false, 1);
                }
                else if (find(costly.begin(), costly.end(), cell_index) != costly.end()) {
                    _grid[i][j] = Cell(false, false, false, 2);
                }
                else {
                    _grid[i][j] = Cell(false, false, false, 1);
                }
            }
        }

        return _grid;
    }
    int Map::ManhattanDistance(const Position &position1,const Position &position2){
        return abs(position1.X() -position2.X()) + abs(position1.Y() -position2.Y());
    }

    void Map::SetVisibleToCells(const Player& player){
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                if (ManhattanDistance(Position(x,y),player.GetPos()) <= player.GetVisibleRadius()){
                    _grid[y][x].SetVisible(true);
                    _grid[y][x].SetExploed(true);
                }
                else{
                    _grid[y][x].SetVisible(false);
                }
            }
        }
    }
