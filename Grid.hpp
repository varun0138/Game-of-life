#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

enum State: unsigned char {
    DEAD, ALIVE
};

class Grid {
private:
    sf::Vector2f m_pos;
    sf::Vector2f m_size;
    unsigned int m_rows;
    unsigned int m_cols;

    sf::RectangleShape m_cell;
    sf::Vector2f m_cellSize;

    std::vector<std::vector<State>> m_cells;

public:
    Grid(const sf::Vector2f& pos, const sf::Vector2f& size, unsigned int rows, unsigned int cols);

    void setUp(unsigned int rows, unsigned int cols);
    void setState(unsigned int row, unsigned int col, State state);

    bool validCoords(unsigned int row, unsigned int col);
    State getState(unsigned int row, unsigned int col);

    void draw(sf::RenderTarget& target);
};