#include "timer_manager.h"
#include <algorithm>
#include <iostream>




TimerManager::TimerManager()
    : _timer_vector()
{
}
int TimerManager::Start(float time){
    int id = FindFreeId();
    timerSt timer;
    timer.timer.StartTimer(time);
    timer.id = id;
    _timer_vector.push_back(timer);
    return id;
}

int TimerManager::FindFreeId(){
    int maxId = 0;
    if (_timer_vector.empty()){
        return 0;
    }
    for (auto &timer: _timer_vector){
        if (maxId == timer.id){
            maxId++;
            continue;
        }
        else {
            return maxId;
        }
    }
    return maxId;
}
float TimerManager::GetProgress(int id) const{
    for (const auto &timer: _timer_vector){
        if (timer.id == id){
            float k = timer.timer.GetElapsed()/timer.timer.GetDuration();
            return k;
        }
    }
    return -1;
}
float TimerManager::GetElapsed(int id){
    for (auto &timer: _timer_vector){
        if (timer.id == id){
            return timer.timer.GetElapsed();
        }
    }
    return -1;
    
}
void TimerManager::CancelTimer(int id){
    auto pi = std::find_if(_timer_vector.begin(),_timer_vector.end(),[id](const timerSt& t){
        return t.id == id;
    });
    if (pi != _timer_vector.end()){
        _timer_vector.erase(pi);
    }
}
