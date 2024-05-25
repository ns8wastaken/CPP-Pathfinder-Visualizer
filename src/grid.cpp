#include "grid.hpp"

const std::array<sf::Color, 3> Grid::colors = {
    Colors::Empty,
    Colors::Wall,
    Colors::Checkpoint
};


Cell* Grid::getCell(int x, int y)
{
    return &grid[y][x];
}


void Grid::resetCellCosts()
{
    for (std::vector<Cell>& row : grid) {
        for (Cell& cell : row) {
            cell.f_cost = std::numeric_limits<uint16_t>::max();
            cell.g_cost = std::numeric_limits<uint16_t>::max();
            cell.h_cost = 0;
        }
    }
}


void Grid::setSize(const uint16_t _size_x, const uint16_t _size_y)
{
    size_x = _size_x;
    size_y = _size_y;

    grid.resize(_size_y);
    for (int y = 0; y < _size_y; y++) {
        grid[y].resize(_size_x);
        for (int x = 0; x < _size_x; x++) {
            grid[y][x].index = sf::Vector2i(x, y);
        }
    }
}


void Grid::drawGrid(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(Settings::TileSize, Settings::TileSize));

    for (std::vector<Cell>& row : grid) {
        for (Cell& cell : row) {
            if (cell.type != 0) {
                rect.setPosition(sf::Vector2f(cell.index.x * Settings::TileSize, cell.index.y * Settings::TileSize));
                rect.setFillColor(colors[cell.type]);
                window.draw(rect);
            }
        }
    }
}


void Grid::setCellType(const uint16_t x, const uint16_t y, char type)
{
    grid[y][x].type = type;
}
