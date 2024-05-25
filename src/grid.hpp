#pragma once
#include <vector>
#include <array>

#include "cell.hpp"
#include "settings.hpp"


class Grid
{
private:
    std::vector<std::vector<Cell>> grid{};

    static const std::array<sf::Color, 3> colors;

public:
    uint16_t size_x;
    uint16_t size_y;

    Grid(uint16_t _size_x, uint16_t _size_y) : size_x(_size_x), size_y(_size_y)
    {
        grid.resize(_size_y);
        for (int y = 0; y < _size_y; y++) {
            grid[y].resize(_size_x);
            for (int x = 0; x < _size_x; x++) {
                grid[y][x].index = sf::Vector2i(x, y);
            }
        }
    }

    Cell* getCell(int x, int y);

    void resetCellCosts();

    void drawGrid(sf::RenderWindow& window);

    void setSize(const uint16_t size_x, const uint16_t size_y);

    /*
    @param type 0 Empty
    @param type 1 Wall
    @param type 2 Checkpoint
    */
    void setCellType(const uint16_t x, const uint16_t y, char type);
};
