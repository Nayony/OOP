#ifndef Slowth_H
#define Slowth_H

#include "statuses.h"
#include "../constants.h"
#include "../Robot.h"



class Slowth : public Statuses {
public:
    Slowth();
    void OnApply(Robot &robot,Game &game) override;
    bool ApplyStatus(Robot &robot,Game &game) override;
    StatusType GetStatusType() const override;
    int GetStatusEndurance() const override;
    void OnReapply(Robot &robot,Game &game) override;
    bool DecreaseEffect() override;
private:
    StatusType _type;
    int _duration;
};

#endif
