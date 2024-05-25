#pragma once
#include "../grid.hpp"
#include "../settings.hpp"

#include <array>


class Pathfinder
{
protected:
    Grid* grid;
    const int* cost_orthogonal;
    const int* cost_diagonal;

    sf::Clock clock;

    Cell* start;
    Cell* end;

    bool use_diagonals = true;
    bool searching = false;

    const std::array<sf::Vector2i, 4> neighbor_offsets_ortho = {
        sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 0)
    };

    const std::array<sf::Vector2i, 4> neighbor_offsets_diag = {
        sf::Vector2i(-1, -1), sf::Vector2i(1, -1), sf::Vector2i(1, 1), sf::Vector2i(-1, 1),
    };

    std::vector<Cell*> path{};

public:
    Pathfinder(Grid* _grid, const int* _cost_ortho, const int* _cost_diag)
        : grid(_grid), cost_orthogonal(_cost_ortho), cost_diagonal(_cost_diag)
    {
        start = grid->getCell(0, 0);
        end = grid->getCell(grid->size_x - 1, grid->size_y - 1);
    }

    virtual ~Pathfinder();

    virtual void reset();

    void startSearch();
    void stopSearch();
    bool isSearching();
    virtual char stepSearch();

    virtual void draw(sf::RenderWindow& window);

    void setStart(const uint16_t x, const uint16_t y);
    void setEnd(const uint16_t x, const uint16_t y);
    void setCellType(Cell* cell, const char type);

    void update();

    void findPath();

    std::vector<Cell*> getNeighbors(Cell* cell);
    int getCost(Cell* cell1, Cell* cell2);
};
