#include "map.h"
#include "cell.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
int main(){
    auto game_map = Map(5, 7 , 15); 
    std::vector cell_size =  game_map.CalculateCellSize({500,500});
    auto grid = game_map.CreateGrid();
    auto map_size = game_map.GetSize();
    // visual
    //auto MakeCross(float pos_x, float pos_y,int width, int height){
        
    //}
    float x;
    float y;
    vector<sf::RectangleShape> rects;
     for (int i = 0; i < map_size[1]; i++){
            for (int j = 0; j < map_size[0]; j++){
            sf::RectangleShape rectangle(sf::Vector2f(cell_size[0], cell_size[1]));
            x = (j*cell_size[0] + 5);
            y = (i*cell_size[1] + 5);
            rectangle.setPosition({x,y});
            if (grid[i][j].GetPassible() == true){
                rectangle.setFillColor(sf::Color::Red);
            }
            else{
                rectangle.setFillColor(sf::Color::Transparent);
            }
            rectangle.setOutlineThickness(1.f);
            rectangle.setOutlineColor(sf::Color::Green);
            rects.push_back(rectangle);
        }
    }
    
    sf::RenderWindow window(sf::VideoMode({510, 510}), "main");
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
        window.display();
    }


    return 0;
}