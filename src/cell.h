#include <vector>

#ifndef CELL
#define CELL

class Cell{
    protected:
    bool _is_impassable;
    bool _is_occupied;
    public:
        Cell();
        Cell(bool _is_impassable,bool _is_occupied);
        const bool GetPassable() const;
        const bool GetOccupied() const;
        void SetOccupied(bool value);
        
};
    

#endif


