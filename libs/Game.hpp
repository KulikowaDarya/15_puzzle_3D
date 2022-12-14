#ifndef GAME_HPP
#define GAME_HPP
#include "./Block.hpp"
#include "./Board.hpp"

class Game {
    public:
        int ind;
        Board board;
        Block menu;
        Block rule;
        Block victory;
        Game();
};

Game :: Game() {
    ind = 1;
    board = Board(ind, "cube.txt");
    // menu = Block(3, 1, ind, "parallelipiped.txt");
    // rule = Block(1, 1, ind, "cube.txt");
    // victory = Block(3, 1, ind, "parallelipiped.txt");
}
#endif