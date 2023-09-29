.PHONY: all

game.o: game.cpp game.hpp
	g++ -c game.cpp -o game.o

run: game.o direct-to-food.cpp
	g++ -c direct-to-food.cpp -o direct-to-food.o
	g++ -o a.out game.o direct-to-food.o 
	./a.out

debug: game 
	gdb a.out
