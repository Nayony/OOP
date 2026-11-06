#ifndef TELEPORT_H
#define TELEPORT_H

#include "abilities.h"
#include "../Robot.h"
#include "../game.h"

class Teleport : public Abilities {
public:
    Teleport();
    void UseAbility(Robot& main, Game& game) override;
    void EndAbility(const Position pos, Game& game) override;

    AbilityType GetAbilityType() const override;
    int GetAbilityId() const override;
    int GetAbilityLvl() const override;
    int GetAbilityCost() const override;
    bool LvlUp(int value) override;
    int GetRadius() const;
    Position RandomCell(std::vector<Position>);
private:
    AbilityType _abilityType;
    int _Id;
    int _energy_cost;
    int _radius;
    int _lvl;
};

#endif
