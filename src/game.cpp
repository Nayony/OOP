#include "game.h"


#include <iostream>

using namespace std;

Game::Game(int _enemy_robot_count)
        : _enemy_robot_count(_enemy_robot_count),
            _map(MapSettings::InitialWidth, MapSettings::InitialHeight, MapSettings::InitialBlockedCellCount),
            _player(PlayerSettings::MaxHp, PlayerSettings::MaxEnergy, PlayerSettings::XpToLevel,
                            PlayerSettings::Damage, false, PlayerSettings::VisibilityRadius, PlayerSettings::MaxSpeed),
            _player_turn(true), _lose(false), _win(false), _factory(FactorySettings::SpawnPeriod), _turn(0),_selectedSpell(Abilities::AbilityType::sNone)
{
    if(_enemy_robot_count <= 0){
        _win = true;
    }
    _map.CreateGrid();
    SetRobotPos();
    _map.CellsForFactory(_factory);
    _map.SetVisibleToCells(_player);
}

struct Delta { int dx; int dy; };

Delta DirectionDelta(Controls::keys cmd) {
    switch (cmd) {
        case Controls::keys::kUp:    return {0, -1};
        case Controls::keys::kDown:  return {0, 1};
        case Controls::keys::kLeft:  return {-1, 0};
        case Controls::keys::kRight: return {1, 0};
        default:                     return {0, 0};
    }
}

void Game::DecreaseEnemyCount(){
    _enemy_robot_count--;
}

void Game::Kill(Robot& robot) {
    if (&robot == &_player) {
        _lose = true;
    }
    auto it = std::find_if(_enemy_arr.begin(), _enemy_arr.end(),
                            [&robot](const Robot& r) { return &r == &robot; });

    if (it != _enemy_arr.end()) {
        _map.GetCell(robot.GetPos()).SetOccupied(false);
        DecreaseEnemyCount();
        _enemy_arr.erase(it);
        if (_enemy_robot_count == 0) {
            _win = true;
        }
    }

}
void Game::SetRobotPos(){
    for (int i = 0; i < _enemy_robot_count; ++i) {
        Robot enemy(RobotSettings::EnemyMaxHp, RobotSettings::EnemyMaxEnergy,
                RobotSettings::EnemyXpToLevel, RobotSettings::EnemyDamage, true,
                RobotSettings::EnemyMaxSpeed);
        _map.FindFreeCell(enemy);
        _enemy_arr.push_back(std::move(enemy));
    }
    _map.FindFreeCell(_player);
}

Robot& Game::WhoOccupies(const Position& position){
    if (_player.GetPos().X() == position.X() and _player.GetPos().Y() == position.Y()){
        return _player;
    }
    for (Robot& robot : _enemy_arr){
        if (robot.GetPos().X() == position.X() and robot.GetPos().Y() == position.Y()){
            return robot;
        }
    }
    throw std::runtime_error("No robot here");
}

Controls::keys Game::RandomDirection() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(Controls::keys::kDown));
    return static_cast<Controls::keys>(dist(gen));
}
void Game::ResetTurnResources(){
    _player.ResetTurnResources();
    for (Robot& robot : _enemy_arr) {
        robot.ResetTurnResources();
    }
}
void Game::MoveEnemyRobots(){
    if (_player_turn) return;

    for (Robot& robot : _enemy_arr) {
        int attempts = 0;
        while (robot.GetEnergy() > 0 && attempts < RobotSettings::MaxFailedMoveAttempts && !_lose) {
            if (MoveRobot(robot, RandomDirection())) {
                attempts = 0;
            }
            else {
                ++attempts;
            }
        }
    }
    EndTurn();

}
void Game::EndTurn(){
    if (_player_turn == false){
        _player_turn = true;
        ResetTurnResources();
        FactoryTrySpawn(_turn);
    }
    else{
        _turn += 1;
        _player_turn = false;
        MoveEnemyRobots(); 
    }
}
void Game::Pass(){
    if (!_player_turn || _win || _lose) return;
    EndTurn();

}
void Game::FactoryTrySpawn(int turn){
    int y;
    int x;
    if (turn%_factory.GetSpawnPeriod() == 0){
        y = _factory.GetPosMain().Y();
        x = _factory.GetPosMain().X();
        if (auto pos = _map.FindFreeNear(_factory)) {
        Robot enemy(RobotSettings::EnemyMaxHp, RobotSettings::EnemyMaxEnergy,
                RobotSettings::EnemyXpToLevel, RobotSettings::EnemyDamage, true,
                RobotSettings::EnemyMaxSpeed);
        enemy.SetPos(*pos);
        _map.GetCell(*pos).SetOccupied(true);
        _enemy_robot_count += 1;
        _enemy_arr.push_back(std::move(enemy));
        }
    }
}
void Game::Move(Controls::keys cmd) {
    if (!_player_turn || _win || _lose) return;
    if (MoveRobot(_player, cmd)) {
        SetCellsInRange({});
		SetAbility(Abilities::AbilityType::sNone);
        if (_win || _lose) return;
        if (_player.GetEnergy() <= 0) {
            Pass();
        }
    }
}
bool CalculateRobotSpeed(Robot& robot,const Cell& cell){
    const int cost = cell.GetCost();
    if (cost == -1 || robot.GetSpeed() < cost) {
        return false;
    }

    robot.AddSpeed(-cost);
    if (robot.GetSpeed() == 0) {
        robot.ResetSpeed();
        robot.AddEnergy(-1);
    }

    return true;
}



void GiveAbilityToRobot(Abilities::AbilityType type,Robot &robot){
    
}
void Game::GiveAbilityToPlayer(Abilities::AbilityType type){
    if (!_player.HasAbilityPoint()) return;
    auto ability = _player.FindAbility(type);
    if (ability == nullptr){
        switch (type)
        {
        case Abilities::AbilityType::sAroundHit:
            _player.AddAbility(std::make_unique<AroundHit>());
            break;
        case Abilities::AbilityType::sFarHit:
            _player.AddAbility(std::make_unique<FarHit>());
            break;
        case Abilities::AbilityType::sHeal:
            _player.AddAbility(std::make_unique<Heal>());
            break;
        case Abilities::AbilityType::sTeleport:
            _player.AddAbility(std::make_unique<Teleport>());
            break;
        default:
            return;
            break;

        }
    }
    _player.AddAbilityPoint(-1);
    ability = _player.FindAbility(type);
    ability->LvlUp(1);
}

void Game::RobotUseAbility(Abilities::AbilityType  type,Robot &robot){
    
    auto ability = robot.FindAbility(type);
    if (ability == nullptr) {
        return;
    }
    if (robot.GetEnergy() >= ability->GetAbilityCost()){
        robot.AddEnergy(-1);
        ability->UseAbility(robot, *this);
    }
    
}
void Game::PlayerUseAbility(Abilities::AbilityType type){
    auto ability = _player.FindAbility(type);
    if (ability == nullptr) {
        return;
    }
    if (_player.GetEnergy() >= ability->GetAbilityCost()){
        ability->UseAbility(_player, *this);
    }

}

bool Game::MoveRobot(Robot& robot, Controls::keys cmd) {
    if (cmd == Controls::keys::kNone) return false;
    Delta delta = DirectionDelta(cmd);
    if (delta.dx == 0 && delta.dy == 0) return false;
    const Position current_position = robot.GetPos();
    const Position new_position(current_position.X() + delta.dx, current_position.Y() + delta.dy);

    if (!_map.IsFree(new_position)) return false;
    if (_map.IsOccupied(new_position)){

        auto& other_robot = WhoOccupies(new_position);
        interaction(robot, other_robot);
        robot.AddEnergy(-1);
        return true;
    }
    else{
        if (!CalculateRobotSpeed(robot, _map.GetCell(new_position))) {
            return false;
        }
        MoveRobotToCell(robot, new_position);
        return true;
    }
}
void Game::MoveRobotToCell(Robot& robot, const Position& position) {
    _map.GetCell(robot.GetPos()).SetOccupied(false);
    robot.SetPos(position);
    _map.GetCell(position).SetOccupied(true);
    if (robot.GetType() == false) _map.SetVisibleToCells(_player);
}
bool Game::interaction(Robot& main,Robot &other){
    if (main.GetType() != other.GetType()){
        other.AddHp(-main.GetDamage());
        if (other.GetHp() <= 0){
            main.AddXp(GameSettings::XpForKill);
            Kill(other);
            return false;
        }
    }
    else{
        if (main.GetDamage() > 0){
            other.AddHp(main.GetDamage());
        }
    }
    return true;
}

void Game::SetAbility(Abilities::AbilityType type){
        _selectedSpell = type;
}
void Game::SetCellsInRange(std::vector<Position> cells){
        _cells_in_range = cells;
}

std::string Game::GetGameState() const {
    if (_win) {
        return "Win";
    }
    if (_lose) {
        return "Lose";
    }
    return "Playing";
}


const Map& Game::GetMap() const { return _map; }
Map& Game::GetMap() { return _map; }
Player& Game::GetPlayer() { return _player; }
const Player& Game::GetPlayer() const { return _player; }
const std::vector<Robot>& Game::GetRobots() const { return _enemy_arr; }
const Abilities::AbilityType Game::GetSelectedAbility() const { return _selectedSpell; }
const std::vector<Position> Game::GetCellsInRange() const { return _cells_in_range; }
