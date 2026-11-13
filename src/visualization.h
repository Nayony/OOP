#ifndef VISUALIZATION
#define VISUALIZATION

#include "game.h"
#include "abilities/AbilityInfo.h"
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>
#include "time/timer_manager.h"
class Visualizer{
    private:
    const Game& _game;
    sf::RenderWindow& _window;
    sf::Font _fontBold;
    sf::Font _fontRegular;
    sf::Texture _status_texture;
    AbilityInfo _abilityInfo;
    bool _cellIncludesMouse;
    int _cur_mode;
    std::vector<std::string> modes;
    public:
        Visualizer(const Game& game, sf::RenderWindow& window);
        void Draw(std::string game_state,int win_x,int win_y);
        const std::vector<int> CalculateCellSize(std::vector<int> window_size,int width,int height) const;
        void DrawCross(float pos_x, float pos_y,int width, int height, int alpha);
        void DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid);
        void DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size,const std::vector<std::vector<Cell>>& grid,sf::Vector2f mouse);
        void DrawPlayer(const Player& player, const std::vector<int>& cell_size,sf::Vector2f mouse);
        void ShowCurSpecifications(const Player& player);
        sf::Color LerpColor(VisualSettings::Rgba from, VisualSettings::Rgba to, float t);
        void DrawSpecificationsOnRobot(const sf::RectangleShape& rectangle, const Robot& robot);
        void DrawAbilityButton(const Game& game,sf::Vector2f mouse);
        void DrawGuideAbilityPanel(std::string description,std::string topic,std::string lvl);
        std::optional<Position> CellAt(sf::Vector2i mouse);
        std::vector<int> CellSize() const;
        void DrawAbilityCells(const std::vector<Position>& cells,bool onlyCircle);
        void ChangeVisualizationMode();   
        void DrawCurrentMode();
        void DrawStatus(StatusType status,const std::vector<int>& cell_size,Position pos,int counter,int position);
        void DrawStatusInfo(const Robot &robot,Position pos,const std::vector<int>& cell_size);
};
    

#endif
