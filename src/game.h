
#ifndef GAME
#define GAME

#include "map.h"
#include "robot.h"
#include "player.h"
#include "cell.h"
#include <vector>
#include "controls.h"

class Game{
    protected:
        int _enemy_robot_count;
        Map _map;
        std::vector<Robot> _enemy_arr;
        Player _player;
    public:
        Game(int _enemy_robot_count);
        void SetRobotPos();
        void TestCells(Robot &enemy, std::vector<std::vector<Cell>> &grid, int w, int h);
        const Map& GetMap() const;
        const Player& GetPlayer() const;
        const std::vector<Robot>& GetRobots() const;
        void Move(Controls::keys cmd);
        bool TestCellPassibility(int x, int y);
};
    

#endif