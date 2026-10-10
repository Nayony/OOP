#ifndef MAP
#define MAP

#include <vector>
#include "cell.h"
#include "position.h"
#include <optional>
#include "constants.h"
#include "player.h"
#include "factory.h"
#include <vector>

class Robot;

class Map{
    private:
        int _width,_height,_count_of_blocked;
        std::vector<std::vector<Cell>> _grid;
    public:
        Map(int _width, int _height,int _count_of_blocked);
        const std::vector<int> GetSize() const;
        std::vector<std::vector<Cell>> CreateGrid();
        std::vector<int> RandomBlockedCells(std::vector<int>& indexses);
        bool CellsForFactory(Factory &factory);
        const std::vector<std::vector<Cell>>& GetGrid() const;
        Cell& GetCell(const Position& position);
        const Cell& GetCell(const Position& position) const;
        void FindFreeCell(Robot& robot);
        bool IsAvailable(const Position& pos) const;
        bool IsAreaAvailable(const Position& main) const;
        std::optional<Position> FindFreeAround(const Position& anchor, int size, int step) const;
        std::optional<Position> FindFreeNear(const Factory& factory) const;
        std::optional<Position> FindFreeNear(const Robot& robot) const;
        bool HasFreeNeighbor(int x, int y) const;
        void MarkFactoryArea(const Position& main);
        bool IsFree(const Position& position) const;
        bool IsOccupied(const Position& position) const;
        void SetVisibleToCells(const Player& player);
        int ManhattanDistance(const Position &position1,const Position &position2);
};
#endif
