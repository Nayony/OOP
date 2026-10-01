
#ifndef FACTORY
#define FACTORY
#include "position.h"



class Factory{
    private:
    Position _posMain;
    int _spawnPeriod;
    public:
        Factory();
        const Position GetPosMain () const;
        void SetPosMain(const Position& position);
        void SetSpawnPeriod(int value);
        const int GetSpawnPeriod() const;
};
    

#endif
