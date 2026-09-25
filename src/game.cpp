#include "game.h"

Game::Game(int _enemy_robot_count)
    : _enemy_robot_count(_enemy_robot_count),_map(15, 15, 10),
    _player(100, 100, 240, 10, false, 3)
{
    _map.CreateGrid();
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
void Game::Kill(Robot& robot) {
    if (&robot == &_player) {
        throw std::runtime_error("Player has been killed!"); // тут сделать нормальную логику
    }
    auto it = std::find_if(_enemy_arr.begin(), _enemy_arr.end(),
                            [&robot](const Robot& r) { return &r == &robot; }); //Еще раз разобраться с этим

    if (it != _enemy_arr.end()) {
        _enemy_arr.erase(it);
    }

}
void Game::SetRobotPos(){
    for (int i = 0; i < _enemy_robot_count; ++i) {
        Robot enemy(10, 10, 240, 10, true);
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
void Game::MoveEnemyRobots(){
    for (Robot& robot : _enemy_arr) {
        for (int attempts = 0; attempts < 4; ++attempts) {
            if (MoveRobot(robot, RandomDirection())) {
                break;
            }
        }
    }
}
void Game::Move(Controls::keys cmd) {
    MoveRobot(_player, cmd);
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

const Map& Game::GetMap() const { return _map; }
const Player& Game::GetPlayer() const { return _player; }
const std::vector<Robot>& Game::GetRobots() const { return _enemy_arr; }
