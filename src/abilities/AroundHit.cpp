#include "AroundHit.h"



AroundHit::AroundHit()
    : _abilityType(AbilityType::sAroundHit), _Id(1),
            _energy_cost(AbilitiesSettings::StandartEnergyCost),
            _radius(AbilitiesSettings::AroundHitRadius), _lvl(0)
{
}

std::vector<Position> AroundHit::FindTargets(Position pos, Game& game){
    std::vector<Position> targets;
    for (int y = -_radius; y <= _radius; ++y){
        for (int x = -_radius; x <= _radius; ++x){
            if (x == 0 && y == 0){
                continue;
            }

            Position cur_pos(pos.X() + x, pos.Y() + y);

            if (game.GetMap().IsOccupied(cur_pos)){
                targets.push_back(cur_pos);
            }
        }
    }
    return targets;
}

void AroundHit::UseAbility(Robot& main, Game& game)
{
    game.ClearSelection();
    const std::vector<Position> targets = FindTargets(main.GetPos(),game);
    for (const Position& target_pos : targets) {
        Robot& target = game.WhoOccupies(target_pos);
        if (main.GetType() != target.GetType()) {
            if (_lvl == AbilitiesSettings::MaxLvl) game.ApplyStatus(StatusType::sOverload,target);
            game.DealDamage(target,main.GetDamage());
        }
    }
    main.AddEnergy(-_energy_cost);
}
void AroundHit::EndAbility(const Position pos,Game& game){
    return;
}
AbilityType AroundHit::GetAbilityType() const { return _abilityType;}
int AroundHit::GetAbilityId() const { return _Id;}
int AroundHit::GetAbilityLvl() const { return _lvl;}
int AroundHit::GetAbilityCost() const { return _energy_cost;}
bool AroundHit::LvlUp(int value) {
    if (value <= 0 || _lvl >= AbilitiesSettings::MaxLvl) return false;
    if (value >= AbilitiesSettings::MaxLvl - _lvl) {
        _lvl = AbilitiesSettings::MaxLvl;
    } else {
        _lvl += value;
    }
    if (_lvl < AbilitiesSettings::MaxLvl && _lvl > 1){
        _radius += AbilitiesSettings::AroundHitRadiusDelta;
    }
    return true;
}
