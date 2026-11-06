

#ifndef CELL
#define CELL

#include <algorithm>
#include <vector>
#include <memory>
#include "statuses/statuses.h"

class Cell{
    private:
    bool _is_occupied;
    bool _is_visible;
    bool _explored;
    bool _factory;
    int _cost;
    std::vector<StatusType> _statuses;
    public:
        Cell(bool _is_occupied, bool _is_visible, int _cost);
        void EraseStatus(StatusType type);
        bool FindStatus(StatusType type);
        const bool GetOccupied() const;
        const bool GetVisible() const;
        const bool GetExplored() const;
        const int GetCost() const;
        const int GetStatusesCount() const;
        const bool GetFactory() const;
        const std::vector<StatusType> GetStatuses() const;
        void AddStatus(StatusType type);
        void SetOccupied(bool value);
        void SetCost(int value);
        void SetFactory(bool value);
        void SetVisible(bool value);
        void SetExplored(bool value);

        
};
    

#endif


