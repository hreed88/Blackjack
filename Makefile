make:
	g++ -std=c++17 game.cpp -I"include" -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_image -o Test
