#include "map.h"
#include "cell.h"
#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

auto MakeCross(float pos_x, float pos_y,int width, int height){
    sf::VertexArray lines(sf::PrimitiveType::Lines, 4);
    lines[0].position = {pos_x, pos_y};
    lines[1].position = {pos_x + width,pos_y+height};
    lines[2].position = {pos_x+width, pos_y};
    lines[3].position = {pos_x,pos_y+height};
    return lines;
}
int main(){
    // auto game = Game(3);
    // auto map = game.GetMap();
    // auto map_size = map.GetSize();
    // auto cell_size = map.CalculateCellSize({1000,1000});
    // auto grid = map.GetGrid();
    float x;
    float y;
    vector<sf::RectangleShape> rects;
    vector<sf::VertexArray> crosses;
    for (int i = 0; i < map_size[1]; i++){
        for (int j = 0; j < map_size[0]; j++){
            sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
            cout << "Cell[" << i << "][" << j << "] - Passible: " << grid[i][j].GetPassible() << ", Occupied: " << grid[i][j].GetOccupied() << endl;
            x = (j*cell_size[0] + 5);
            y = (i*cell_size[1] + 5);
            rectangle.setPosition({x,y});
            if (grid[i][j].GetPassible() == true){
                crosses.push_back(MakeCross(x,y,cell_size[0],cell_size[1]));
            }
            else if(grid[i][j].GetOccupied() == true){
                rectangle.setFillColor(sf::Color::Red);
            }
            rectangle.setFillColor(sf::Color::Transparent);
            rectangle.setOutlineThickness(1.f);
            rectangle.setOutlineColor(sf::Color::Green);
            rects.push_back(rectangle);
        }
    }
    
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "main");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        for (const auto rect : rects){
            window.draw(rect);
        }
        for (const auto arr: crosses){
            window.draw(arr);
        }
        window.display();
    }


    return 0;
}