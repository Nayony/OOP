#ifndef MAP
#define MAP
#include <vector>
#include "cell.h"
#include "position.h"
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
        vector<int> RandomBlockedCells();
        vector<vector<Cell>>& GetGrid();
        const vector<vector<Cell>>& GetGrid() const;
        Position ChangeIndexType(int index);
        Cell& GetCell(const Position& position);
        void FindFreeCell(Robot& robot);
        bool IsFree(const Position& position) const;
        bool IsOccupied(const Position& position) const;
};
    

#endif
