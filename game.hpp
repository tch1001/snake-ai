#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <cstdlib>
#define OK 0
#define OUT_OF_BOUNDS 1
#define EAT_OWN_TAIL 2


using namespace std;

typedef pair<int, int> pi;
class GameState{
	public:
	char **board;
	pi head, apple;
	int width, height;
	deque<pi> tails;
	GameState(int width, int height, pi head, pi apple, deque<pi> tails);
	void display();
};


class Game{
	public:
	int width, height;
	vector<GameState> history;
	vector<char> moves;
	Game(int width, int height);
	int try_move(GameState *g, char move);
	int make_move(char move);
	void display();
};