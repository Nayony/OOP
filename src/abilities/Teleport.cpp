#include "Teleport.h"
#include <iostream>

Teleport::Teleport()
    : _abilityType(AbilityType::sTeleport), _Id(4),
      _energy_cost(AbilitiesSettings::StandartEnergyCost),
      _radius(AbilitiesSettings::TeleportRadius), _lvl(0)
{
}
Position Teleport::RandomCell(std::vector<Position> pos){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0,pos.size() - 1);
    return (pos[dist(gen)]);
}
void Teleport::UseAbility(Robot& main, Game& game)
{
    
    if (main.GetType() == true){
        game.SetCellsInRange(game.GetMap().CellsInRadius(main.GetPos(),_radius,false));
        game.SetAbility(AbilityType::sNone);
        
        auto cells = game.GetCellsInRange();
        if (!cells.empty()){
            auto pos = RandomCell(cells);
            game.MoveRobotToCell(main, pos);
            game.SetCellsInRange({});
        }
        main.AddEnergy(-_energy_cost);

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
    if (game.GetSelectedAbility() != AbilityType::sNone){
        auto& player = game.GetPlayer();
        player.AddEnergy(-_energy_cost);
        game.MoveRobotToCell(player, pos);
    }
    game.SetCellsInRange({});
    game.SetAbility(AbilityType::sNone);
    }

}

AbilityType Teleport::GetAbilityType() const { return _abilityType; }
int Teleport::GetAbilityId() const { return _Id; }
int Teleport::GetAbilityLvl() const { return _lvl; }
int Teleport::GetAbilityCost() const { return _energy_cost; }
bool Teleport::LvlUp(int value) {
    if (value <= 0 || _lvl >= AbilitiesSettings::MaxLvl) return false;
    if (value >= AbilitiesSettings::MaxLvl - _lvl) {
        _lvl = AbilitiesSettings::MaxLvl;
    } else {
        _lvl += value;
    }
    if (_lvl < AbilitiesSettings::MaxLvl && _lvl > 1){
        _energy_cost += AbilitiesSettings::TeleportEnergyCostDelta;
    }
    return true;
}
int Teleport::GetRadius() const { return _radius; }
