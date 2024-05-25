#pragma once
#include "pathfinder.hpp"

#include <deque>
#include <unordered_set>


class BFS : public Pathfinder
{
private:
    std::deque<Cell*> queue{ start };
    std::unordered_set<Cell*> visited{ start };

public:
    BFS(Grid* _grid, const int* _cost_ortho, const int* _cost_diag)
        : Pathfinder(_grid, _cost_ortho, _cost_diag)
    {
        use_diagonals = false;
        reset();
    }

    void reset() override;

    void draw(sf::RenderWindow& window) override;
    char stepSearch() override;
};
