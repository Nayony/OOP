
#ifndef CONTROLS
#define CONTROLS

#include <string>
#include <SFML/Graphics.hpp>
class Controls{
    public:

    enum keys{
    kUp,
    kRight,
    kLeft,
    kDown,
    kNone,
    };  
        keys TranslateCmd(const sf::Event::KeyPressed& key);
};


#endif