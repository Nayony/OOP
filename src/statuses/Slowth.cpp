#include "Slowth.h"


Slowth::Slowth()
    : _type(StatusType::sSlowth), _duration(StatusesSettings::SlowthDuration)
{
}

void Slowth::OnApply(Robot &robot,Game &game) {
    robot.SetCanMove(false);
}

bool Slowth::ApplyStatus(Robot &robot,Game &game) {
    if (DecreaseEffect()) {
        robot.SetCanMove(true);
        return true;
    }
    return false;
}

StatusType Slowth::GetStatusType() const{
    return _type;
}

int Slowth::GetStatusEndurance() const{
    return _duration;
}

void Slowth::OnReapply(Robot&,Game&) {
    _duration += StatusesSettings::SlowthDuration;
}
bool Slowth::DecreaseEffect(){
    _duration--;
    if (_duration<=0){
        return true;
    }
    return false;
}