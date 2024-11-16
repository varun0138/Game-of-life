#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Game.hpp"

Game::Game() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Game of Life", sf::Style::Close | sf::Style::Titlebar);

    if(!m_font.loadFromFile("./Fonts/Retron2000.ttf")) {
        std::cerr << "Error loading font file!!" << std::endl;
    }

    m_grid = std::make_unique<Grid>(m_gridPosition, m_gridSize, m_rows, m_cols);

    m_sizeLabel = std::make_unique<Label>(m_font, sf::Vector2f(850.0f, 50.0f), 30, "", LIGHT);
    m_sizeSlider = std::make_unique<Slider>(sf::Vector2f(850.0f, 100.0f), sf::Vector2f(400.0f, 23.0f), 1.0f, 5, 70, 1, LIGHT);
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

    if(m_sizeSlider->isHandleMoved()) {
        m_grid->setUp(m_sizeSlider->getCurrentValue(), m_sizeSlider->getCurrentValue());
        m_sizeLabel->caption = "SIZE: " + std::to_string(m_sizeSlider->getCurrentValue());
    }
}

void Game::render() {
    m_window.clear(sf::Color(29, 29, 29, 255));

    m_grid->draw(m_window);

    m_sizeLabel->draw(m_window);
    m_sizeSlider->draw(m_window);

    m_window.display();
}

