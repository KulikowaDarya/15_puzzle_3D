#ifndef GAME_HPP
#define GAME_HPP
#include <map>
#include "./Block.hpp"
#include "./Board.hpp"

class Game {
    private:
        map<string, bool> is_show;
    public:
        static const int NEW_GAME = 17;
        static const int EXIT = 18;
        static const int RESTART = 20;
        static const int MENU = 21;
        int ind;
        Board board;
        Block menu;
        Block victory;
        Game();
        bool Is_Show(string);
        void Switch(string, string);
};

Game :: Game() {
    ind = 1;
    board = Board(ind, "cube.txt");
    menu = Block(2, 1, ind, "parallelipiped.txt");
    victory = Block(3, 1, ind, "parallelipiped.txt");
    is_show["menu"] = 1;
    is_show["board"] = 0;
    is_show["victory"] = 0;
}

bool Game :: Is_Show(string name) {
    if (is_show.find(name) != is_show.end()) {
        return is_show[name];
    }
    return 0;
}

void Game :: Switch(string from, string to) {
    if (is_show.find(from) != is_show.end() && is_show.find(to) != is_show.end()) {
        is_show[from] = 0;
        is_show[to] = 1;
    }
}

#endif