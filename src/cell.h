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
        const bool GetPassible();
        const bool GetOccupied();
        void SetOccupied(bool value);
        
};
    

#endif


