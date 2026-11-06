#ifndef AROUND_HIT_H
#define AROUND_HIT_H

#include "abilities.h"
#include "../Robot.h"
#include "../game.h"


class AroundHit : public Abilities {
public:
    AroundHit();
    void UseAbility(Robot& main, Game& game) override;
    void EndAbility(const Position pos,Game& game) override;
    std::vector<Position> FindTargets(Position pos, Game& game);
    
    AbilityType GetAbilityType() const override;
    int GetAbilityId() const override;
    int GetAbilityLvl() const override;
    int GetAbilityCost() const override;
    bool LvlUp(int value) override;
    
private:

    AbilityType _abilityType;
    int _Id;
    int _energy_cost;
    int _radius;
    int _lvl;
};

#endif
