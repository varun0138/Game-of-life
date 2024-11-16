#include "Grid.hpp"

#include <SFML/Window/Mouse.hpp>
#include <iostream>

Grid::Grid(const sf::Vector2f& pos, const sf::Vector2f& size, unsigned int rows, unsigned int cols) 
    : m_pos(pos), m_size(size) {
    
    setUp(rows, cols);
}

void Grid::setUp(unsigned int rows, unsigned int cols) {
    m_rows = rows;
    m_cols = cols;

    m_cellSize = { m_size.x / m_cols, m_size.y / m_rows };
    m_cells = std::vector<std::vector<State>>(m_rows, std::vector<State>(m_cols, DEAD));
}

void Grid::setState(unsigned int row, unsigned int col, State state) {
    if(validCoords(row, col)) {
        m_cells[row][col] = state;
    } 
}

void Grid::update(const sf::Vector2i& mousePos) {
    const unsigned int row = (mousePos.y - m_pos.y) / m_cellSize.y;
    const unsigned int col = (mousePos.x - m_pos.x) / m_cellSize.x;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && validCoords(row, col)) {
        setState(row, col, ALIVE);
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && validCoords(row, col)) {
        setState(row, col, DEAD);
    }
}

bool Grid::validCoords(unsigned int row, unsigned int col) {
    if(0 <= row && row < m_rows && 0 <= col && col < m_cols) {
        return true;
    }
    return false;
}

State Grid::getState(unsigned int row, unsigned int col) {
    if(validCoords(row, col)) {
        return m_cells[row][col];
    }
    return DEAD;
}

void Grid::draw(sf::RenderTarget& target) {
    for(unsigned int y = 0; y < m_rows; y++) {
        for(unsigned int x = 0; x < m_cols; x++) {
            m_cell.setPosition(sf::Vector2f(x * m_cellSize.x + m_pos.x, y * m_cellSize.y + m_pos.y));
            m_cell.setSize(sf::Vector2f(m_cellSize.x - 1, m_cellSize.y - 1));

            switch(m_cells[y][x]) {
                case DEAD:
                    m_cell.setFillColor(sf::Color(55, 55, 55, 255));
                    break;

                case ALIVE:
                    m_cell.setFillColor(sf::Color(138, 204, 116, 255));
                    break;
            }

            target.draw(m_cell);
        }
    }
}