#include <vector>
#include "cell.h"
#ifndef MAP
#define MAP

class Map{
    protected:
        int _width,_height,_count_of_impassable;
    public:
        Map(int _width, int _height,int _count_of_impassable);
        std::vector<int> CalculateCellSize(std::vector<int> window_size);
        std::vector<int> GetSize();
        std::vector<std::vector<Cell>> CreateGrid();
        std::vector<int> RandomBlockedCells();
};
    

#endif