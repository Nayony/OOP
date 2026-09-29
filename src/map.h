#ifndef MAP
#define MAP

#include <vector>
#include "cell.h"
#include "position.h"
#include "player.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

class Robot;

class Map{
    protected:
        int _width,_height,_count_of_impassable;
        vector<int> _banned_cells;
        vector<vector<Cell>> _grid;
    public:
        Map(int _width, int _height,int _count_of_impassable);
        const vector<int> CalculateCellSize(vector<int> window_size) const;
        const vector<int> GetSize() const;
        vector<vector<Cell>> CreateGrid();
        vector<int> RandomBlockedCells(vector<int>& indexses);
        //vector <int> RandomCostlyCells(vector<int>& indexes);
        vector<vector<Cell>>& GetGrid();
        const vector<vector<Cell>>& GetGrid() const;
        Position ChangeIndexType(int index);
        Cell& GetCell(const Position& position);
        const Cell& GetCell(const Position& position) const;
        void FindFreeCell(Robot& robot);
        bool IsFree(const Position& position) const;
        bool IsOccupied(const Position& position) const;
        void SetVisibleToCells(const Player& player);
        int ManhattanDistance(const Position &position1,const Position &position2);
};
    

#endif
