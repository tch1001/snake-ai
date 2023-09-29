.PHONY: all

game: game.cpp
	g++ -o game.out game.cpp -g

run: game
	./game.out

debug: game
	gdb game.out
