
#ifndef FACTORY
#define FACTORY
#include "position.h"



class Factory{
    protected:
    Position _posMain;
    public:
        Factory();
        const Position GetPosMain () const;
        void SetPosMain(const Position& position);
};
    

#endif
