#include "map.h"
#include "cell.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
using namespace std;
Map::Map(int _w,int _h,int _count_of_impassable)
    : _width(_w), _height(_h), _count_of_impassable(_count_of_impassable)
    {
    if (_width < 5){
        _width = 5;
    }
    else if(_width > 7){
        _width = 7;
    }
    if (_height < 5){
        _height = 5;
    }
    else if(_height > 7){
        _height = 7;
    }
    if (_count_of_impassable > min(_width,_height) - 1){
        _count_of_impassable = min(_width,_height) - 1;
    }
    _grid.assign(_height, vector<Cell>(_width, Cell(false,false)));
    }
    vector<int> Map::CalculateCellSize(vector<int> window_size){
        int cell_width = (window_size[0]) / _width;
        int cell_height = (window_size[1]) / _height;
        return vector<int>{cell_width, cell_height};
    }
    const vector<int> Map::GetSize(){ return {_width, _height};}
    vector<vector<Cell>>& Map::GetGrid(){ return _grid;}
    vector<int> Map::ChangeIndexType(int index){
        int row = index / _width;
        int col = index % _width;
        return {row, col};
    }
    vector <int> Map::RandomBlockedCells(){
        vector<int> nums;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(1,_width*_height);
        for (int i =0;i<_count_of_impassable;i++){
            nums.push_back(distr(gen));
        }
        return nums;
    }
    vector<vector<Cell>> Map::CreateGrid(){
        _grid.assign(_height, vector<Cell>(_width, Cell(false,false)));
        auto nums = RandomBlockedCells();
        int index = 0;
        for (int i = 0; i < _height; i++){
            for (int j = 0; j < _width; j++){
                index += 1;
                if (find(nums.begin(),nums.end(),index) != nums.end()){
                    _grid[i][j] = Cell(true,false);
                }
                else{
                    _grid[i][j] = Cell(false,false);
                }
            }
        }
        return _grid;
    }
    
    