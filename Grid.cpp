#include "Grid.hpp"

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

bool Grid::validCoords(unsigned int row, unsigned int col) {
    if(0 <= row && row < m_rows && 0 <= col && col < m_cols) {
        return true;
    }
    return false;
}

State Grid::getState(unsigned int row, unsigned int col) {
    return m_cells[row][col];
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
                    m_cell.setFillColor(sf::Color(0, 255, 0, 255));
                    break;
            }

            target.draw(m_cell);
        }
    }
}