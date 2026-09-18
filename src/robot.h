

#ifndef ROBOT_H
#define ROBOT_H


class Robot{
    protected:
        int _hp, _max_hp, _energy, _max_energy, _xp, _xp_to_lvlup, _current_lvl,_damage;
        bool _is_enemy;
    public:
    Robot(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy);
    void SetHp(int value);
    void SetEnergy(int value);
    void SetLvl(int value);
    void SetXp(int value);
    void SetEnemy(bool value);
    const int GetHp();
    const int GetDamage();
    const int GetType();
    const int GetEnergy();
    
    void interaction(Robot &other);
};
#endif
