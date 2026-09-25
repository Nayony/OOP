#include "game.h"
#include <iostream>

Game::Game(int _enemy_robot_count)
    : _enemy_robot_count(_enemy_robot_count),_map(7, 7, 7),
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
void Game::TestCells(Robot &robot, vector<vector<Cell>> &grid,int w,int h){
    if (robot.GetType() == true){
        for (int i = w-1; i > 0; --i) {
            for (int j = h-1; j > 0; --j) {
                if (grid[i][j].GetPassible() == false and grid[i][j].GetOccupied() == false){
                    robot.SetPos(j, i);
                    grid[i][j].SetOccupied(true);
                    return;
                }
            }
        }
    }
    else{
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (grid[i][j].GetPassible() == false and grid[i][j].GetOccupied() == false){
                robot.SetPos(j, i);
                grid[i][j].SetOccupied(true);
                return;
            }
        }
    }
}
}
void Game::SetRobotPos(){
    auto map_size = _map.GetSize();
    for (int i = 0; i < _enemy_robot_count; ++i) {
        Robot enemy(100, 100, 240, 10, true);
        TestCells(enemy, _map.GetGrid(), map_size[0], map_size[1]);
        _enemy_arr.push_back(enemy);
    }

    TestCells(_player, _map.GetGrid(), map_size[0], map_size[1]);
}
bool Game::TestCellPassibility(int x, int y){
    if (x < 0 or y < 0 or x >= _map.GetSize()[0] or y >= _map.GetSize()[1]){
        return false;
    }
    if (_map.GetGrid()[y][x].GetPassible() == true or _map.GetGrid()[y][x].GetOccupied() == true){
        return false;
    }
    return true;
}
void Game::Move(Controls::keys cmd) {
    if (cmd == Controls::keys::kNone) return;

    Delta delta = DirectionDelta(cmd);
    int new_x = _player.GetPos().X() + delta.dx;
    int new_y = _player.GetPos().Y() + delta.dy;

    if (!TestCellPassibility(new_x, new_y)) return;

    _map.GetCell(_player.GetPos().X(), _player.GetPos().Y()).SetOccupied(false);
    _player.SetPos(Position(new_x, new_y));
    _map.GetCell(new_x, new_y).SetOccupied(true);
}

const Map& Game::GetMap() const { return _map; }
const Player& Game::GetPlayer() const { return _player; }
const std::vector<Robot>& Game::GetRobots() const { return _enemy_arr; }