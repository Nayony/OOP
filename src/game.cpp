#include "game.h"
#include "controls.h"
#include "position.h"

#include <iostream>

using namespace std;

Game::Game(int _enemy_robot_count)
    : _enemy_robot_count(_enemy_robot_count),
      _map(MapSettings::InitialWidth, MapSettings::InitialHeight,
           MapSettings::InitialBlockedCellCount),
      _player(PlayerSettings::MaxHp, PlayerSettings::MaxEnergy,
              PlayerSettings::XpToLevel, PlayerSettings::Damage, false,
              PlayerSettings::VisibilityRadius, PlayerSettings::MaxSpeed),
      _player_turn(true), _lose(false), _win(false),
      _factory(FactorySettings::SpawnPeriod), _turn(0),
      _selectedSpell(AbilityType::sNone) {
  if (_enemy_robot_count <= 0) {
    _win = true;
  }
  _map.CreateGrid();
  SetRobotPos();
  _map.CellsForFactory(_factory);
  _map.SetVisibleToCells(_player);
}

struct Delta {
  int dx;
  int dy;
};

Delta DirectionDelta(Controls::keys cmd) {
  switch (cmd) {
  case Controls::keys::kUp:
    return {0, -1};
  case Controls::keys::kDown:
    return {0, 1};
  case Controls::keys::kLeft:
    return {-1, 0};
  case Controls::keys::kRight:
    return {1, 0};
  default:
    return {0, 0};
  }
}
void Game::DecreaseEnemyCount() { _enemy_robot_count--; }

void Game::Kill(Robot &robot) {
  if (&robot == &_player) {
    _lose = true;
 }
  auto it = std::find_if(_enemy_arr.begin(), _enemy_arr.end(),
                         [&robot](const Robot &r) { return &r == &robot; });

  if (it != _enemy_arr.end()) {
    _map.GetCell(robot.GetPos()).SetOccupied(false);
    _player.AddXp(GameSettings::XpForKill);
    DecreaseEnemyCount();
    _enemy_arr.erase(it);
    if (_enemy_robot_count == 0) {
      _win = true;
    }
  }
}
void Game::SetRobotPos() {
  for (int i = 0; i < _enemy_robot_count; ++i) {
    Robot enemy(RobotSettings::EnemyMaxHp, RobotSettings::EnemyMaxEnergy,
                RobotSettings::EnemyXpToLevel, RobotSettings::EnemyDamage, true,
                RobotSettings::EnemyMaxSpeed);
    _map.FindFreeCell(enemy);
    GiveAbilityToRobot(enemy);
    _enemy_arr.push_back(std::move(enemy));
  }
  _map.FindFreeCell(_player);
}

Robot &Game::WhoOccupies(const Position &position) {
  if (_player.GetPos().X() == position.X() and
      _player.GetPos().Y() == position.Y()) {
    return _player;
  }
  for (Robot &robot : _enemy_arr) {
    if (robot.GetPos().X() == position.X() and
        robot.GetPos().Y() == position.Y()) {
      return robot;
    }
  }
  throw std::runtime_error("No robot here");
}

void Game::ResetTurnResources() {
  _player.ResetTurnResources();
  for (Robot &robot : _enemy_arr) {
    robot.ResetTurnResources();
  }
}
Controls::keys Game::CastToControl(const Position &player, Position &enemy){
     Delta move = {enemy.X() - player.X(),enemy.Y() - player.Y()};
    if (move.dx ==  0 and move.dy == -1){
        return Controls::keys::kUp;
    }
    else if (move.dx ==  0 and move.dy == 1){
        return Controls::keys::kDown;
    }
    else if (move.dx ==  -1 and move.dy == 0){
        return Controls::keys::kLeft;
    }
    else if (move.dx ==  0 and move.dy == 0){
        return Controls::keys::kRight;
    }
    else{
        return Controls::keys::kNone;
    }
}


bool Game::HasEnemyNeighbor(Robot &robot){
  const Position main = robot.GetPos();
  const std::vector<Position> movement_vector = {
      {1, 0}, {0, -1}, {-1, 0}, {0, 1}};
  for (const Position &direction : movement_vector) {
    const Position neighbor(main.X() + direction.X(),
                            main.Y() + direction.Y());
    if (_map.IsOccupied(neighbor) &&
        WhoOccupies(neighbor).GetType() != robot.GetType()) {
      return true;
    }
  }
  return false;
}
//Написать нормальную логику врагам(сейчас работает враги идут если есть куда и не тепаются если стоят рядом);
void Game::MoveEnemyRobots() {
  if (_player_turn)
    return;

  for (Robot &robot : _enemy_arr) {
    int attempts = 0;
    while ((robot.GetSpeed() > 0 || robot.GetEnergy() > 0) &&
           attempts < RobotSettings::MaxFailedMoveAttempts && !_lose) {
        if (!robot.GetAbilities().empty() and !HasEnemyNeighbor(robot)) {
        if (robot.GetEnergy() >=
            robot.GetAbilities()[0].get()->GetAbilityCost()) {
          if (RobotUseAbility(robot.GetAbilities()[0].get()->GetAbilityType(),
                              robot)) {
            attempts = 0;
          }
        }
      }
      auto path = _map.Dijkstra(robot.GetPos(), _player.GetPos());
      if (path.empty())
        break;
      auto move = CastToControl(robot.GetPos(), path.front());
      if (MoveRobot(robot, move)) {
        attempts = 0;
      } else {
        ++attempts;
      }
    }
  }
  EndTurn();
}
bool Game::KillMarked() {
  bool win = false;
  auto it = _enemy_arr.begin();

  while (it != _enemy_arr.end()) {
    Robot &robot = *it;
    if (robot.GetDemise()) {
      _map.GetCell(robot.GetPos()).SetOccupied(false);
      _player.AddXp(GameSettings::XpForKill);
      DecreaseEnemyCount();
      if (_enemy_robot_count == 0) {
        _win = true;
        win = true;
      }
      it = _enemy_arr.erase(it);

    } else {
      ++it;
    }
  }
  return win;
}

void Game::ActivateStatuses(Robot &robot) {

  vector<StatusType> statuses_;
  for (auto &status : robot.GetStatuses()) {
    if (status->ApplyStatus(robot, *this)) {
      statuses_.push_back(status->GetStatusType());
    }
  }
  for (auto status : statuses_) {
    robot.EraseStatus(status);
  }
}
void Game::EndTurn() {
  if (_player_turn == false) {
    _player_turn = true;
    ResetTurnResources();
    FactoryTrySpawn(_turn);
    ActivateStatuses(_player);
  } else {
    for (auto &robot : _enemy_arr) {
      ActivateStatuses(robot);
    }
    if (!KillMarked()) {
      _turn += 1;
      _player_turn = false;
      MoveEnemyRobots();
    }
  }
}
void Game::Pass() {
  if (!_player_turn || _win || _lose)
    return;
  ClearSelection();
  EndTurn();
}
void Game::FactoryTrySpawn(int turn) {
  int y;
  int x;
  if (turn % _factory.GetSpawnPeriod() == 0 && _enemy_arr.size() < 10) {
    y = _factory.GetPosMain().Y();
    x = _factory.GetPosMain().X();
    if (auto pos = _map.FindFreeNear(_factory)) {
      Robot enemy(RobotSettings::EnemyMaxHp, RobotSettings::EnemyMaxEnergy,
                  RobotSettings::EnemyXpToLevel, RobotSettings::EnemyDamage,
                  true, RobotSettings::EnemyMaxSpeed);
      enemy.SetPos(*pos);
      _map.GetCell(*pos).SetOccupied(true);
      _enemy_robot_count += 1;
      GiveAbilityToRobot(enemy);
      _enemy_arr.push_back(std::move(enemy));
    }
  }
}
void Game::Move(Controls::keys cmd) {
  if (!_player_turn || _win || _lose)
    return;
  if (MoveRobot(_player, cmd)) {
    ClearSelection();
    if (_win || _lose)
      return;
    if (_player.GetEnergy() <= 0 && _player.GetSpeed() <= 0) {
      Pass();
    }
  }
}
bool CalculateRobotSpeed(Robot &robot, const Cell &cell) {
    
  const int cost = cell.GetCost();
  if (cost == -1 || robot.GetSpeed() < cost) {
    return false;
  }

  robot.AddSpeed(-cost);

  return true;
}

void Game::GiveAbilityToRobot(Robot &robot) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 1);
  int num = distr(gen);
  auto type = (num == 0) ? AbilityType::sHeal : AbilityType::sTeleport;
  switch (type) {
  case AbilityType::sHeal:
    robot.AddAbility(std::make_unique<Heal>());
    break;
  case AbilityType::sTeleport:
    robot.AddAbility(std::make_unique<Teleport>());
    break;
  default:
    return;
    break;
  }
}
void Game::GiveAbilityToPlayer(AbilityType type) {
  if (!_player.HasAbilityPoint())
    return;
  auto ability = _player.FindAbility(type);
  if (ability == nullptr) {
    switch (type) {
    case AbilityType::sAroundHit:
      _player.AddAbility(std::make_unique<AroundHit>());
      break;
    case AbilityType::sFarHit:
      _player.AddAbility(std::make_unique<FarHit>());
      break;
    case AbilityType::sHeal:
      _player.AddAbility(std::make_unique<Heal>());
      break;
    case AbilityType::sTeleport:
      _player.AddAbility(std::make_unique<Teleport>());
      break;
    default:
      return;
      break;
    }
  }
  ability = _player.FindAbility(type);
  if (ability && ability->LvlUp(1)) {
    _player.AddAbilityPoint(-1);
  }
}

bool Game::RobotUseAbility(AbilityType type, Robot &robot) {

  auto ability = robot.FindAbility(type);
  if (ability == nullptr) {
    return false;
  }
  if (robot.GetEnergy() >= ability->GetAbilityCost()) {
    if (robot.CanUseAbility() == true) {
      if (ability->GetAbilityType() == AbilityType::sHeal) {
        if (robot.GetHp() < robot.GetMaxHp() / 2) {
          ability->UseAbility(robot, *this);
          return true;
        }
      }
      if (ability->GetAbilityType() == AbilityType::sTeleport) {
        ability->UseAbility(robot, *this);
        return true;
      }
    } else {
      robot.AddEnergy(-ability->GetAbilityCost());
      robot.SetCanUseAbility(true);
      robot.EraseStatus(StatusType::sOverload);
      return true;
    }
  }
  return false;
}
void Game::PlayerUseAbility(AbilityType type) {
  auto ability = _player.FindAbility(type);
  if (ability == nullptr) {
    return;
  }
  if (_player.GetEnergy() >= ability->GetAbilityCost()) {
    if (_player.CanUseAbility() == true) {
      ability->UseAbility(_player, *this);
      if (_player.GetEnergy() <= 0 && _player.GetSpeed() <= 0) {
        Pass();
      }
    } else {
      _player.AddEnergy(-ability->GetAbilityCost());
      _player.SetCanUseAbility(true);
      _player.EraseStatus(StatusType::sOverload);
    }
  }
}

bool Game::MoveRobot(Robot &robot, Controls::keys cmd) {
  if (cmd == Controls::keys::kNone)
    return false;
  Delta delta = DirectionDelta(cmd);
  if (delta.dx == 0 && delta.dy == 0)
    return false;
  const Position current_position = robot.GetPos();
  const Position new_position(current_position.X() + delta.dx,
                              current_position.Y() + delta.dy);

  if (!_map.IsFree(new_position))
    return false;
  if (_map.IsOccupied(new_position)) {

    if (robot.GetEnergy() <= 0)
      return false;
    auto &other_robot = WhoOccupies(new_position);
    interaction(robot, other_robot);
    robot.AddEnergy(-1);
    return true;
  } else {
    if (!CalculateRobotSpeed(robot, _map.GetCell(new_position))) {
      return false;
    }
    MoveRobotToCell(robot, new_position);
    return true;
  }
}

void Game::ApplyStatus(StatusType statusType, Robot &robot) {
  auto status = robot.FindStatus(statusType);
  if (status != nullptr) {
    status->OnReapply(robot, *this);
    return;
  }
  switch (statusType) {
  case StatusType::sBurn:
    robot.AddStatus(std::make_unique<Burn>());
    break;
  case StatusType::sShield:
    robot.AddStatus(std::make_unique<Shield>());
    break;
  case StatusType::sSlowth:
    robot.AddStatus(std::make_unique<Slowth>());
    break;
  case StatusType::sOverload:
    robot.AddStatus(std::make_unique<Overload>());
    break;

  default:
    return;
  }
  robot.FindStatus(statusType)->OnApply(robot, *this);
}
void Game::ApplyStatusOnCell(Position pos, Robot &robot) {
  Cell &cell = _map.GetCell(pos);
  for (StatusType statusType : cell.GetStatuses()) {
    ApplyStatus(statusType, robot);
    cell.EraseStatus(statusType);
    break;
  }
}
void Game::MoveRobotToCell(Robot &robot, const Position &position) {
  if (robot.CanMove() == true) {
    _map.GetCell(robot.GetPos()).SetOccupied(false);
    robot.SetPos(position);
    _map.GetCell(position).SetOccupied(true);
    ApplyStatusOnCell(position, robot);
  }
  if (robot.GetType() == false)
    _map.SetVisibleToCells(_player);
}

bool Game::DealDamage(Robot &target, int damage, bool safe) {
  if (damage < 0)
    target.AddHp(-damage);
  else {
    int RealDamage = target.GetShield() - damage;
    if (RealDamage <= 0) {
      target.AddShield(-damage);
      target.AddHp(RealDamage);
    } else {
      target.AddShield(-damage);
    }
  }
  if (target.GetHp() <= 0) {
    if (!safe) {
      Kill(target);
    } else {
      target.SetDemise(true);
    }
    return false;
  }
  return true;
}
bool Game::interaction(Robot &main, Robot &other) {
  if (main.GetType() != other.GetType()) {
    if (!DealDamage(other, main.GetDamage()))
      return false;
  } else {
    if (main.GetDamage() > 0) {
      DealDamage(other, -main.GetDamage());
    }
  }
  return true;
}

void Game::SetAbility(AbilityType type) { _selectedSpell = type; }
void Game::SetCellsInRange(std::vector<Position> cells) {
  _cells_in_range = cells;
}

void Game::ClearSelection() {
  SetCellsInRange({});
  SetAbility(AbilityType::sNone);
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

const Map &Game::GetMap() const { return _map; }
Map &Game::GetMap() { return _map; }
Player &Game::GetPlayer() { return _player; }
const Player &Game::GetPlayer() const { return _player; }
const std::vector<Robot> &Game::GetRobots() const { return _enemy_arr; }
const AbilityType Game::GetSelectedAbility() const { return _selectedSpell; }
const std::vector<Position> Game::GetCellsInRange() const {
  return _cells_in_range;
}
