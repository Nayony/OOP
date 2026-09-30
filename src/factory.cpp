#include "factory.h"
Factory::Factory()
    : _posMain(0,0)
{

}

const Position Factory::GetPosMain() const{
    return _posMain;
}
void Factory::SetPosMain(const Position& position){
       _posMain = position;
}