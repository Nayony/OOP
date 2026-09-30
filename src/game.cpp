#include "game.h"
#include <iostream>
Game::Game(int _enemy_robot_count)
    : _enemy_robot_count(_enemy_robot_count),_map(12, 12, 10),
    _player(8, 2, 240, 10, false, 333,2),_player_turn(true), _lose(false), _win(false), _factory(), _turn(0)
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
//debug
// static const char* DirName(Controls::keys cmd) {
//     switch (cmd) {
//         case Controls::keys::kUp:    return "Up";
//         case Controls::keys::kDown:  return "Down";
//         case Controls::keys::kLeft:  return "Left";
//         case Controls::keys::kRight: return "Right";
//         case Controls::keys::kNone:  return "None";
//         default:                     return "Other";
//     }
// }
void Game::DecreaseEnemyCount(){
    _enemy_robot_count--;
}

void Game::Kill(Robot& robot) {
    if (&robot == &_player) {
        _lose = true;
    }
    auto it = std::find_if(_enemy_arr.begin(), _enemy_arr.end(),
                            [&robot](const Robot& r) { return &r == &robot; }); //Еще раз разобраться с этим

    if (it != _enemy_arr.end()) {
        DecreaseEnemyCount();
        _enemy_arr.erase(it);
        if (_enemy_robot_count == 0) {
            _win = true;
        }
    }

}
void Game::SetRobotPos(){
    for (int i = 0; i < _enemy_robot_count; ++i) {
        Robot enemy(10, 1, 240, 4, true,3);
        _map.FindFreeCell(enemy);
        _enemy_arr.push_back(enemy);
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
void Game::ResetEnergy(){
    _player.SetEnergy(-1);
    _player.SetSpeed(-1);
    for (Robot& robot : _enemy_arr) {
        robot.SetEnergy(-1);
        robot.SetSpeed(-1);
    }
}
void Game::MoveEnemyRobots(){
    if (_player_turn) return;

    for (Robot& robot : _enemy_arr) {
        int attempts = 0;
        while (robot.GetEnergy() > 0 && attempts < 10 && !_lose) {
            if (MoveRobot(robot, RandomDirection())) {
                attempts = 0;
            }
            else {
                ++attempts;
            }
        }
    }
    //cout << "###" << "\n";
    EndTurn();

}
void Game::EndTurn(){
    if (_player_turn == false){
        _player_turn = true;
    }
    else{
        _player_turn = false;
        MoveEnemyRobots();
    }
    ResetEnergy();
    _turn+= 1;
    FactoryTrySpawn(_turn);
}
void Game::Pass(){
    if (!_player_turn || _win || _lose) return;
    EndTurn();

}
void Game::FactoryTrySpawn(int turn){
    int y;
    int x;
    if (turn%10 == 0){
        y = _factory.GetPosMain().Y();
        x = _factory.GetPosMain().X();
        Robot enemy(10, 1, 240, 4, true,3);
        //todo Тут не хватает проверки на то что клетке свободна
        _map.GetCell({x+1,y}).SetOccupied(true);
        enemy.SetPos({x+1,y});
        _enemy_robot_count += 1;
        _enemy_arr.push_back(enemy);
    }
}
void Game::Move(Controls::keys cmd) {
    if (!_player_turn || _win || _lose) return;
    if (MoveRobot(_player, cmd)) {
        _map.SetVisibleToCells(_player);
        if (_win || _lose) return;
        if (_player.GetEnergy() <= 0) {
            Pass();
        }
    }
}

bool CalculateRobotSpeed(Robot& robot,const Cell& cell){
    const int cost = cell.GetCost();
    if (robot.GetSpeed() < cost) {
        return false;
    }

    robot.SetSpeed(robot.GetSpeed() - cost);
    if (robot.GetSpeed() == 0) {
        robot.SetSpeed(-1);
        robot.SetEnergy(robot.GetEnergy() - 1);
    }

    return true;
}


bool Game::MoveRobot(Robot& robot, Controls::keys cmd) {
    //if (robot.GetType() != _player.GetType()) {std::cout << "cmd: " << DirName(cmd) << "\n";}
    
    if (cmd == Controls::keys::kNone) return false;
    Delta delta = DirectionDelta(cmd);
    if (delta.dx == 0 && delta.dy == 0) return false;
    const Position current_position = robot.GetPos();
    const Position new_position(current_position.X() + delta.dx, current_position.Y() + delta.dy);

    if (!_map.IsFree(new_position)) return false;
    if (_map.IsOccupied(new_position)){

        auto& other_robot = WhoOccupies(new_position);
        if (!interaction(robot, other_robot)) {
            robot.SetXp(80);
            Kill(other_robot);
            _map.GetCell(new_position).SetOccupied(false);
        }
        return true;
    }
    else{
        if (!CalculateRobotSpeed(robot, _map.GetCell(new_position))) {
            return false;
        }
        _map.GetCell(current_position).SetOccupied(false);
        robot.SetPos(new_position);
        _map.GetCell(new_position).SetOccupied(true);
        return true;
    }
}
bool Game::interaction(Robot& main,Robot &other){
    main.SetEnergy(main.GetEnergy() - 1);
    if (main.GetType() != other.GetType()){
        other.SetHp(other.GetHp() - main.GetDamage());
        if (other.GetHp() <= 0){
            return false;
        }
    }
    else{
        if (main.GetDamage() > 0){
            other.SetHp(other.GetHp() + main.GetDamage());
        }
    }
    return true;
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
const Player& Game::GetPlayer() const { return _player; }
const std::vector<Robot>& Game::GetRobots() const { return _enemy_arr; }