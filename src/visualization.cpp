#include "visualization.h"

Visualizer::Visualizer(const Game& game, sf::RenderWindow& window)
    : game_(game), window_(window), _offset(5)
{
}

void Visualizer::Draw(){
    //const Map& map = game_.GetMap();
    auto map_size = game_.GetMap().GetSize();
    auto cell_size = game_.GetMap().CalculateCellSize({1000,1000});
    auto grid = game_.GetMap().GetGrid();
    Visualizer::DrawCells(map_size, cell_size,grid);
    Visualizer::DrawRobots(game_.GetRobots(), cell_size);
    Visualizer::DrawPlayer(game_.GetPlayer(), cell_size);
}
void Visualizer::DrawPlayer(const Player& player, const std::vector<int>& cell_size){
    sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
    rectangle.setPosition({float(player.GetPos()[0] * cell_size[0]) + _offset, float(player.GetPos()[1] * cell_size[1]) + _offset});
    rectangle.setFillColor(sf::Color::Blue);
    window_.draw(rectangle);
}
void Visualizer::DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size){
    for (const auto& robot : robots){
        sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
        rectangle.setPosition({float(robot.GetPos()[0] * cell_size[0]) + _offset, float(robot.GetPos()[1] * cell_size[1]) + _offset});
        rectangle.setFillColor(sf::Color::Red);
        window_.draw(rectangle);
    }
}
void Visualizer::MakeCross(float pos_x, float pos_y,int width, int height){
    sf::VertexArray lines(sf::PrimitiveType::Lines, 4);
    lines[0].position = {pos_x, pos_y};
    lines[1].position = {pos_x + width,pos_y+height};
    lines[2].position = {pos_x+width, pos_y};
    lines[3].position = {pos_x,pos_y+height};
    window_.draw(lines);
}
void Visualizer::DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid){
    float x,y;
    for (int i = 0; i < map_size[1]; i++){
        for (int j = 0; j < map_size[0]; j++){
            sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
            x = (j*cell_size[0] + _offset);
            y = (i*cell_size[1] + _offset);
            rectangle.setPosition({x,y});
            if (grid[i][j].GetPassible() == true){
                MakeCross(x,y,cell_size[0],cell_size[1]);
            }
            if(grid[i][j].GetOccupied() != true){
                rectangle.setFillColor(sf::Color::Transparent);
            }
            rectangle.setOutlineThickness(1.f);
            rectangle.setOutlineColor(sf::Color::Green);
            window_.draw(rectangle);
        }
}
}