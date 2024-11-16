#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "Grid.hpp"

class Game {
private:
    const unsigned int m_windowWidth = 1300;
    const unsigned int m_windowHeight = 800;

    sf::Vector2f m_gridPosition = { 5.0f, 5.0f };
    sf::Vector2f m_gridSize = { 750.0f, 750.f };

    unsigned int m_rows = 30;
    unsigned int m_cols = 30;

    sf::RenderWindow m_window;
    std::unique_ptr<Grid> m_grid;
    
    void userInput();
    void update();
    void render();

public:
    Game();
    void run();
};