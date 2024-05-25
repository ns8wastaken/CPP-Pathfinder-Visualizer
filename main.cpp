#include <SFML/Graphics.hpp>

#include "src/settings.cpp"
#include "src/grid.cpp"

#include "src/pathfinders/pathfinder.cpp"
#include "src/pathfinders/bfs.cpp"
#include "src/pathfinders/dijkstra.cpp"
#include "src/pathfinders/astar.cpp"


void makeGridLines(std::array<sf::Vertex[2], Settings::SizeX + Settings::SizeY - 2>& lines)
{
    const int height = Settings::SizeY * Settings::TileSize;
    const int width = Settings::SizeX * Settings::TileSize;

    for (int i = 1; i < (int)Settings::SizeX; i++) {
        lines[i - 1][1] = sf::Vertex(sf::Vector2f(i * Settings::TileSize, 0), Colors::Lines);
        lines[i - 2][2] = sf::Vertex(sf::Vector2f(i * Settings::TileSize, height), Colors::Lines);
    }

    for (int i = 1; i < (int)Settings::SizeY; i++) {
        lines[i + Settings::SizeX - 2][1] = sf::Vertex(sf::Vector2f(0, i * Settings::TileSize), Colors::Lines);
        lines[i + Settings::SizeX - 3][2] = sf::Vertex(sf::Vector2f(width, i * Settings::TileSize), Colors::Lines);
    }
}


int main()
{
    // Init window
    sf::RenderWindow window(sf::VideoMode(Settings::SizeX * Settings::TileSize, Settings::SizeY * Settings::TileSize), "Pathfinder Visualizer", sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    sf::Image icon;
    icon.loadFromFile("src/pathfinder.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Init grid lines
    std::array<sf::Vertex[2], Settings::SizeX + Settings::SizeY - 2> gridLines;
    makeGridLines(gridLines);

    // Init stuff
    Grid* grid = new Grid(Settings::SizeX, Settings::SizeY);
    Pathfinder* pathfinder = new Dijkstra(grid, &Settings::cost_orthogonal, &Settings::cost_diagonal);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        break;
                    }

                    if (event.key.code == sf::Keyboard::Num1 && !pathfinder->isSearching()) {
                        const sf::Vector2i mpos = sf::Mouse::getPosition(window);
                        const sf::Vector2u wsize = window.getSize();

                        // If the mouse is in the screen set tile to the pathfinder's start
                        if ((unsigned)mpos.x < wsize.x && (unsigned)mpos.y < wsize.y) {
                            pathfinder->setStart(mpos.x / Settings::TileSize, mpos.y / Settings::TileSize);
                        }
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Num2 && !pathfinder->isSearching()) {
                        const sf::Vector2i mpos = sf::Mouse::getPosition(window);
                        const sf::Vector2u wsize = window.getSize();

                        // If the mouse is in the screen set tile to the pathfinder's end
                        if ((unsigned)mpos.x < wsize.x && (unsigned)mpos.y < wsize.y) {
                            pathfinder->setEnd(mpos.x / Settings::TileSize, mpos.y / Settings::TileSize);
                        }
                        break;
                    }
                    else if (event.key.code == sf::Keyboard::Space) {
                        if (!pathfinder->isSearching()) pathfinder->startSearch();
                    }
                    else if (event.key.code == sf::Keyboard::Backspace) {
                        pathfinder->reset();
                    }

                default:
                    break;
            }
        }

        // Dont do stuff if the window is not in focus
        if (!window.hasFocus()) continue;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pathfinder->isSearching()) {
            const sf::Vector2i mpos = sf::Mouse::getPosition(window);
            const sf::Vector2u wsize = window.getSize();

            // If the mouse is in the screen set tile to wall
            if ((unsigned)mpos.x < wsize.x && (unsigned)mpos.y < wsize.y) {
                pathfinder->setCellType(grid->getCell(mpos.x / Settings::TileSize, mpos.y / Settings::TileSize), 1);
            }
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !pathfinder->isSearching()) {
            const sf::Vector2i mpos = sf::Mouse::getPosition(window);
            const sf::Vector2u wsize = window.getSize();

            // If the mouse is in the screen set tile to empty
            if ((unsigned)mpos.x < wsize.x && (unsigned)mpos.y < wsize.y) {
                pathfinder->setCellType(grid->getCell(mpos.x / Settings::TileSize, mpos.y / Settings::TileSize), 0);
            }
        }

        window.clear(sf::Color(255, 255, 255));

        // Pathfinder stuff
        pathfinder->update();
        pathfinder->draw(window);

        // Draw grid lines
        for (const std::array<sf::Vertex[2], Settings::SizeX + Settings::SizeY - 2>::value_type & line : gridLines)
            window.draw(line, 2, sf::Lines);

        window.display();
    }

    delete pathfinder;
    return 0;
}
