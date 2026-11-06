#ifndef Overload_H
#define Overload_H

#include "statuses.h"
#include "../constants.h"
#include "../Robot.h"



class Overload : public Statuses {
public:
    Overload();
    void OnApply(Robot &robot,Game &game) override;
    bool ApplyStatus(Robot &robot,Game &game) override;
    StatusType GetStatusType() const override;
    int GetStatusEndurance() const override;
    bool DecreaseEffect() override;
    void OnReapply(Robot &robot,Game &game) override;
private:
    StatusType _type;
    int _duration;
};

#endif
