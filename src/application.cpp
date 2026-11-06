#include "application.h"
#include <optional>
#include <iostream>

Application::Application(int enemy_robot_count)
	: _enemy_robot_count(enemy_robot_count),
	  _game(enemy_robot_count),
	_win_x(ApplicationSettings::WindowWidth), _win_y(ApplicationSettings::WindowHeight),
	_window(sf::VideoMode({_win_x, _win_y}), ApplicationSettings::WindowTitle),
	  _visualizer(_game, _window)
{
}

void Application::Restart(){
	_game = Game(_enemy_robot_count);
}

void Application::run()
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

		_window.clear({VisualSettings::BackgroundColor.red, VisualSettings::BackgroundColor.green,
			       VisualSettings::BackgroundColor.blue, VisualSettings::BackgroundColor.alpha});
		_visualizer.Draw(_game.GetGameState(), _win_x, _win_y);
		_window.display();
	}
}
