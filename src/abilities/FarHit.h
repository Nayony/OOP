#ifndef FAR_HIT_H
#define FAR_HIT_H

#include "abilities.h"
#include "../Robot.h"
#include "../game.h"


class FarHit : public Abilities {
public:
    FarHit();
    void UseAbility(Robot& main, Game& game) override;
    void EndAbility(const Position pos,Game& game) override;

    AbilityType GetAbilityType() const override;
    int GetAbilityId() const override;
    int GetAbilityLvl() const override;
    int GetAbilityCost() const override;
    void LvlUp(int value) override;
    int GetRadius() const;
private:
    AbilityType _abilityType;
    int _Id;
    int _energy_cost;
    int _radius;
    int _lvl;
    int _bonusDamage;
};

#endif
