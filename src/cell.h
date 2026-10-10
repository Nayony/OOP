

#ifndef CELL
#define CELL

#include <algorithm>
#include <vector>

class Cell{
    private:
    bool _is_occupied;
    bool _is_visible;
    bool _explored;
    bool _factory;
    int _cost;
    public:
        Cell(bool _is_occupied, bool _is_visible, int _cost);
        const bool GetOccupied() const;
        const bool GetVisible() const;
        const bool GetExplored() const;
        const int GetCost() const;
        const bool GetFactory() const;
        void SetOccupied(bool value);
        void SetCost(int value);
        void SetFactory(bool value);
        void SetVisible(bool value);
        void SetExplored(bool value);

        
};
    

#endif


