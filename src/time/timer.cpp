#include "timer.h"
#include <algorithm>

void Timer::StartTimer(float time)
{
    _duration = sf::seconds(time);
    _clock.restart();
}

float Timer::GetElapsed() const
{
    return _clock.getElapsedTime().asSeconds();
}

float Timer::GetDuration() const
{
    return _duration.asSeconds();
}

bool Timer::IsFinished() const
{
    return _clock.getElapsedTime() >= _duration;
}
void Timer::Update(){
    _clock.restart();
}
