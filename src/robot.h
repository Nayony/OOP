

#ifndef ROBOT_H
#define ROBOT_H
#include "position.h"
#include "constants.h"
#include "abilities/abilities.h"
#include "statuses/statuses.h"
#include <algorithm>
#include <memory>
class Robot{
    protected:
        int _hp, _max_hp, _energy, _max_energy, _xp, _xp_to_lvlup, _current_lvl,_damage, _max_speed, _speed;
        Position _position;
        bool _is_enemy;
        std::vector<std::unique_ptr<Abilities>> _abilities;
        std::vector<std::unique_ptr<Statuses>> _statuses;
        int _ability_point;
        bool _can_use_ability;
        bool _can_move;
        int _shield;
        bool _demise;

    private:
        void ProcessLevelUps();
    public:
    Robot(int _max_hp, int _max_energy, int _xp_to_lvlup,int _damage, bool _is_enemy, int _max_speed);
    void SetHp(int value);
    void AddHp(int value);
    void SetEnergy(int value);
    void AddEnergy(int value);
    void AddXp(int value);
    void AddDamage(int value);
    void SetEnemy(bool value);
    void SetSpeed(int value);
    void SetDemise(bool value);
    void AddSpeed(int value);
    void AddShield(int value);
    void SetCanUseAbility(bool value);
    void SetCanMove(bool value);
    void ResetSpeed();
    void ResetTurnResources();
    void IncreaseMaxHp(int value);
    void SetPos(const Position& position);
    Abilities* FindAbility(AbilityType type);
    const Abilities* FindAbility(AbilityType type) const;
    Statuses* FindStatus (StatusType type);
    void EraseStatus(StatusType type);
    void AddAbility(std::unique_ptr<Abilities> ability);
    void AddStatus(std::unique_ptr<Statuses> status);
    void AddAbilityPoint(int value);
    

    const int GetHp() const;
    const int GetMaxHp() const;
    const bool GetType() const;
    const bool GetDemise() const;
    const int GetEnergy() const;
    const int GetDamage() const;
    const int GetLvl() const;
    const int GetXp() const;
    const int GetShield() const;
    const int GetSpeed() const;
    const int GetXpToLvlUp() const;
    const Position GetPos() const;
    const bool CanUseAbility() const;
    const bool CanMove() const;
    const std::vector<std::unique_ptr<Abilities>>& GetAbilities() const;
    const std::vector<std::unique_ptr<Statuses>>& GetStatuses() const;
    const int HasAbilityPoint() const;
    
    

};
#endif
