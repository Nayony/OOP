#include "AroundHit.h"



AroundHit::AroundHit()
    : _abilityType(AbilityType::sAroundHit), _Id(1),
            _energy_cost(AbilitiesSettings::StandartEnergyCost),
            _radius(AbilitiesSettings::AroundHitRadius), _lvl(0)
{
}

void AroundHit::FindTargets(Position pos, Game& game, std::vector<Robot*>& targets){
    for (int y = -_radius; y <= _radius; ++y){
        for (int x = -_radius; x <= _radius; ++x){
            if (x == 0 && y == 0){
                continue;
            }

            Position cur_pos(pos.X() + x, pos.Y() + y);

            if (game.GetMap().IsOccupied(cur_pos)){
                targets.push_back(&game.WhoOccupies(cur_pos));
            }
        }
    }
}

void AroundHit::UseAbility(Robot& main, Game& game)
{
    game.SetAbility(_abilityType);
    std::vector<Robot*> targets = {};
    FindTargets(main.GetPos(),game,targets);
    for (Robot* target : targets) {
        game.interaction(game.GetPlayer(),*target);
    }
    main.AddEnergy(-_energy_cost);
}
void AroundHit::EndAbility(const Position pos,Game& game){
    return;
}
Abilities::AbilityType AroundHit::GetAbilityType() const { return _abilityType;}
int AroundHit::GetAbilityId() const { return _Id;}
int AroundHit::GetAbilityLvl() const { return _lvl;}
int AroundHit::GetAbilityCost() const { return _energy_cost;}
void AroundHit::LvlUp(int value) {
    if (value <= 0 || _lvl >= AbilitiesSettings::MaxLvl) return;
    if (value >= AbilitiesSettings::MaxLvl - _lvl) {
        _lvl = AbilitiesSettings::MaxLvl;
    } else {
        _lvl += value;
    }
    if (_lvl < AbilitiesSettings::MaxLvl && _lvl > 1){
        _radius += AbilitiesSettings::AroundHitRadiusDelta;
    }
}
