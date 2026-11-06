#include "Overload.h"


Overload::Overload()
    : _type(StatusType::sOverload), _duration(StatusesSettings::OverloadDuration)
{
}

void Overload::OnApply(Robot &robot,Game &game) {
    robot.SetCanUseAbility(false);
}

bool Overload::ApplyStatus(Robot &robot,Game &game) {
    return false;
}

StatusType Overload::GetStatusType() const{
    return _type;
}

int Overload::GetStatusEndurance() const{
    return _duration;
}

void Overload::OnReapply(Robot&,Game&) {
    _duration = StatusesSettings::OverloadDuration;
}

bool Overload::DecreaseEffect(){
    return true;
}