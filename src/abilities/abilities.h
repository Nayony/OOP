#ifndef abilities
#define abilities

#include "../constants.h"
#include <vector>
class Robot;
class Game;
class Position;

enum class AbilityType {
    sAroundHit,
    sFarHit,    
    sHeal,
    sTeleport,
    sInfoCatalog,
    sNone
};

class Abilities{

public:
virtual void UseAbility(Robot &robot, Game &game) = 0;
virtual void EndAbility(const Position pos,Game& game) = 0;
virtual ~Abilities() = default;
virtual bool LvlUp(int value) = 0;
virtual AbilityType GetAbilityType() const = 0;
virtual int GetAbilityId() const = 0;
virtual int GetAbilityLvl() const = 0;
virtual int GetAbilityCost() const = 0;



};
#endif
