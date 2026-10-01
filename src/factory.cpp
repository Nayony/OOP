#include "factory.h"
Factory::Factory()
    : _posMain(0,0), _spawnPeriod(5)
{
    if (_spawnPeriod <= 0){
        _spawnPeriod = 5;
    }
}

const Position Factory::GetPosMain() const{
    return _posMain;
}
void Factory::SetPosMain(const Position& position){
       _posMain = position;
}
void Factory::SetSpawnPeriod(int value){
       _spawnPeriod = value;
}
const int Factory::GetSpawnPeriod() const{ return _spawnPeriod;}