
#ifndef GAME
#define GAME

#include "map.h"
#include "player.h"
#include "factory.h"
#include "controls.h"
#include "abilities/AroundHit.h"
#include "abilities/FarHit.h"
#include "abilities/Heal.h"
#include "abilities/Teleport.h"
#include "statuses/Burn.h"
#include "statuses/Slowth.h"
#include "statuses/Shield.h"
#include "statuses/Overload.h"
#include <algorithm>
#include <vector>
#include <random>
#include "constants.h"


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
        AbilityType _selectedSpell;
        bool MoveRobot(Robot& robot, Controls::keys cmd);
        std::vector<Position> _cells_in_range;
        
        
    public:
        Game(int _enemy_robot_count);
        void SetRobotPos();
        const Map& GetMap() const;
        Map& GetMap();
        Player& GetPlayer();
        const Player& GetPlayer() const;
        const std::vector<Robot>& GetRobots() const;
        void Move(Controls::keys cmd);
        void MoveRobotToCell(Robot& robot, const Position& position);
        void ClearSelection();
        bool interaction(Robot& main,Robot &other);
        bool DealDamage(Robot& target,int damage,bool safe = false);
        Robot& WhoOccupies(const Position& position);
        bool RobotUseAbility(AbilityType type,Robot &robot);
        void PlayerUseAbility(AbilityType type);
        void DecreaseEnemyCount();
        void Kill(Robot& robot);
        void ResetTurnResources();
        Controls::keys RandomDirection();
        void MoveEnemyRobots();
        void Pass();
        std::string GetGameState() const;
        void FactoryTrySpawn(int turn);
        void EndTurn();
        void GiveAbilityToPlayer(AbilityType type);
        void GiveAbilityToRobot(Robot &robot);
        void SetAbility(AbilityType type);
        const AbilityType GetSelectedAbility() const;
        const std::vector<Position> GetCellsInRange() const;
        void SetCellsInRange(std::vector<Position> cells);
        void ApplyStatusOnCell(Position pos,Robot& robot);
        void ApplyStatus(StatusType status,Robot& robot);
        void ActivateStatuses(Robot &robot);
        bool KillMarked();
};
    

#endif
