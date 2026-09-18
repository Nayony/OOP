#include "player.h"

Player::Player(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage,bool _is_enemy, int _visible_radius)
            : Robot(_max_hp,_max_energy, _xp_to_lvlup, _damage, _is_enemy), 
            _visible_radius(_visible_radius)
            {
            }