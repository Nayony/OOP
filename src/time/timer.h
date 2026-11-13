
#ifndef TIMER_H
#define TIMER_H


#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>


class Timer
{
private:
    sf::Clock _clock;
    sf::Time _duration;

public:
    Timer() = default;

    void StartTimer(float time);
    void Update();
    float GetElapsed() const;
    float GetDuration() const;

    bool IsFinished() const;
};

#endif
