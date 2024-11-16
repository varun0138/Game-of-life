#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>

#include "Game.hpp"

Game::Game() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Game of Life", sf::Style::Close | sf::Style::Titlebar);
    // m_window.setFramerateLimit(15);

    if(!m_font.loadFromFile("./Fonts/Retron2000.ttf")) {
        std::cerr << "Error loading font file!!" << std::endl;
    }

    m_grid = std::make_unique<Grid>(m_gridPosition, m_gridSize, m_rows, m_cols);

    m_sizeLabel = std::make_unique<Label>(m_font, sf::Vector2f(850.0f, 50.0f), 30, "", LIGHT);
    m_sizeSlider = std::make_unique<Slider>(sf::Vector2f(850.0f, 100.0f), sf::Vector2f(400.0f, 23.0f), 1.0f, 5, 70, 1, LIGHT);

    m_startButton = std::make_unique<Button>(m_font, sf::Vector2f(850.0f, 200.0f),  sf::Vector2f(180.0f, 70.0f), 1.0f, "START", LIGHT);
    m_resetButton = std::make_unique<Button>(m_font, sf::Vector2f(1080.0f, 200.0f), sf::Vector2f(180.0f, 70.0f), 1.0f, "RESET", LIGHT);
    m_pauseButton = std::make_unique<Button>(m_font, sf::Vector2f(850.0f, 300.0f), sf::Vector2f(180.0f, 70.0f), 1.0f, "PAUSE", LIGHT);
    m_noiseButton = std::make_unique<Button>(m_font, sf::Vector2f(1080.0f, 300.0f), sf::Vector2f(180.0f, 70.0f), 1.0f, "NOISE", LIGHT);
}

void Game::run() {
    while(m_window.isOpen()) {
        userInput();
        update();
        render();
    }
}

void Game::userInput() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;

            default:
                break;
        }
    }
}

void Game::update() {
    const sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
    m_grid->update(mousePos);

    m_rows = m_cols = m_sizeSlider->getCurrentValue();

    if(m_sizeSlider->isHandleMoved() && !m_simulationStarted) {
        m_grid->setUp(m_rows, m_cols);
        m_sizeLabel->caption = "SIZE: " + std::to_string(m_rows);
    }

    if(m_startButton->buttonClicked(mousePos)) {
        m_simulationStarted = true;
    }
    else if(m_pauseButton->buttonClicked(mousePos)) {
        m_simulationStarted = false;
    }
    else if(m_resetButton->buttonClicked(mousePos) && !m_simulationStarted) {
        
    }
    else if(m_noiseButton->buttonClicked(mousePos) && !m_simulationStarted) {
        
    }

    if(m_simulationStarted) {
        startSimulation();
        m_sizeSlider->setMovement(false);
        sf::sleep(sf::milliseconds(100));
    }
    else {
        m_sizeSlider->setMovement(true);
    }
}

void Game::render() {
    m_window.clear(sf::Color(29, 29, 29, 255));

    m_grid->draw(m_window);

    m_sizeLabel->draw(m_window);
    m_sizeSlider->draw(m_window);

    m_startButton->draw(m_window);
    m_resetButton->draw(m_window);
    m_pauseButton->draw(m_window);
    m_noiseButton->draw(m_window);

    m_window.display();
}

void Game::startSimulation() {
    static std::vector<std::vector<State>> temp = std::vector<std::vector<State>>(m_rows, std::vector<State>(m_cols, DEAD));

    for(unsigned int y = 0; y < m_rows; y++) {
        for(unsigned int x = 0; x < m_cols; x++) {
            temp[y][x] = m_grid->getState(y, x);
        }
    }

    for(unsigned int y = 0; y < m_rows; y++) {
        for(unsigned int x = 0; x < m_cols; x++) {
            unsigned int neighbours = countNeighbours(temp, y, x);
            if(neighbours < 2 || neighbours > 3) {
                m_grid->setState(y, x, DEAD);
            }
            else if(neighbours == 3) {
                m_grid->setState(y, x, ALIVE);
            }
        }
    }
}

unsigned int Game::countNeighbours(const std::vector<std::vector<State>>& cells, unsigned int row, unsigned int col) {
    unsigned int count = 0;
    static const std::vector<sf::Vector2i> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };

    for(unsigned int i = 0; i < directions.size(); i++) {
        int neighbourRow = (row + directions[i].x + m_rows) % m_rows;
        int neighboutCol = (col + directions[i].y + m_cols) % m_cols;

        count += cells[neighbourRow][neighboutCol];
    }

    return count;
}