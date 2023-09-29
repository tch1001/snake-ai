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
	GameState(int width, int height, pi head, pi apple, deque<pi> tails){
		this->width = width;
		this->height = height;
		this->head = head;
		this->apple = apple;
		this->tails = tails;
	}
	void display(){
		char **board = (char**) malloc(height * sizeof(char *));
		for(int i=0; i<height; ++i){
			board[i] = (char*) malloc(width * sizeof(char));
			for(int j=0; j<width; ++j) 
				board[i][j] = '.';
		}
		board[head.first][head.second] = 'H';
		for(int i=0; i<tails.size(); ++i)
			board[tails[i].first][tails[i].second] = (i%10)+'0';
		if(apple.first != -1 && apple.second != -1)
			board[apple.first][apple.second] = '@';
		for(int i=0; i<height; ++i){
			for(int j=0; j<width; ++j) 
				cout << board[i][j];
			cout << "\n";
		}
		cout << "\n";
	}
};


class Game{
	public:
	int width, height;
	vector<GameState> history;
	vector<char> moves;
	Game(int width, int height){
		this->width = width;
		this->height = height;
		deque<pi> nothing;
		// careful with pass by value or sth
		this->history.push_back(GameState(width, height, pi(0,0), pi(1,1), nothing));
	}
	int try_move(GameState *g, char move){ // dont push to history yet
		GameState last = *g;
		pi head = last.head;
		pi apple = last.apple;
		deque<pi> tails = last.tails;
		if(move == 'U') head.first -= 1;
		else if(move == 'D') head.first += 1;
		else if(move == 'L') head.second -= 1;
		else if(move == 'R') head.second += 1;
		if(head.first < 0 || head.first >= height || head.second < 0 || head.second >= width){
			return OUT_OF_BOUNDS;
		}
		for(int i=0; i<tails.size(); ++i){
			if(head.first == tails[i].first && head.second == tails[i].second){
				return EAT_OWN_TAIL;
			}
		}	
		tails.push_front(last.head);
		tails.pop_back();
		if(head.first == apple.first && head.second == apple.second){
			if(tails.empty()) tails.push_back(head);
			else tails.push_back(tails.back());
			// generate random apple
			apple.first = rand() % height;
			apple.second = rand() % width;
		}
		GameState next(width, height, head, apple, tails);
		*g = next;
		return OK;
	}
	int make_move(char move){
		GameState nextState = this->history.back();
		int trial = this->try_move(&nextState, move);
		if(trial != OK){
			if(trial == OUT_OF_BOUNDS) throw "OUT_OF_BOUNDS";
			if(trial == EAT_OWN_TAIL) throw "EAT_OWN_TAIL";
		}
		this->history.push_back(nextState);
		this->display();
		return OK;
	}
	void display(){
		this->history.back().display();
	}
};
void test(){
	Game game(20, 10);
	game.display();
	string moves = "";
	while(true){
		char move;
		cin >> move;
		moves += move;
		try{
			game.make_move(move);
		}catch(const char* msg){
			cout << msg << "\n";
			break;
		}
	}
}
