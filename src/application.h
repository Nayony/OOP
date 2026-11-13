#ifndef APPLICATION_H
#define APPLICATION_H

#include "controls.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "game.h"
#include "visualization.h"

template <typename LevelGenerator, int LevelCount>
class Application {
public:
Application()
        : _generator(),                                   
          _level(0),
          _game(_generator.Generate(_level)),             
          _win_x(ApplicationSettings::WindowWidth),
          _win_y(ApplicationSettings::WindowHeight),
          _window(sf::VideoMode({_win_x, _win_y}), ApplicationSettings::WindowTitle),
          _visualizer(_game, _window)
    {
    }

void Restart(){
	_game = Game(GameSettings::NormalEnemyCount);
}

void run()
{
	while (_window.isOpen()) {
		while (const std::optional event = _window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				_window.close();
				continue;
			}
			if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
				if (key->code == sf::Keyboard::Key::Escape) {
					if (!_game.GetCellsInRange().empty()){
						_game.ClearSelection();
					}
					else{ _window.close();}
				} else if (key->code == sf::Keyboard::Key::Space) {
					_game.Pass();
                } else if (key->code == sf::Keyboard::Key::R) {
					Restart();
                }
                else if (key->code == sf::Keyboard::Key::C) {
					_visualizer.ChangeVisualizationMode();
                }
				else if (key->control) {
					if (key->code == sf::Keyboard::Key::Num1) {
						_game.GiveAbilityToPlayer(AbilityType::sAroundHit);
					}
					else if (key->code == sf::Keyboard::Key::Num2) {
						_game.GiveAbilityToPlayer(AbilityType::sFarHit);
					}
					else if (key->code == sf::Keyboard::Key::Num3) {
						_game.GiveAbilityToPlayer(AbilityType::sHeal);
					}
					else if (key->code == sf::Keyboard::Key::Num4) {
						_game.GiveAbilityToPlayer(AbilityType::sTeleport);
					}
				}
				else if (key->code == sf::Keyboard::Key::Num1) {
					_game.PlayerUseAbility(AbilityType::sAroundHit);
				}
				else if (key->code == sf::Keyboard::Key::Num2) {
					_game.PlayerUseAbility(AbilityType::sFarHit);
				}
				else if (key->code == sf::Keyboard::Key::Num3) {
					_game.PlayerUseAbility(AbilityType::sHeal);
				}
				else if (key->code == sf::Keyboard::Key::Num4) {
					_game.PlayerUseAbility(AbilityType::sTeleport);
				}
				else if (_game.GetGameState() == "Playing") {
					_game.Move(_controls.TranslateCmd(*key));
				}
			}
			else if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (mouseButton->button == sf::Mouse::Button::Left){
				auto type = _game.GetSelectedAbility();
				if (type != AbilityType::sNone){
					sf::Vector2i clickPos = mouseButton->position;
					if (const auto cell = _visualizer.CellAt(clickPos)) {
						if (auto* ability = _game.GetPlayer().FindAbility(type)) {
							ability->EndAbility(*cell, _game);
						}
					}
				}
			}
			}
		}

		_game.UpdateVisualEvents();
		_window.clear({VisualSettings::BackgroundColor.red, VisualSettings::BackgroundColor.green,
			       VisualSettings::BackgroundColor.blue, VisualSettings::BackgroundColor.alpha});
		_visualizer.Draw(_game.GetGameState(), _win_x, _win_y);
		_window.display();
	}
}
private:
    LevelGenerator _generator;   
    int _level;
    Game _game;
    unsigned int _win_x, _win_y;
    sf::RenderWindow _window;
    Visualizer _visualizer;
    Controls _controls;
};


#endif
