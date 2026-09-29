

#ifndef ROBOT_H
#define ROBOT_H
#include "position.h"
class Robot{
    protected:
        int _hp, _max_hp, _energy, _max_energy, _xp, _xp_to_lvlup, _current_lvl,_damage, _max_speed, _speed;
        Position _position;
        bool _is_enemy;
    public:
    Robot(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy, int _max_speed);
    void SetHp(int value);
    void SetEnergy(int value);
    void SetLvl();
    void SetXp(int value);
    void SetEnemy(bool value);
    void SetSpeed(int value);
    void IncreaseMaxHp(int value);
    void SetPos(const Position& position);
    const int GetHp() const;
    const bool GetType() const;
    const int GetEnergy() const;
    const int GetDamage() const;
    const int GetLvl() const;
    const int GetXp() const;
    const int GetSpeed() const;
    const int GetXpToLvlUp() const;
    const Position GetPos() const;

};
#endif
