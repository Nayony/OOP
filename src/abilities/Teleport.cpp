#include "Teleport.h"
#include <iostream>

Teleport::Teleport()
    : _abilityType(AbilityType::sTeleport), _Id(4),
      _energy_cost(AbilitiesSettings::StandartEnergyCost),
      _radius(AbilitiesSettings::TeleportRadius), _lvl(0)
{
}

void Teleport::UseAbility(Robot& main, Game& game)
{
    
    if (main.GetType() == true){
        game.SetCellsInRange(game.GetMap().CellsInRadius(main.GetPos(),AbilitiesSettings::TeleportRadius,false));
        main.AddEnergy(_energy_cost);
        game.SetAbility(Abilities::AbilityType::sNone);

        //auto pos = random pos;
        // if (game.GetMap().IsOccupied(pos)){
        // if (game.GetSelectedAbility() != Abilities::AbilityType::sNone){
        //     auto& player = game.GetPlayer();
            
        //     game.GetMap().GetCell(player.GetPos()).SetOccupied(false);
        //     player.AddEnergy(-_energy_cost);
        //     player.SetPos(pos);
        //     game.GetMap().GetCell(pos).SetOccupied(true);
        // }
        // game.SetCellsInRange({});
        // game.SetAbility(Abilities::AbilityType::sNone);
        // }
    }
    else{
        game.SetCellsInRange(game.GetMap().CellsInRadius(main.GetPos(),_radius,false));
        game.SetAbility(_abilityType);
    }
}

void Teleport::EndAbility(const Position pos, Game& game)
{
    bool found = false;
    for (auto& cell: game.GetCellsInRange()){
        if (cell == pos) {
            found = true; 
            break;
        }
    }
    if (!game.GetMap().IsOccupied(pos)&& found){
    if (game.GetSelectedAbility() != Abilities::AbilityType::sNone){
        auto& player = game.GetPlayer();
        player.AddEnergy(-_energy_cost);
        game.MoveRobotToCell(player, pos);
    }
    game.SetCellsInRange({});
    game.SetAbility(Abilities::AbilityType::sNone);
    }

}

Abilities::AbilityType Teleport::GetAbilityType() const { return _abilityType; }
int Teleport::GetAbilityId() const { return _Id; }
int Teleport::GetAbilityLvl() const { return _lvl; }
int Teleport::GetAbilityCost() const { return _energy_cost; }
void Teleport::LvlUp(int value) {
    if (value <= 0 || _lvl >= AbilitiesSettings::MaxLvl) return;
    if (value >= AbilitiesSettings::MaxLvl - _lvl) {
        _lvl = AbilitiesSettings::MaxLvl;
    } else {
        _lvl += value;
    }
    if (_lvl < AbilitiesSettings::MaxLvl && _lvl > 1){
        _energy_cost += AbilitiesSettings::TeleportEnergyCostDelta;
    }
}
int Teleport::GetRadius() const { return _radius; }
