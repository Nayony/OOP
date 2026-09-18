
#ifndef PLAYER
#define PLAYER
#include "Robot.h"

class Player: public Robot{
    protected:
        int _visible_radius;
    public:
        Player(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage,bool _is_enemy, int _visible_radius);
};
#endif