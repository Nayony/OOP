#include "FarHit.h"


FarHit::FarHit()
    : _abilityType(AbilityType::sFarHit), _Id(2),
            _energy_cost(AbilitiesSettings::StandartEnergyCost),
            _radius(AbilitiesSettings::FarHitRadius), _lvl(0),_bonusDamage(AbilitiesSettings::FarHitBonusDamage)
{
}

void FarHit::UseAbility(Robot& main, Game& game)
{
    game.SetAbility(_abilityType);
    game.SetCellsInRange(game.GetMap().CellsInRadius(main.GetPos(),_radius,true));
    
}
void FarHit::EndAbility(const Position pos,Game& game){
    bool found = false;
    for (auto& cell: game.GetCellsInRange()){
        if (cell == pos) {
            found = true; 
            break;
        }
    }
    if(game.GetMap().IsOccupied(pos) && found){
        auto& target = game.WhoOccupies(pos);
        game.GetPlayer().AddDamage(_bonusDamage);
        game.interaction(game.GetPlayer(),target);
        game.GetPlayer().AddDamage(-_bonusDamage);
        game.SetCellsInRange({});
		game.SetAbility(Abilities::AbilityType::sNone);
        game.GetPlayer().AddEnergy(-_energy_cost);
    }
}

Abilities::AbilityType FarHit::GetAbilityType() const { return _abilityType;}
int FarHit::GetAbilityId() const { return _Id;}
int FarHit::GetAbilityLvl() const { return _lvl;}
int FarHit::GetAbilityCost() const { return _energy_cost;}
void FarHit::LvlUp(int value) {
    if (value <= 0 || _lvl >= AbilitiesSettings::MaxLvl) return;
    if (value >= AbilitiesSettings::MaxLvl - _lvl) {
        _lvl = AbilitiesSettings::MaxLvl;
    } else {
        _lvl += value;
    }
    if (_lvl < AbilitiesSettings::MaxLvl && _lvl > 1){
        _bonusDamage += AbilitiesSettings::FarHitDamageDelta;
    }
}
int FarHit::GetRadius() const {return _radius;}