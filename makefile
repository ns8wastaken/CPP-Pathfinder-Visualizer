CPP = g++ -g -Wall -pedantic -Wextra main.cpp
DEPS_SFML = -L C:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

HEADERS = -I src/headers

DEPS_PATHFINDER = main.cpp src/settings.cpp src/grid.cpp src/pathfinder.cpp src/bfs.cpp src/pathfinder.png src/Ubuntu-R.ttf
DEPS_STATIC_SFML = -D SFML_STATIC -L lib_sfml_static -L C:/SFML/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
# -lopengl32 -lfreetype -lwinmm -lgdi32

all: compile finish open

compile:
	$(CPP) -I C:/SFML/include -o main.exe $(DEPS_SFML)

compile-static:
	$(CPP) -I C:/SFML/include $(HEADERS) -o main.exe $(DEPS_PATHFINDER) $(DEPS_STATIC_SFML)

finish:
	@echo -e "\033[0;32m== Done ==\e[0m"

open:
	@echo -e "\033[0;94mRunning exe...\e[0m"
	@main.exe
