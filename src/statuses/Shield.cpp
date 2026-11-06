#include "Shield.h"


Shield::Shield()
    : _type(StatusType::sShield), _endurance(StatusesSettings::ShieldEndurance)
{
}

void Shield::OnApply(Robot &robot,Game &game) {
    robot.AddShield(_endurance);
}

bool Shield::ApplyStatus(Robot &robot,Game &game) {
    return robot.GetShield() == 0;
}

StatusType Shield::GetStatusType() const{
    return _type;
}

int Shield::GetStatusEndurance() const{
    return _endurance;
}

void Shield::OnReapply(Robot &robot,Game&) {
    robot.AddShield(_endurance);
}

bool Shield::DecreaseEffect(){
    return false;
}