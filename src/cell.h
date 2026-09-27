

#ifndef CELL
#define CELL

#include <vector>

class Cell{
    protected:
    bool _is_impassable;
    bool _is_occupied;
    bool _is_visible;
    bool _explored;
    public:
        Cell();
        Cell(bool _is_impassable,bool _is_occupied, bool _is_visible);
        const bool GetPassable() const;
        const bool GetOccupied() const;
        const bool GetVisible() const;
        const bool GetExplored() const;
        void SetOccupied(bool value);
        void SetVisible(bool value);
        void SetExploed(bool value);

        
};
    

#endif


