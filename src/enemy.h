
#ifndef ENEMY
#define ENEMY
#include "Robot.h"

class Enemy: public Robot{
    public:
        Enemy(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy);
};
#endif