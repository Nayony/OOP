#ifndef Shield_H
#define Shield_H

#include "statuses.h"
#include "../constants.h"
#include "../Robot.h"



class Shield : public Statuses {
public:
    Shield();
    void OnApply(Robot &robot,Game &game) override;
    bool ApplyStatus(Robot &robot,Game &game) override;
    void OnReapply(Robot &robot,Game &game) override;
    StatusType GetStatusType() const override;
    int GetStatusEndurance() const override;
    bool DecreaseEffect() override;
private:
    StatusType _type;
    int _endurance;
};

#endif
