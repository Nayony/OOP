#include "application.h"
#include <optional>

Application::Application(int enemy_robot_count)
	: _enemy_robot_count(enemy_robot_count),
	  _game(enemy_robot_count),
      _win_x(1300), _win_y(1300),
	  _window(sf::VideoMode({_win_x, _win_y}), "Baldur's Gate 4"),
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
					_window.close();
				} else if (key->code == sf::Keyboard::Key::Space) {
					_game.Pass();
                } else if (key->code == sf::Keyboard::Key::R) {
					Restart();
				} else if (_game.GetGameState() == "Playing") {
					_game.Move(_controls.TranslateCmd(*key));
				}
			}
		}

		_window.clear(sf::Color::Black);
		_visualizer.Draw(_game.GetGameState(),_win_x,_win_y);
		_window.display();
	}
}
