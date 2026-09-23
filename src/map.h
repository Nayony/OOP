#include <vector>
#include "cell.h"
#ifndef MAP
#define MAP
using namespace std;
class Map{
    protected:
        int _width,_height,_count_of_impassable;
        vector<int> _banned_cells;
        vector<vector<Cell>> _grid;
    public:
        Map(int _width, int _height,int _count_of_impassable);
        vector<int> CalculateCellSize(vector<int> window_size);
        const vector<int> GetSize();
        vector<vector<Cell>> CreateGrid();
        vector<int> RandomBlockedCells();
        vector<vector<Cell>>& GetGrid();
        vector<int> ChangeIndexType(int index);
};
    

#endif