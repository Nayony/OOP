#ifndef VISUALIZATION
#define VISUALIZATION

#include "game.h"
#include <string>
#include <SFML/Graphics.hpp>

class Visualizer{
    private:
    const Game& game_;
    sf::RenderWindow& window_;
    sf::Font font_;
    float _offset_x,_offset_y;
    public:
        Visualizer(const Game& game, sf::RenderWindow& window);
        void Draw(std::string game_state,int win_x,int win_y);
        const std::vector<int> CalculateCellSize(std::vector<int> window_size,int width,int height) const;
        void DrawCross(float pos_x, float pos_y,int width, int height, int alpha);
        void DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid);
        void DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size,const std::vector<std::vector<Cell>>& grid);
        void DrawPlayer(const Player& player, const std::vector<int>& cell_size);
        void ShowCurSpecifications(const Player& player);
        void DrawSpecificationsOnRobot(const sf::RectangleShape& rectangle, const Robot& robot);
};
    

#endif


