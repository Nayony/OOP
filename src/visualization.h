#ifndef VISUALIZATION
#define VISUALIZATION

#include "game.h"
#include <SFML/Graphics.hpp>

class Visualizer{
    private:
    const Game& game_;
    sf::RenderWindow& window_;
    float _offset;
    public:
        Visualizer(const Game& game, sf::RenderWindow& window);
        void Draw();
        void MakeCross(float pos_x, float pos_y,int width, int height);
        void DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid);
        void DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size);
        void DrawPlayer(const Player& player, const std::vector<int>& cell_size);
};
    

#endif


