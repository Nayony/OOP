#include "game.h"
#include "map.h"
Game::Game(int _enemy_robot_count)
    : _enemy_robot_count(_enemy_robot_count),_map(7, 7, 3),
    _player(100, 100, 240, 10, false, 3)
{
    _map.CreateGrid();
    SetRobotPos();
}

void Game::TestCells(Robot &enemy, vector<vector<Cell>> &grid,int w,int h){
    if (enemy.GetType() == true){
        for (int i = w; i > 0; --i) {
            for (int j = h; j < 0; --j) {
                if (grid[i][j].GetPassible() == false and grid[i][j].GetOccupied() == false){
                    enemy.SetPos(i,j);
                    grid[i][j].SetOccupied(true);
                    break;
                }
            }
        }
    }
    else{
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (grid[i][j].GetPassible() == false and grid[i][j].GetOccupied() == false){
                enemy.SetPos(i,j);
                grid[i][j].SetOccupied(true);
                break;
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
    Player player(100, 100, 240, 10, false,3);
    TestCells(player, _map.GetGrid(), map_size[0], map_size[1]);
}

const Map& Game::GetMap() const { return _map; }