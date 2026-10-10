#include "visualization.h"
#include "constants.h"

namespace {
sf::Color ToSfColor(VisualSettings::Rgba color){
    return {color.red, color.green, color.blue, color.alpha};
}
}


Visualizer::Visualizer(const Game& game,sf::RenderWindow& window)
    : _game(game), _window(window), _offset_x(VisualSettings::MapOffsetX),
      _offset_y(VisualSettings::MapOffsetY)
{
    _window.setFramerateLimit(ApplicationSettings::FrameRateLimit);
    if (!_font.openFromFile("D:\\vscode\\public\\OOP\\OOP\\assets\\font.ttf")) {
        throw std::runtime_error("Font not found");
    }
}
void Visualizer::Draw(std::string game_state,int win_x, int win_y){
    const auto& map_size = _game.GetMap().GetSize();
    const auto& cell_size = CalculateCellSize(
        {int(win_x - VisualSettings::WindowPaddingMultiplier * _offset_x),
         int(win_y - VisualSettings::WindowPaddingMultiplier * _offset_y)}, map_size[0], map_size[1]);
    const auto& grid = _game.GetMap().GetGrid();

    
    if (game_state == "Win" || game_state == "Lose") {
    const bool win = (game_state == "Win");
    sf::Text text(_font, win ? "You Win" : "You Lose", VisualSettings::EndStateTextSize);
    text.setFillColor(ToSfColor(win ? VisualSettings::HighlightColor : VisualSettings::EnemyColor));
    text.setCharacterSize(VisualSettings::EndStateTextSize);
    text.setPosition({float(_window.getSize().x / VisualSettings::CenteringDivisor - text.getLocalBounds().size.x / VisualSettings::CenteringDivisor),
                      float(_window.getSize().y / VisualSettings::CenteringDivisor - text.getLocalBounds().size.y)});
    _window.draw(text);
    }
    else{
        Visualizer::DrawCells(map_size, cell_size,grid);
        Visualizer::DrawRobots(_game.GetRobots(), cell_size,grid);
        Visualizer::DrawPlayer(_game.GetPlayer(), cell_size);
        Visualizer::ShowCurSpecifications(_game.GetPlayer());
    }
    

}
const std::vector<int> Visualizer::CalculateCellSize(std::vector<int> window_size,int width,int height) const{
    int cell_width = (window_size[0]) / width;
    int cell_height = (window_size[1]) / height;
    return std::vector<int>{cell_width, cell_height};
}
void Visualizer::ShowCurSpecifications(const Player& player) {
    const std::string labels[] = {
        "Energy: " + std::to_string(player.GetEnergy()),
        "Xp: " + std::to_string(player.GetXp()) + " / " + std::to_string(player.GetXpToLvlUp()),
        "Lvl: " + std::to_string(player.GetLvl()),
        "Speed: " + std::to_string(player.GetSpeed())
    };

    const float slot = _window.getSize().x / VisualSettings::SpecificationSlotDivisor;
    for (int i = 0; i < VisualSettings::SpecificationCount; ++i) {
        sf::Text text(_font, labels[i], VisualSettings::SpecificationTextSize);
        text.setFillColor(ToSfColor(VisualSettings::HighlightColor));
        text.setPosition({slot * i + VisualSettings::SpecificationTextOffset, 0.f});
        _window.draw(text);
    }
}

void Visualizer::DrawSpecificationsOnRobot(const sf::RectangleShape& rectangle,const Robot& robot){
    if (!_font.getInfo().family.empty()){
    sf::Text text = sf::Text{ _font, std::to_string(robot.GetHp())};
    text.setCharacterSize(VisualSettings::RobotTextSize);
    text.setFillColor(ToSfColor(VisualSettings::TextColor));
    text.setPosition({rectangle.getPosition().x, rectangle.getPosition().y});
    _window.draw(text);
    text = sf::Text{ _font, std::to_string(robot.GetDamage())};
    text.setCharacterSize(VisualSettings::RobotTextSize);
    text.setFillColor(ToSfColor(VisualSettings::TextColor));
    text.setPosition({rectangle.getPosition().x + rectangle.getSize().x - VisualSettings::DamageTextWidthFactor*text.getLocalBounds().size.x, rectangle.getPosition().y});
    _window.draw(text);
}
}
void Visualizer::DrawPlayer(const Player& player, const std::vector<int>& cell_size){
    sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
    const Position position = player.GetPos();
    rectangle.setPosition({float(position.X() * cell_size[0]) + _offset_x, float(position.Y() * cell_size[1]) + _offset_y});
    rectangle.setFillColor(ToSfColor(VisualSettings::PlayerColor));
    _window.draw(rectangle);
    DrawSpecificationsOnRobot(rectangle, player);
}
void Visualizer::DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid){
    for (const auto& robot : robots){
        sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
        const Position position = robot.GetPos();
        if (grid[position.Y()][position.X()].GetVisible() == true){
            rectangle.setPosition({float(position.X() * cell_size[0]) + _offset_x, float(position.Y() * cell_size[1]) + _offset_y});
            rectangle.setFillColor(ToSfColor(VisualSettings::EnemyColor));
            _window.draw(rectangle);
            DrawSpecificationsOnRobot(rectangle, robot);
        }
    }
}
void Visualizer::DrawCross(float pos_x, float pos_y,int width, int height, int alpha){
    sf::VertexArray lines(sf::PrimitiveType::Lines, VisualSettings::CrossVertexCount);
    lines[0].position = {pos_x, pos_y};
    auto cross_color = VisualSettings::CrossColor;
    cross_color.alpha = static_cast<unsigned char>(alpha);
    lines[0].color = ToSfColor(cross_color);
    lines[1].position = {pos_x + width, pos_y + height};
    lines[1].color = ToSfColor(cross_color);
    lines[2].position = {pos_x + width, pos_y};
    lines[2].color = ToSfColor(cross_color);
    lines[3].position = {pos_x, pos_y + height};
    lines[3].color = ToSfColor(cross_color);

    _window.draw(lines);
}
void Visualizer::DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size,
                           const std::vector<std::vector<Cell>>& grid) {
    sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
    rectangle.setOutlineThickness(VisualSettings::CellOutlineThickness);

    for (int i = 0; i < map_size[1]; i++) {
        for (int j = 0; j < map_size[0]; j++) {
            const Cell& cell = grid[i][j];
            float x = j * cell_size[0] + _offset_x;
            float y = i * cell_size[1] + _offset_y;

            bool visible = cell.GetVisible();
            bool seen = visible || cell.GetExplored();
            const unsigned char alpha = visible ? VisualSettings::VisibleAlpha : VisualSettings::ExploredAlpha;

            sf::Color fill = ToSfColor(VisualSettings::TransparentColor);
            if (seen) {
                if (cell.GetFactory() == true) {
                    auto factory_color = VisualSettings::FactoryColor;
                    factory_color.alpha = alpha;
                    fill = ToSfColor(factory_color);
                }
                else if (cell.GetCost() == CellSettings::ImpassableCost) {
                    DrawCross(x, y, cell_size[0], cell_size[1], alpha);
                }
                else if (cell.GetCost() != CellSettings::DefaultMoveCost) {
                    auto difficult_cell_color = VisualSettings::DifficultCellColor;
                    difficult_cell_color.alpha = alpha;
                    fill = ToSfColor(difficult_cell_color);
                }
            }

            rectangle.setPosition({x, y});
            rectangle.setFillColor(fill);
            auto outline_color = VisualSettings::CellOutlineColor;
            outline_color.alpha = visible ? VisualSettings::VisibleAlpha : VisualSettings::HiddenOutlineAlpha;
            rectangle.setOutlineColor(ToSfColor(outline_color));
            _window.draw(rectangle);
        }
    }
}
