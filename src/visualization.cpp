#include "visualization.h"


Visualizer::Visualizer(const Game& game,sf::RenderWindow& window)
    : game_(game), window_(window), _offset_x(20), _offset_y(50)
{
    window_.setFramerateLimit(60);
    if (!font_.openFromFile("D:\\vscode\\public\\OOP\\OOP\\assets\\font.ttf")) {
        throw std::runtime_error("Font not found");
    }
}
using namespace sf ;
void Visualizer::Draw(std::string game_state){
    const auto& map_size = game_.GetMap().GetSize();
    const auto& cell_size = game_.GetMap().CalculateCellSize({int(1000-(2*_offset_x)),int(1000- (2*_offset_y))});
    const auto& grid = game_.GetMap().GetGrid();

    
    if (game_state == "Win" || game_state == "Lose") {
    const bool win = (game_state == "Win");
    Text text(font_, win ? "You Win" : "You Lose", 100);
    text.setFillColor(win ? Color::Yellow : Color::Red);
    text.setCharacterSize(100);
    text.setPosition({float(window_.getSize().x/2-text.getLocalBounds().size.x/2),float(window_.getSize().y/2-text.getLocalBounds().size.y)});
    window_.draw(text);
    }
    else{
        Visualizer::DrawCells(map_size, cell_size,grid);
        Visualizer::DrawRobots(game_.GetRobots(), cell_size,grid);
        Visualizer::DrawPlayer(game_.GetPlayer(), cell_size);
        Visualizer::ShowCurSpecifications(game_.GetPlayer());
    }
    

}
void Visualizer::ShowCurSpecifications(const Player& player) {
    const std::string labels[] = {
        "Energy: " + std::to_string(player.GetEnergy()),
        "Xp: " + std::to_string(player.GetXp()) + " / " + std::to_string(player.GetXpToLvlUp()),
        "Lvl: " + std::to_string(player.GetLvl()),
        "Speed: " + std::to_string(player.GetSpeed())
    };

    const float slot = window_.getSize().x / 4.f;
    for (int i = 0; i < 4; ++i) {
        Text text(font_, labels[i], 30);
        text.setFillColor(Color::Yellow);
        text.setPosition({slot * i + 10.f, 0.f});
        window_.draw(text);
    }
}

void Visualizer::DrawSpecificationsOnRobot(const RectangleShape& rectangle,const Robot& robot){
    if (!font_.getInfo().family.empty()){
    Text text = Text{ font_, std::to_string(robot.GetHp())};
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    text.setPosition({rectangle.getPosition().x, rectangle.getPosition().y});
    window_.draw(text);
    text = Text{ font_, std::to_string(robot.GetDamage())};
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    text.setPosition({rectangle.getPosition().x + rectangle.getSize().x - 1.5f*text.getLocalBounds().size.x, rectangle.getPosition().y});
    window_.draw(text);
}
}
void Visualizer::DrawPlayer(const Player& player, const std::vector<int>& cell_size){
    RectangleShape rectangle(::Vector2f(cell_size[0], cell_size[1]));
    const Position position = player.GetPos();
    rectangle.setPosition({float(position.X() * cell_size[0]) + _offset_x, float(position.Y() * cell_size[1]) + _offset_y});
    rectangle.setFillColor(::Color::Blue);
    window_.draw(rectangle);
    DrawSpecificationsOnRobot(rectangle, player);
}
void Visualizer::DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid){
    for (const auto& robot : robots){
        RectangleShape rectangle(Vector2f(cell_size[0], cell_size[1]));
        const Position position = robot.GetPos();
        if (grid[position.Y()][position.X()].GetVisible() == true){
            rectangle.setPosition({float(position.X() * cell_size[0]) + _offset_x, float(position.Y() * cell_size[1]) + _offset_y});
            rectangle.setFillColor(Color::Red);
            window_.draw(rectangle);
            DrawSpecificationsOnRobot(rectangle, robot);
        }
    }
}
void Visualizer::DrawCross(float pos_x, float pos_y,int width, int height, int alpha){
    VertexArray lines(PrimitiveType::Lines, 4);
    lines[0].position = {pos_x, pos_y};
    lines[0].color = Color(255, 255, 255, alpha);
    lines[1].position = {pos_x + width, pos_y + height};
    lines[1].color = Color(255, 255, 255, alpha);
    lines[2].position = {pos_x + width, pos_y};
    lines[2].color = Color(255, 255, 255, alpha);
    lines[3].position = {pos_x, pos_y + height};
    lines[3].color = Color(255, 255, 255, alpha);

    window_.draw(lines);
}
void Visualizer::DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size,
                           const std::vector<std::vector<Cell>>& grid) {
    RectangleShape rectangle(Vector2f(cell_size[0], cell_size[1]));
    rectangle.setOutlineThickness(1.f);

    for (int i = 0; i < map_size[1]; i++) {
        for (int j = 0; j < map_size[0]; j++) {
            const Cell& cell = grid[i][j];
            const float x = j * cell_size[0] + _offset_x;
            const float y = i * cell_size[1] + _offset_y;

            const bool visible = cell.GetVisible();
            const bool seen = visible || cell.GetExplored();
            const int alpha = visible ? 255 : 128;

            Color fill = Color::Transparent;
            if (seen) {
                if (!cell.GetPassable()) {
                    DrawCross(x, y, cell_size[0], cell_size[1], alpha);
                }
                else if (cell.GetCost() != 1) {
                    fill = Color(161, 208, 252, alpha);
                }
            }

            rectangle.setPosition({x, y});
            rectangle.setFillColor(fill);
            rectangle.setOutlineColor(Color(91, 183, 186, visible ? 255 : 64));
            window_.draw(rectangle);
        }
    }
}
