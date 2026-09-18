#include <vector>

#ifndef CELL
#define CELL

class Cell{
    protected:
    bool _is_impassable;
    public:
        Cell();
        Cell(bool _is_impassable);
        const bool GetPassible();
};
    

#endif