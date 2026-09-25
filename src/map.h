#ifndef MAP
#define MAP
#include <vector>
#include "cell.h"
using namespace std;
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
        vector<int> ChangeIndexType(int index);
        Cell& GetCell(int x, int y);
};
    

#endif