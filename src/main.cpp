#include "map.h"
#include "cell.h"
#include "game.h"
#include "visualization.h"
#include <iostream>
#include "controls.h"
using namespace std;
#include <SFML/Graphics.hpp>

int main(){
    auto game = Game(10);
    Controls controls;
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "main");
    Visualizer visualizer(game, window);

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()){
                if (key->code == sf::Keyboard::Key::Escape){
                    window.close();
                }
                else if(key->code == sf::Keyboard::Key::M){
                    game.MoveEnemyRobots();
                }
                else{
                    game.Move(controls.TranslateCmd(*key));
                }
            }
        }

        window.clear(sf::Color::Black);
        visualizer.Draw();
        window.display();
    }


    return 0;
}