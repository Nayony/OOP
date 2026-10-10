#ifndef APPLICATION_H
#define APPLICATION_H

#include "controls.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "game.h"
#include "visualization.h"

class Application {
public:
    Application(int enemy_robot_count = ApplicationSettings::DefaultEnemyCount);
    void run();
    void Restart();
private:
    unsigned int _win_x,_win_y;
    int _enemy_robot_count;
    Game _game;
    sf::RenderWindow _window;
    Visualizer _visualizer;
    Controls _controls;
};


#endif