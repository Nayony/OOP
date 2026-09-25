#include "robot.h"
#include <iostream>
using namespace std;
Robot::Robot(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy)
            :_max_hp(_max_hp), _damage(_damage) ,_hp(_max_hp), _max_energy(_max_energy),
            _energy(_max_energy), _xp(0), _xp_to_lvlup(240), _current_lvl(0), _is_enemy(_is_enemy),
            _position(0, 0)
            {
            }
    void Robot ::SetHp(int value){
        if (_hp+value>_max_hp){
            _hp = _max_hp;
        }
        else if (value>0){
            _hp = value;
            }
        if (value <= 0){
            _hp = 0;
        }
    }
    void Robot::SetPos(const Position& position){
        _position = position;
    }
    void Robot ::SetEnergy(int value){
        if (value>_max_energy){
            _hp = _max_energy;
        }
        if (value>0){
            _energy = value;
        }
    }
    void Robot ::SetLvl(int xp){
        while (_xp > _xp_to_lvlup){
            _xp - _xp_to_lvlup;
            _current_lvl += 1;
        }
    }
    void Robot ::SetXp(int value){
        if (value>0){
            _xp = value;
        }
    }
    void Robot ::SetEnemy(bool value){
        _is_enemy = value;
    }
    const int Robot ::GetDamage() { return _damage;}
    const int Robot ::GetHp() { return _hp;}
    const bool Robot ::GetType() { return _is_enemy;}
    const int Robot ::GetEnergy() { return _energy;}
    Position Robot::GetPos() const { return _position; }
