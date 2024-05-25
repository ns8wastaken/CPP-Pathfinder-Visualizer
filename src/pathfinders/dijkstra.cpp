#include "dijkstra.hpp"
#include <math.h>


void Dijkstra::reset()
{
    open.clear();
    open.push_back(start);
    closed.clear();
    closed.insert(start);

    grid->resetCellCosts();
    start->g_cost = 0;

    path.clear();

    searching = false;
}


// 0 = Nothing happened
// 1 = Path was found
// 2 = No path available
char Dijkstra::stepSearch()
{
    // Return 2 if no possible path
    if (open.empty()) return 2;

    std::vector<Cell*>::iterator current_cell_it = open.begin();
    Cell* current_cell = *current_cell_it;

    // Get cell with smallest g_cost
    for (std::vector<Cell*>::iterator it = open.begin(); it != open.end(); ++it) {
        Cell* cell = *it;
        if (cell->g_cost < current_cell->g_cost) {
            current_cell_it = it;
            current_cell = cell;
        }
    }

    open.erase(current_cell_it);
    closed.insert(current_cell);

    // Return 1 if path found
    if (current_cell == end) return 1;

    // Get neighbors
    std::vector<Cell*> neighbors = getNeighbors(current_cell);

    // Update neighbors
    for (Cell* neighbor : neighbors) {
        if (closed.count(neighbor)) continue;

        int new_g_cost = current_cell->g_cost + getCost(current_cell, neighbor);
        if (new_g_cost < neighbor->g_cost) {
            neighbor->parent = current_cell;
            neighbor->g_cost = new_g_cost;

            if (std::find(open.begin(), open.end(), neighbor) == open.end())
                open.push_back(neighbor);
        }
    }

    return 0;
}


void Dijkstra::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(Settings::TileSize, Settings::TileSize));

    rect.setFillColor(Colors::Visited);

    for (const Cell* cell : closed) {
        rect.setPosition(cell->index.x * Settings::TileSize, cell->index.y * Settings::TileSize);
        window.draw(rect);
    }

    rect.setFillColor(Colors::Search);

    for (const Cell* cell : open) {
        rect.setPosition(cell->index.x * Settings::TileSize, cell->index.y * Settings::TileSize);
        window.draw(rect);
    }

    Pathfinder::draw(window);
}
