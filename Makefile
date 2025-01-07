make:
	g++ -std=c++17 game.cpp ./src/glad.c -I"include" -L"lib" -Wall -lSDL2main -lSDL2 -lSDL2_image -lGL -o Game.out
clean:
	rm *.o *.out
