#include "Burn.h"


Burn::Burn()
    : _type(StatusType::sBurn), _duration(StatusesSettings::BurnDuration), _damage(StatusesSettings::BurnDamage)
{
}

void Burn::OnApply(Robot&,Game&) {
}

bool Burn::ApplyStatus(Robot &robot,Game &game) {
    bool safeNeeded = (robot.GetType() == true) ? true : false;
    if (game.DealDamage(robot,StatusesSettings::BurnDamage,safeNeeded)){
    if (robot.FindStatus(_type)){
        if (robot.FindStatus(_type)->DecreaseEffect()){
            return true;
        }

    }
    }
    return false;
}

void Burn::OnReapply(Robot&,Game&) {
    _duration += StatusesSettings::BurnDuration;
}

StatusType Burn::GetStatusType() const{
    return _type;
}

int Burn::GetStatusEndurance() const{
    return _duration;
}

bool Burn::DecreaseEffect(){
    _duration--;
    if (_duration <= 0){
        return true;
    }
    return false;        
}
