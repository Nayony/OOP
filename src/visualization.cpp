#include "visualization.h"
#include "constants.h"
#include <iostream>

namespace {
sf::Color ToSfColor(VisualSettings::Rgba color){
    return {color.red, color.green, color.blue, color.alpha};
}
}


Visualizer::Visualizer(const Game& game,sf::RenderWindow& window)
    : _game(game), _window(window), _cellIncludesMouse(false), modes({"standart","enemy","blocked","statuses"}),_cur_mode(0)
{
    _window.setFramerateLimit(ApplicationSettings::FrameRateLimit);
    if (!_fontBold.openFromFile("D:\\vscode\\public\\OOP\\OOP\\assets\\NotoSerif-Bold.ttf")) {
        throw std::runtime_error("Font not found");
    }
    if (!_fontRegular.openFromFile("D:\\vscode\\public\\OOP\\OOP\\assets\\NotoSansJP-Medium.ttf")) {
        throw std::runtime_error("Font not found");
    }
    if (!_status_texture.loadFromFile("D:\\vscode\\public\\OOP\\OOP\\assets\\status_icons.png")) {
        throw std::runtime_error("Image not found");
    }
    
}

void Visualizer::Draw(std::string game_state,int win_x, int win_y){
    const auto& map_size = _game.GetMap().GetSize();
    const auto cell_size = CellSize();
    const auto& grid = _game.GetMap().GetGrid();
    sf::Vector2f mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
    
    
    if (game_state == "Win" || game_state == "Lose") {
    const bool win = (game_state == "Win");
    sf::Text text(_fontBold, win ? "You Win" : "You Lose", VisualSettings::EndStateTextSize);
    text.setFillColor(ToSfColor(win ? VisualSettings::HighlightColor : VisualSettings::EnemyColor));
    text.setCharacterSize(VisualSettings::EndStateTextSize);
    text.setPosition({float(_window.getSize().x / VisualSettings::CenteringDivisor - text.getLocalBounds().size.x / VisualSettings::CenteringDivisor),
                      float(_window.getSize().y / VisualSettings::CenteringDivisor - text.getLocalBounds().size.y)});
    _window.draw(text);
    }
    else{
        Visualizer::DrawCells(map_size, cell_size,grid);
        if (modes[_cur_mode] == "standart"){
            Visualizer::DrawRobots(_game.GetRobots(), cell_size,grid,mouse);
        }
        else if(modes[_cur_mode] == "enemy"){
            Visualizer::DrawRobots(_game.GetRobots(), cell_size,grid,mouse);
        }
        if(!_game.GetCellsInRange().empty() && _game.GetSelectedAbility() != AbilityType::sNone){
            DrawAbilityCells(_game.GetCellsInRange());
		}
        Visualizer::DrawPlayer(_game.GetPlayer(), cell_size,mouse);
        Visualizer::ShowCurSpecifications(_game.GetPlayer());
        Visualizer::DrawCurrentMode();
        Visualizer::DrawAbilityButton(_game,mouse);
    }
    

}
const std::vector<int> Visualizer::CalculateCellSize(std::vector<int> window_size,int width,int height) const{
    int cell_width = (window_size[0]) / width;
    int cell_height = (window_size[1]) / height;
    return std::vector<int>{cell_width, cell_height};
}
std::vector<int> Visualizer::CellSize() const{
    const auto& map_size = _game.GetMap().GetSize();
    const sf::Vector2u window_size = _window.getSize();
    return CalculateCellSize(
        {int(window_size.x - VisualSettings::MapMarginLeft - VisualSettings::MapMarginRight),
         int(window_size.y - VisualSettings::MapMarginTop - VisualSettings::MapMarginBot)},
        map_size[0], map_size[1]);
}
void Visualizer::ShowCurSpecifications(const Player& player) {
    sf::Text text(_fontRegular);
    std::string labels[] = {
        "Specifications:",
        "Speed: " + std::to_string(player.GetSpeed()),
        "Energy: " + std::to_string(player.GetEnergy()),
        "Damage: " + std::to_string(player.GetDamage()),
        "Hp: " + std::to_string(player.GetHp()),
        "Xp: " + std::to_string(player.GetXp()) + " / " + std::to_string(player.GetXpToLvlUp()),
        "Lvl: " + std::to_string(player.GetLvl())
    };
    sf::Text topic(_fontBold);
    sf::Text regular(_fontRegular);
    float y = VisualSettings::SpecificationTextOffsetY;
    for (int i = 0; i <= VisualSettings::SpecificationCount; ++i) {
        const bool isTopic = (i == 0);
        sf::Text text(isTopic ? _fontBold : _fontRegular);
        
        text.setString(labels[i]);
        text.setCharacterSize(VisualSettings::SpecificationTextSize);
        text.setFillColor(sf::Color::White);
        text.setPosition({VisualSettings::SpecificationTextOffsetX, y});
        
        _window.draw(text);
        
        y += isTopic
        ? VisualSettings::SpecificationTextOffsetTopic
        : VisualSettings::SpecificationTextOffsetBetween;
    }
    std::string str = "";
    y += VisualSettings::SpecificationTextOffsetTopic;

    if (!player.GetStatuses().empty()){
        text.setCharacterSize(VisualSettings::SpecificationTextSize);
        text.setString("Statuses: ");
        text.setFont(_fontBold);
        text.setPosition({VisualSettings::SpecificationTextOffsetX, y});
        _window.draw(text);
        y += VisualSettings::SpecificationTextOffsetTopic;

    for (const auto& status:player.GetStatuses()){
        switch (status.get()->GetStatusType())
        {
            case StatusType::sBurn:
            str = "Burn:" + std::to_string(status.get()->GetStatusEndurance());
            break;
            case StatusType::sSlowth:
            str = "Slowth:" + std::to_string(status.get()->GetStatusEndurance());
            break;
            case StatusType::sOverload:
            str = "OverLoad:" + std::to_string(status.get()->GetStatusEndurance());
            break;
            case StatusType::sShield:
            str = "Shield:" + std::to_string(player.GetShield());
            break;
            default:
            break; 
        }
            text.setFont(_fontRegular);
            text.setString(str);
            text.setCharacterSize(VisualSettings::SpecificationTextSize);
            text.setFillColor(sf::Color::White);
            text.setPosition({VisualSettings::SpecificationTextOffsetX, y});
            y += VisualSettings::SpecificationTextOffsetBetween;
            _window.draw(text);
    }
}
    
}
void Visualizer::ChangeVisualizationMode(){
    _cur_mode++;
    if (_cur_mode>=modes.size()) _cur_mode = 0;
}
void Visualizer::DrawSpecificationsOnRobot(const sf::RectangleShape& rectangle,const Robot& robot){
    if (!_fontBold.getInfo().family.empty()){
    sf::Text text = sf::Text{ _fontBold, std::to_string(robot.GetHp())};
    text.setCharacterSize(VisualSettings::RobotTextSize);
    text.setFillColor(ToSfColor(VisualSettings::TextColor));
    text.setPosition({rectangle.getPosition().x, rectangle.getPosition().y});
    _window.draw(text);
    text = sf::Text{ _fontBold, std::to_string(robot.GetDamage())};
    text.setCharacterSize(VisualSettings::RobotTextSize);
    text.setFillColor(ToSfColor(VisualSettings::TextColor));
    text.setPosition({rectangle.getPosition().x + rectangle.getSize().x - VisualSettings::DamageTextWidthFactor*text.getLocalBounds().size.x, rectangle.getPosition().y});
    _window.draw(text);
}
}
void Visualizer::DrawStatusInfo(const Robot &robot,Position pos,const std::vector<int>& cell_size){
    sf::RectangleShape guidePanel({float(cell_size[0]),float(cell_size[1])});
    std::string str;
    sf::Text text(_fontRegular);
    guidePanel.setPosition({float(pos.X()),float(pos.Y())});
    if (robot.GetStatuses().size() == 0){
        text.setString("No\nstatuses");
        text.setPosition({float(pos.X()),float(pos.Y())});
        text.setCharacterSize(VisualSettings::StatusInfoTextSize);
        _window.draw(text);
        return;
    }
    int i = 0;
    for (const auto& status:robot.GetStatuses()){
        switch (status.get()->GetStatusType())
        {
        case StatusType::sBurn:
            str = "Burn:" + std::to_string(status.get()->GetStatusEndurance());
            break;
        case StatusType::sSlowth:
            str = "Slowth:" + std::to_string(status.get()->GetStatusEndurance());
            break;
        case StatusType::sOverload:
            str = "OverLD:" + std::to_string(status.get()->GetStatusEndurance());
            break;
        case StatusType::sShield:
            str = "Shield:" + std::to_string(robot.GetShield());
            break;
        default:
            break; 
        }
        text.setString(str);
        text.setPosition({pos.X() + VisualSettings::StatusInfoTextOffsetX,pos.Y() + VisualSettings::StatusInfoTextOffsetY*i});
        text.setCharacterSize(VisualSettings::StatusInfoTextSize);
        i++;
        _window.draw(text);
    }
}
void Visualizer::DrawPlayer(const Player& player, const std::vector<int>& cell_size,sf::Vector2f mouse){
    sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
    const Position position = player.GetPos();
    float x = float(position.X() * cell_size[0]) + VisualSettings::MapMarginLeft;
    float y = float(position.Y() * cell_size[1]) + VisualSettings::MapMarginTop;
    rectangle.setPosition({x,y});
    rectangle.setFillColor(ToSfColor(VisualSettings::PlayerColor));
    _window.draw(rectangle);
    bool hovered = rectangle.getGlobalBounds().contains(mouse);
    if (hovered)
    DrawStatusInfo(player,{int(x),int(y)},cell_size);
    else{
    DrawSpecificationsOnRobot(rectangle, player);
    for (int i = 0;i<player.GetStatuses().size();i++){
        DrawStatus(player.GetStatuses()[i]->GetStatusType(),cell_size,{int(x),int(y)},player.GetStatuses().size(),i+1);
    }
    }
}
void Visualizer::DrawCurrentMode(){
    sf::Text text(_fontRegular);
    text.setString("Current visualization mode: " + modes[_cur_mode]);
    text.setOrigin({text.getLocalBounds().size.x / 2.f, text.getLocalBounds().position.y});
    text.setPosition({_window.getSize().x / 2.f, VisualSettings::MapMarginTop/2});
    _window.draw(text);
}
void Visualizer::DrawRobots(const std::vector<Robot>& robots, const std::vector<int>& cell_size, const std::vector<std::vector<Cell>>& grid,sf::Vector2f mouse){
    for (const auto& robot : robots){
        sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
        const Position position = robot.GetPos();
        if (grid[position.Y()][position.X()].GetVisible() == true){
            float x = float(position.X() * cell_size[0]) + VisualSettings::MapMarginLeft;
            float y = float(position.Y() * cell_size[1]) + VisualSettings::MapMarginTop;
            rectangle.setPosition({x,y});
            rectangle.setFillColor(ToSfColor(VisualSettings::EnemyColor));
            _window.draw(rectangle);
            bool hovered = rectangle.getGlobalBounds().contains(mouse);
            if (hovered) DrawStatusInfo(robot,{int(x),int(y)},cell_size);
            else{
            DrawSpecificationsOnRobot(rectangle, robot);
            for (int i = 0;i<robot.GetStatuses().size();i++){
                DrawStatus(robot.GetStatuses()[i]->GetStatusType(),cell_size,{int(x),int(y)},robot.GetStatuses().size(),i+1);
            }
        }
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

void Visualizer::DrawGuideAbilityPanel(std::string description,std::string topic,std::string lvl){
    sf::RectangleShape guidePanel({VisualSettings::GuideAbilityPanelWidth,
                                   VisualSettings::GuideAbilityPanelHeight});

    const float win_w = static_cast<float>(_window.getSize().x);
    const float win_h = static_cast<float>(_window.getSize().y);

    const float x = (win_w - guidePanel.getSize().x) / 2.f;
    const float y = win_h - VisualSettings::MapMarginBot - guidePanel.getSize().y;

    guidePanel.setPosition({x, y});
    guidePanel.setFillColor(ToSfColor(VisualSettings::GuideAbilityOutlineColor));
    _window.draw(guidePanel);

    sf::Text top(_fontBold);
    top.setString(topic + " " + "LVL:" + " " + lvl + "/" + std::to_string(AbilitiesSettings::MaxLvl));
    top.setCharacterSize(VisualSettings::StandartTextSize);            
    top.setFillColor(sf::Color::White);
    top.setOrigin({top.getLocalBounds().position.x + top.getLocalBounds().size.x / 2.f, top.getLocalBounds().position.y});
    top.setPosition({guidePanel.getPosition().x + guidePanel.getSize().x / 2.f, guidePanel.getPosition().y + VisualSettings::GuideAbilityTopicOffsetY});

    sf::Text desc(_fontRegular);
    desc.setString(description);
    desc.setCharacterSize(VisualSettings::AbilityDescriptionSize);            
    desc.setFillColor(sf::Color::White);
    desc.setPosition({VisualSettings::GuideAbilityDescOffsetX + guidePanel.getPosition().x, guidePanel.getPosition().y + guidePanel.getSize().y/5.f});
    
    _window.draw(top);
    _window.draw(desc);

}
void Visualizer::DrawAbilityButton(const Game& game,sf::Vector2f mouse){
    const auto& _abilities = game.GetPlayer().GetAbilities();
    auto& player = game.GetPlayer();
    const bool hasPoint = player.HasAbilityPoint() >= 1;

    for (int abilityId = 1; abilityId <= VisualSettings::AbilitySlotCount; abilityId++){
        int ownedIndex = -1;                                          
        for (int k = 0; k < static_cast<int>(_abilities.size()); k++){
            if (_abilities[k]->GetAbilityId() == abilityId) ownedIndex = k;
        }
        const bool owned = ownedIndex != -1;

        if (!owned && !hasPoint) continue;                           

        sf::RectangleShape button({VisualSettings::ButtonSize,VisualSettings::ButtonSize});
        button.setPosition({VisualSettings::AbilityPanelOffsetX + VisualSettings::ButtonOffset*(abilityId-1),VisualSettings::AbilityPanelOffsetY});
        button.setFillColor(sf::Color::White);
        sf::Color outlineColor = sf::Color::Transparent;

        if (hasPoint){
        if (owned){
            outlineColor = sf::Color::Green;
        
        if(_abilities[ownedIndex]->GetAbilityLvl() == AbilitiesSettings::MaxLvl){
            outlineColor = sf::Color::Transparent;
        }
        }
        else{outlineColor = sf::Color::Yellow;}
        }
        //if (hasPoint) outlineColor = owned ? sf::Color::Green : sf::Color::Yellow;
        button.setOutlineColor(outlineColor);
        button.setOutlineThickness(VisualSettings::OutlineThickness); 

        
        sf::Text label(_fontBold);
        label.setString(std::to_string(abilityId));
        label.setCharacterSize(VisualSettings::StandartTextSize);            
        label.setFillColor(sf::Color::Black);

        label.setOrigin({label.getLocalBounds().position.x+ label.getLocalBounds().size.x/2,label.getLocalBounds().position.y + label.getLocalBounds().size.y/2});
        label.setPosition({button.getPosition().x + button.getSize().x/2,button.getPosition().y + button.getSize().y/2});


        _window.draw(button);
        _window.draw(label);

        bool hovered = button.getGlobalBounds().contains(mouse);
        if (hovered){
            const int level = owned ? _abilities[ownedIndex]->GetAbilityLvl() : 0;
            DrawGuideAbilityPanel(_abilityInfo.GetDescription(abilityId), _abilityInfo.GetName(abilityId),
            std::to_string(level));
        }
        
    }
}
std::optional<Position> Visualizer::CellAt(sf::Vector2i mouse){
    const auto& map_size = _game.GetMap().GetSize();
    const auto cell_size = CellSize();
    sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
    for (int i = 0; i < map_size[1]; i++) {
        for (int j = 0; j < map_size[0]; j++) {
            float x = j * cell_size[0] + VisualSettings::MapMarginLeft;
            float y = i * cell_size[1] + VisualSettings::MapMarginTop;
            rectangle.setPosition({x, y});
            if (rectangle.getGlobalBounds().contains({float(mouse.x),float(mouse.y)})){
                return Position{j, i};
            }
        }
    }
    return std::nullopt;
}
void Visualizer::DrawAbilityCells(const std::vector<Position>& cells){
    const auto cell_size = CellSize();
    const sf::Color color = ToSfColor(VisualSettings::AbilityCellOutlineColor);
    const float outerR = std::min(cell_size[0], cell_size[1]) / 4.f;
    const float innerR = outerR / 2.f;

    sf::RectangleShape rectangle({float(cell_size[0]), float(cell_size[1])});
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(VisualSettings::CellOutlineThickness);
    rectangle.setOutlineColor(color);

    sf::CircleShape outer(outerR);
    outer.setOrigin({outerR, outerR});
    outer.setFillColor(sf::Color::Transparent);
    outer.setOutlineThickness(VisualSettings::CellOutlineThickness);
    outer.setOutlineColor(color);

    sf::CircleShape inner(innerR);
    inner.setOrigin({innerR, innerR});
    inner.setFillColor(color);

    for (const auto& cell : cells){
        const sf::Vector2f topLeft{float(cell.X() * cell_size[0] + VisualSettings::MapMarginLeft),
                                   float(cell.Y() * cell_size[1] + VisualSettings::MapMarginTop)};
        const sf::Vector2f center = topLeft + rectangle.getSize() / 2.f;

        rectangle.setPosition(topLeft);
        outer.setPosition(center);
        inner.setPosition(center);

        _window.draw(rectangle);
        _window.draw(outer);
        _window.draw(inner);
    }
}

void Visualizer::DrawStatus(StatusType statusType,const std::vector<int>& cell_size,Position pos,int counter,int position){
    sf::Sprite burning (_status_texture, sf::IntRect({0,  0}, {32, 32}));
    sf::Sprite slow    (_status_texture, sf::IntRect({32, 0}, {32, 32}));
    sf::Sprite overload(_status_texture, sf::IntRect({64, 0}, {32, 32}));
    sf::Sprite shield  (_status_texture, sf::IntRect({96, 0}, {32, 32}));

    sf::Sprite* status;
    float scale = 1.5*counter;
    if (modes[_cur_mode] == "standart" or modes[_cur_mode] == "statuses"){
        switch (statusType)
        {
        case StatusType::sBurn:
            status = &burning;
            break;
        case StatusType::sSlowth:
            status = &slow;
            break;
        case StatusType::sShield:
            status = &shield;
            break;
        case StatusType::sOverload:
            status = &overload;
            break;
        default:
            break;
        }
        status->setOrigin({status->getLocalBounds().size.x/2,status->getLocalBounds().size.y/2});
        status->setScale({cell_size[0]/(32.f*scale),cell_size[1]/(32.f*scale)});

        if (counter == 1){
            status->setPosition({pos.X() + cell_size[0]/2.f,pos.Y()+cell_size[1]/2.f});
        }
        else if (counter == 2){
            if (position == 1){
                status->setPosition({pos.X() + cell_size[0]/4.f,pos.Y()+cell_size[1]/2.f});
            }
            else {status->setPosition({pos.X() + 3*cell_size[0]/4.f,pos.Y()+cell_size[1]/2.f});}
        }
        else if (counter == 3){
            if (position == 1){
                status->setPosition({pos.X() + cell_size[0]/4.f,pos.Y()+cell_size[1]/4.f});
            }
            else if (position == 2){
                status->setPosition({pos.X() + 3*cell_size[0]/4.f,pos.Y()+cell_size[1]/4.f});
            }
            else if (position == 3){
                status->setPosition({pos.X() + 3*cell_size[0]/4.f,pos.Y()+3*cell_size[1]/4.f});
            }
        }
        else if (counter == 4){
            if (position == 1){
                status->setPosition({pos.X() + cell_size[0]/4.f,pos.Y()+cell_size[1]/4.f});
            }
            else if (position == 2){
                status->setPosition({pos.X() + 3*cell_size[0]/4.f,pos.Y()+cell_size[1]/4.f});
            }
            else if (position == 3){
                status->setPosition({pos.X() + 3*cell_size[0]/4.f,pos.Y()+3*cell_size[1]/4.f});
            }
            else if (position == 4){
                status->setPosition({pos.X() + cell_size[0]/4.f,pos.Y()+3*cell_size[1]/4.f});
            }
        }
        _window.draw(*status); 
    }
    
}
void Visualizer::DrawCells(const std::vector<int>& map_size, const std::vector<int>& cell_size,
                           const std::vector<std::vector<Cell>>& grid) {
    sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
    rectangle.setOutlineThickness(VisualSettings::CellOutlineThickness);

    for (int i = 0; i < map_size[1]; i++) {
        for (int j = 0; j < map_size[0]; j++) {
            const Cell& cell = grid[i][j];
            int x = j * cell_size[0] + VisualSettings::MapMarginLeft;
            int y = i * cell_size[1] + VisualSettings::MapMarginTop;

            bool visible = cell.GetVisible();
            bool seen = visible || cell.GetExplored();
            const unsigned char alpha = visible ? VisualSettings::VisibleAlpha : VisualSettings::ExploredAlpha;

            sf::Color fill = ToSfColor(VisualSettings::TransparentColor);
            if (seen) {
                if (cell.GetFactory() == true && (modes[_cur_mode] == "standart" or modes[_cur_mode] == "enemy")) {
                    auto factory_color = VisualSettings::FactoryColor;
                    factory_color.alpha = alpha;
                    fill = ToSfColor(factory_color);
                }
                else if (cell.GetCost() == CellSettings::ImpassableCost) {
                    if (modes[_cur_mode] == "standart" or modes[_cur_mode] == "blocked"){
                        DrawCross(x, y, cell_size[0], cell_size[1], alpha);
                    }
                }
                else if (cell.GetCost() != CellSettings::DefaultMoveCost) {
                    auto difficult_cell_color = VisualSettings::DifficultCellColor;
                    difficult_cell_color.alpha = alpha;
                    if (modes[_cur_mode] == "standart" or modes[_cur_mode] == "blocked"){
                        fill = ToSfColor(difficult_cell_color);
                    }
                }
                if (cell.GetStatusesCount() != 0 && (modes[_cur_mode] == "standart" or modes[_cur_mode] == "statuses")){
                    for (int i = 0;i<cell.GetStatusesCount();i++){
                        DrawStatus(cell.GetStatuses()[i],cell_size,{x,y},cell.GetStatusesCount(),i+1);
                    }
                }
                    
            }

            rectangle.setPosition({float(x), float(y)});
            rectangle.setFillColor(fill);
            auto outline_color = VisualSettings::CellOutlineColor;
            outline_color.alpha = visible ? VisualSettings::VisibleAlpha : VisualSettings::HiddenOutlineAlpha;
            outline_color.alpha = _game.GetCellsInRange().empty() ? outline_color.alpha : outline_color.alpha/3;
            rectangle.setOutlineColor(ToSfColor(outline_color));
            _window.draw(rectangle);
        }
    }
}