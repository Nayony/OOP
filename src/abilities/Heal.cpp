#include "Heal.h"


Heal::Heal()
    : _abilityType(AbilityType::sHeal), _Id(3),
            _energy_cost(AbilitiesSettings::HealEnergyCost),
            _radius(0), _lvl(0),_power(AbilitiesSettings::HealPower)
{
}

void Heal::UseAbility(Robot& main, Game& game)
{
    game.SetAbility(_abilityType);
    int cur_heal = std::min(main.GetMaxHp() - main.GetHp(),_power);
    main.AddHp(cur_heal);
    //тут AddShield(_power - cur_heal)
    game.GetPlayer().AddEnergy(-_energy_cost);
    
}

void Heal::EndAbility(const Position pos,Game& game){
    return;
}

Abilities::AbilityType Heal::GetAbilityType() const { return _abilityType;}
int Heal::GetAbilityId() const { return _Id;}
int Heal::GetAbilityLvl() const { return _lvl;}
int Heal::GetAbilityCost() const { return _energy_cost;}
void Heal::LvlUp(int value) {
    if (value <= 0 || _lvl >= AbilitiesSettings::MaxLvl) return;
    if (value >= AbilitiesSettings::MaxLvl - _lvl) {
        _lvl = AbilitiesSettings::MaxLvl;
    } else {
        _lvl += value;
    }
    if (_lvl < AbilitiesSettings::MaxLvl && _lvl > 1){
        _power += AbilitiesSettings::HealPowerDelta;
    }
}
int Heal::GetRadius() const {return _radius;}