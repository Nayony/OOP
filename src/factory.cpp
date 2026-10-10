#include "factory.h"
#include "constants.h"
Factory::Factory(int spawnPeriod)
    : _posMain(0,0), _spawnPeriod(spawnPeriod)
{
    if (_spawnPeriod <= 0){
        _spawnPeriod = FactorySettings::SpawnPeriod;
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