#include <cstdlib>
#include "game.hpp"

string shortest_path_to_apple(pi head, pi apple){
    string ans = "";
    for(int i=0; i<apple.first-head.first; ++i) ans += "D";
    for(int i=0; i<head.second-apple.second; ++i) ans += "L";
    for(int i=0; i<apple.second-head.second; ++i) ans += "R";
    for(int i=0; i<head.first-apple.first; ++i) ans += "U";
    return ans;
}

int main(){
    Game game(10, 10);
    while(true){
        string moves = shortest_path_to_apple(game.history.back().head, game.history.back().apple);
        cout << "Trying moves: " << moves << endl;
        for(int i=0; i<moves.size(); ++i){
            GameState last = game.history.back();
            if(game.try_move(&last, moves[i]) != OK){
                string all = "UDLR";
                bool found = false;
                for(int j=0; j<4; ++j){
                    last = game.history.back();
                    if(game.try_move(&last, all[j]) == OK){
                        game.make_move(all[j]);
                        found = true;
                    }
                }
                if(found){
                    break;
                }else{
                    cout << "GAME OVER" << endl;
                    return 0;
                }
            }
            try {
                game.make_move(moves[i]);
            } catch (const char* msg) {
                cout << msg << endl;
                return 0;
            }
        }
    }
}