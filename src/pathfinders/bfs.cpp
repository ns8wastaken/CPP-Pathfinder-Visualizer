#include "bfs.hpp"


void BFS::reset()
{
    queue.clear();
    queue.push_back(start);
    visited.clear();
    visited.insert(start);

    path.clear();

    searching = false;
}


// 0 = Nothing happened
// 1 = Path was found
// 2 = No path available
char BFS::stepSearch()
{
    const int16_t queueSize = queue.size();

    // Loop though every element in queue
    for (int i = 0; i < queueSize; i++) {
        Cell* current_cell = queue[0];
        queue.pop_front();

        // Stop if the path is found
        if (current_cell == end) return 1;

        // Get neighbors
        std::vector<Cell*> neighbors = getNeighbors(current_cell);

        for (Cell* neighbor : neighbors) {
            // If neighbor is not in visited set then add it
            if (visited.count(neighbor) == 0) {
                neighbor->parent = current_cell;
                queue.push_back(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    // Return 2 if no possible path
    if (queue.size() == 0) return 2;

    return 0;
}


void BFS::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(Settings::TileSize, Settings::TileSize));

    rect.setFillColor(Colors::Visited);

    // Draw all visited cells
    for (const Cell* cell : visited) {
        rect.setPosition(cell->index.x * Settings::TileSize, cell->index.y * Settings::TileSize);
        window.draw(rect);
    }

    rect.setFillColor(Colors::Search);

    // Draw all cells in queue
    for (const Cell* cell : queue) {
        rect.setPosition(cell->index.x * Settings::TileSize, cell->index.y * Settings::TileSize);
        window.draw(rect);
    }

    Pathfinder::draw(window);
}
