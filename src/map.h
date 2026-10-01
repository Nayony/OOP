#ifndef MAP
#define MAP

#include <vector>
#include "cell.h"
#include "position.h"
#include "player.h"
#include "factory.h"
#include <vector>

class Robot;

class Map{
    private:
        int _width,_height,_count_of_impassable;
        std::vector<int> _banned_cells;
        std::vector<std::vector<Cell>> _grid;
    public:
        Map(int _width, int _height,int _count_of_impassable);
        const std::vector<int> GetSize() const;
        std::vector<std::vector<Cell>> CreateGrid();
        std::vector<int> RandomBlockedCells(std::vector<int>& indexses);
        void CellsForFactory(Factory &factory);
        const std::vector<std::vector<Cell>>& GetGrid() const;
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
