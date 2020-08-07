//Yuntao Li
//yli346
//Weuxnau Lu
//wlu15
//Alex Zhang
//azhang41

//tmain.cpp
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include"game.h"
#include "basicgamerules.h"
#include "cursesui.h"

int main(int argc, char* argv[]) {
    const char* filename;
    if (argc < 2) {
        std::cerr << "Error: Need filename" << std::endl;
        return 1;
    }
    filename = argv[1];

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open maze file" << std::endl;
        return 1;
    }

    Game* game = Game::loadGame(in);
    if (!game) {
        std::cerr << "Error: Invalid game file" << std::endl;
        return 1;
    }

    game->setUI(new CursesUI());
    game->setGameRules(new BasicGameRules());

    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    game->gameLoop();
    endwin();

    delete game;

    
    return 0;
}
