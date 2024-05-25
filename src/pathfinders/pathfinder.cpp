#include "pathfinder.hpp"


Pathfinder::~Pathfinder() {}


void Pathfinder::reset() {}


bool Pathfinder::isSearching() { return searching; }


void Pathfinder::draw(sf::RenderWindow& window)
{
    grid->drawGrid(window);

    sf::RectangleShape rect(sf::Vector2f(Settings::TileSize, Settings::TileSize));
    rect.setFillColor(Colors::Path);

    for (Cell* cell : path) {
        rect.setPosition(cell->index.x * Settings::TileSize, cell->index.y * Settings::TileSize);
        window.draw(rect);
    }

    rect.setPosition(start->index.x * Settings::TileSize, start->index.y * Settings::TileSize);
    rect.setFillColor(Colors::Start);
    window.draw(rect);

    rect.setPosition(end->index.x * Settings::TileSize, end->index.y * Settings::TileSize);
    rect.setFillColor(Colors::End);
    window.draw(rect);
}


void Pathfinder::startSearch() { searching = true; }
void Pathfinder::stopSearch() { searching = false; }


char Pathfinder::stepSearch() { return 0; }


void Pathfinder::update()
{
    if (searching && clock.getElapsedTime().asMilliseconds() > 50) {
        clock.restart();
        char search_state = stepSearch();

        if (search_state == 1) {
            searching = false;
            findPath();
        }
        else if (search_state == 2) {
            searching = false;
        }
    }
}


void Pathfinder::setCellType(Cell* cell, const char type)
{
    // Set type if the selected cell is not the start or end
    if (start != cell && end != cell) {
        grid->setCellType(cell->index.x, cell->index.y, type);
    }
}


void Pathfinder::setStart(const uint16_t x, const uint16_t y)
{
    Cell* new_start = grid->getCell(x, y);
    if (new_start->index != end->index) {
        new_start->type = 0;
        start = new_start;
        reset();
    }
}


void Pathfinder::setEnd(const uint16_t x, const uint16_t y)
{
    Cell* new_end = grid->getCell(x, y);
    if (new_end->index != start->index) {
        new_end->type = 0;
        end = new_end;
    }
}


void Pathfinder::findPath()
{
    Cell* current_cell = end;
    path.push_back(current_cell);

    while (current_cell != start) {
        current_cell = current_cell->parent;
        path.push_back(current_cell);
    }
}


std::vector<Cell*> Pathfinder::getNeighbors(Cell* cell)
{
    std::vector<Cell*> neighbors;

    // Check all neighboring positions + diagonals if necessary
    for (const sf::Vector2i& neighbor_offset : neighbor_offsets_ortho) {
        const sf::Vector2u new_pos = sf::Vector2u(cell->index.x + neighbor_offset.x, cell->index.y + neighbor_offset.y);
        if (new_pos.x < grid->size_x && new_pos.y < grid->size_y) {
            Cell* new_cell = grid->getCell(new_pos.x, new_pos.y);
            if (new_cell->type != 1)
                neighbors.push_back(new_cell);
        }
    }
    if (use_diagonals) {
        for (const sf::Vector2i& neighbor_offset : neighbor_offsets_diag) {
            const sf::Vector2u new_pos = sf::Vector2u(cell->index.x + neighbor_offset.x, cell->index.y + neighbor_offset.y);
            if (new_pos.x < grid->size_x && new_pos.y < grid->size_y) {
                Cell* new_cell = grid->getCell(new_pos.x, new_pos.y);
                if (new_cell->type != 1)
                    neighbors.push_back(new_cell);
            }
        }
    }

    return neighbors;
}


int Pathfinder::getCost(Cell* cell1, Cell* cell2)
{
    return ((cell1->index.x == cell2->index.x) || (cell1->index.y == cell2->index.y)) ? *cost_orthogonal : *cost_diagonal;
}
