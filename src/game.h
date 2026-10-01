
#ifndef GAME
#define GAME

#include "map.h"
#include "player.h"
#include "factory.h"
#include <vector>
#include "controls.h"
#include <algorithm>
#include <random>


class Game{
    private:
        int _enemy_robot_count;
        int _turn;
        Map _map;
        std::vector<Robot> _enemy_arr;
        Player _player;
        Factory _factory;
        bool _player_turn;
        bool _win;
        bool _lose;
        bool MoveRobot(Robot& robot, Controls::keys cmd);
    public:
        Game(int _enemy_robot_count);
        void SetRobotPos();
        const Map& GetMap() const;
        const Player& GetPlayer() const;
        const std::vector<Robot>& GetRobots() const;
        void Move(Controls::keys cmd);
        bool interaction(Robot &main, Robot &other);
        Robot& WhoOccupies(const Position& position); //todo в map
        void DecreaseEnemyCount();
        void Kill(Robot& robot);
        void ResetEnergy();
        Controls::keys RandomDirection();
        void MoveEnemyRobots();
        void Pass();
        std::string GetGameState() const;
        void FactoryTrySpawn(int turn);
        void EndTurn();
};
    

#endif
