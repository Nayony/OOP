
#ifndef GAME
#define GAME

#include "map.h"
#include "robot.h"
#include "player.h"
#include <vector>
#include "controls.h"
#include <algorithm>
#include <random>


class Game{
    protected:
        int _enemy_robot_count;
        Map _map;
        std::vector<Robot> _enemy_arr;
        Player _player;
    private:
        bool MoveRobot(Robot& robot, Controls::keys cmd);
    public:
        Game(int _enemy_robot_count);
        void SetRobotPos();
        const Map& GetMap() const;
        const Player& GetPlayer() const;
        const std::vector<Robot>& GetRobots() const;
        void Move(Controls::keys cmd);
        bool interaction(Robot main, Robot &other);
        Robot& WhoOccupies(const Position& position);
        void Kill(Robot& robot);
        void RandomMove(Robot& robot);
        void MoveEnemyRobots();
};
    

#endif
