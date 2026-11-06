#ifndef Burn_H
#define Burn_H

#include "statuses.h"
#include "../constants.h"
#include "../game.h"



class Burn : public Statuses {
public:
    Burn();
    void OnApply(Robot &robot,Game &game) override;
    bool ApplyStatus(Robot &robot,Game &game) override;
    void OnReapply(Robot &robot,Game &game) override;
    StatusType GetStatusType() const override;
    int GetStatusEndurance() const override;
    bool DecreaseEffect() override;
private:
    StatusType _type;
    int _duration;
    int _damage;
};

#endif
