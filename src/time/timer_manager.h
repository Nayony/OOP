
#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H


#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include "timer.h"
#include <vector>


class TimerManager
{
private:
    struct timerSt{
        Timer timer;
        int id;
    };
    std::vector<timerSt> _timer_vector;
public:
    TimerManager();
   int Start(float time);
    int FindFreeId();
    float GetProgress(int id) const;
    void CancelTimer(int id);
    float GetElapsed(int id);

};

#endif
