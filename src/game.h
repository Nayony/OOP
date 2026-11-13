
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
#include "time/timer_manager.h"

enum class EventType
{
    kDamageFlash,
    AroundHit,
};
struct VisualEvent
{
    EventType type;
    int robotId;
    int timerId;

    VisualSettings::Rgba startColor;
    VisualSettings::Rgba targetColor;
};
class Game{
    private:
        int _enemy_robot_count;
        int _turn;
        TimerManager _timer_manager;
        Map _map;
        std::vector<Robot> _enemy_arr;
        Player _player;
        Factory _factory;
        bool _player_turn;
        bool _win;
        bool _lose;
        AbilityType _selectedSpell;
        bool MoveRobot(Robot& robot, Controls::keys cmd);
        int FindFreeRobotId() const;
        std::vector<Position> _cells_in_range;
        std::vector<VisualEvent> _events;
        
        
        
    public:
        Game(int _enemy_robot_count);
        VisualEvent CreateVisualEvent(EventType type, int robotId = -1, float timerDuration= -1,
                VisualSettings::Rgba startColor = VisualSettings::TransparentColor,
                VisualSettings::Rgba endColor = VisualSettings::TransparentColor);
        void SetRobotPos();
        const Map& GetMap() const;
        Map& GetMap();
        const std::vector<VisualEvent>& GetEvents() const;
        const VisualEvent* FindEvent(EventType type) const;
        Player& GetPlayer();
        const Player& GetPlayer() const;
        const TimerManager& GetTimerManager() const;
        void UpdateVisualEvents();
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
