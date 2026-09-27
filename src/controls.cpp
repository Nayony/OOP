#include "controls.h"

Controls::keys Controls::TranslateCmd(const sf::Event::KeyPressed& key){
            switch (key.code)
            {
            case sf::Keyboard::Key::W:
                return kUp;
            case sf::Keyboard::Key::S:
                return kDown;
            case sf::Keyboard::Key::A:
                return kLeft;
            case sf::Keyboard::Key::D:
                return kRight;
            default:
                return kNone;
            }
        }