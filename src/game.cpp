#include "game.h"
#include <iostream>
Game::Game(int _enemy_robot_count)
    : _enemy_robot_count(_enemy_robot_count),_map(12, 12, 10),
    _player(8, 2, 240, 10, false, 3),_player_turn(true), _lose(false), _win(false)
{
    _map.CreateGrid();
    _map.SetVisibleToCells(_player);
    SetRobotPos();
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
        Robot enemy(10, 1, 240, 4, true);
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
Controls::keys RandomDirection() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(Controls::kDown));
    return static_cast<Controls::keys>(dist(gen));
}
void Game::ResetEnergy(){
    _player.SetEnergy(-1);
    for (Robot& robot : _enemy_arr) {
        robot.SetEnergy(-1);
    }
}
void Game::MoveEnemyRobots(){
    int index = _enemy_robot_count;
    while (index > 0){
    if (!_player_turn){
    for (Robot& robot : _enemy_arr) {
        for (int attempts = 0; attempts < 4; ++attempts) {
            if (MoveRobot(robot, RandomDirection())) {
                robot.SetEnergy(robot.GetEnergy() - 1);
                if (robot.GetEnergy() <= 0){
                    index--;
                    if (index == 0) {
                        ResetEnergy();
                        _player_turn = true;
                        break;
                    }
                    
                }
                break;
            }
        }
    }
}
    }
}
void Game::Move(Controls::keys cmd) {
    if (_player_turn){
    if (MoveRobot(_player, cmd)){
        _map.SetVisibleToCells(_player);
        _player.SetEnergy(_player.GetEnergy() - 1);
        if (_player.GetEnergy()<=0){
            _player_turn = false;
            MoveEnemyRobots();
        }
    }
}
}

bool Game::MoveRobot(Robot& robot, Controls::keys cmd) {
    if (cmd == Controls::keys::kNone) return false;

    Delta delta = DirectionDelta(cmd);
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
        _map.GetCell(current_position).SetOccupied(false);
        robot.SetPos(new_position);
        _map.GetCell(new_position).SetOccupied(true);
        return true;
    }
}
bool Game::interaction(Robot main,Robot &other){
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
