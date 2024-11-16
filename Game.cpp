#include <SFML/Window/Event.hpp>

#include "Game.hpp"

Game::Game() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "Game of Life", sf::Style::Close | sf::Style::Titlebar);

    m_grid = std::make_unique<Grid>(m_gridPosition, m_gridSize, m_rows, m_cols);
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

}

void Game::render() {
    m_window.clear(sf::Color(29, 29, 29, 255));

    m_grid->draw(m_window);

    m_window.display();
}

