#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "Grid.hpp"
#include "Gui/Slider.hpp"
#include "Gui/Label.hpp"
#include "Gui/Button.hpp"

class Game {
private:
    const unsigned int m_windowWidth = 1300;
    const unsigned int m_windowHeight = 820;

    sf::Vector2f m_gridPosition = { 10.0f, 10.0f };
    sf::Vector2f m_gridSize = { 800.0f, 800.f };

    unsigned int m_rows = 30;
    unsigned int m_cols = 30;

    sf::RenderWindow m_window;
    sf::Font m_font;
    std::unique_ptr<Grid> m_grid;

    std::unique_ptr<Label> m_sizeLabel;
    std::unique_ptr<Slider> m_sizeSlider;

    std::unique_ptr<Button> m_startButton;
    std::unique_ptr<Button> m_pauseButton;
    std::unique_ptr<Button> m_resetButton;
    std::unique_ptr<Button> m_noiseButton;

    bool m_simulationStarted = false;

    void startSimulation();
    unsigned int countNeighbours(const std::vector<std::vector<State>>& cells, unsigned int row, unsigned int col);

    void userInput();
    void update();
    void render();

public:
    Game();
    void run();
};