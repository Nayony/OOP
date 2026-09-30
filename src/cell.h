

#ifndef CELL
#define CELL

#include <vector>

class Cell{
    protected:
    bool _is_impassable;
    bool _is_occupied;
    bool _is_visible;
    bool _explored;
    bool _factory;
    int _cost;
    public:
        Cell();
        Cell(bool _is_impassable,bool _is_occupied, bool _is_visible, int _cost);
        const bool GetPassable() const;
        const bool GetOccupied() const;
        const bool GetVisible() const;
        const bool GetExplored() const;
        const int GetCost() const;
        const bool GetFactory() const;
        void SetPassable(bool value);
        void SetOccupied(bool value);
        void SetFactory(bool value);
        void SetVisible(bool value);
        void SetExplored(bool value);

        
};
    

#endif


