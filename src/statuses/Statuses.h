#ifndef statuses
#define statuses

#include "../constants.h"
class Robot;
class Game;

enum class StatusType{
    sSlowth,
    sBurn,
    sOverload,
    sShield,
    sNone
};

class Statuses{
    
public:
    virtual ~Statuses() = default;
    virtual void OnApply(Robot& robot, Game& game) = 0;
    virtual bool ApplyStatus(Robot &robot,Game &game) = 0;
    virtual void OnReapply(Robot& robot, Game& game) = 0;
    virtual StatusType GetStatusType() const = 0;
    virtual int GetStatusEndurance() const = 0;
    virtual bool DecreaseEffect() = 0;


};
#endif
