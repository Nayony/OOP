#include "robot.h"

Robot::Robot(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy, int max_speed)
            :_hp(_max_hp), _max_hp(_max_hp), _energy(_max_energy), _max_energy(_max_energy),
            _xp(0), _xp_to_lvlup(_xp_to_lvlup), _current_lvl(0), _damage(_damage),
            _max_speed(max_speed), _speed(max_speed), _position(0, 0), _is_enemy(_is_enemy)
            {
            }
    void Robot ::SetHp(int value){
        if (value>_max_hp){
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
            _energy = _max_energy;
        }
        else if (value < 0){
            _energy = _max_energy;
        }
        else if (value>=0){
            _energy = value;
        }
    }
    void Robot ::SetSpeed(int value){
        if (value < 0 || value > _max_speed){
            _speed = _max_speed;
        }
        else{
            _speed = value;
        }
    }
    void Robot::IncreaseMaxHp(int value){
        _max_hp += value;
    }
    void Robot ::SetLvl(){
        while (_xp >= _xp_to_lvlup){
            _xp -= _xp_to_lvlup;
            _current_lvl += 1;
            IncreaseMaxHp(2);
            SetHp(GetHp() + 5);
        }
    }
    void Robot ::SetXp(int value){
        if (value>0){
            _xp += value;
        }
        if (_xp >= _xp_to_lvlup){
            SetLvl();
        }
    }
    void Robot ::SetEnemy(bool value){
        _is_enemy = value;
    }
    const int Robot ::GetDamage() const { return _damage;}
    const int Robot ::GetHp() const { return _hp;}
    const bool Robot ::GetType() const { return _is_enemy;}
    const int Robot ::GetEnergy() const { return _energy;}
    const int Robot ::GetLvl() const { return _current_lvl;}
    const int Robot ::GetXp() const { return _xp;}
    const int Robot ::GetSpeed() const { return _speed;}
    const int Robot ::GetXpToLvlUp() const { return _xp_to_lvlup;}
    const Position Robot::GetPos() const { return _position; }
