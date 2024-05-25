#pragma once
#include "pathfinder.hpp"

#include <unordered_set>


class AStar : public Pathfinder
{
private:
    std::vector<Cell*> open{ start };
    std::unordered_set<Cell*> closed{ start };

public:
    AStar(Grid* _grid, const int* _cost_ortho, const int* _cost_diag)
        : Pathfinder(_grid, _cost_ortho, _cost_diag)
    {
        reset();
    }

    void reset() override;

    int h(Cell* cell);

    void draw(sf::RenderWindow& window) override;
    char stepSearch() override;
};
