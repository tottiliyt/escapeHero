//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//cursesui.cpp
#include "cursesui.h"
#include "game.h"
#include "maze.h"
#include "entity.h"
#include "tile.h"
#include <ncurses.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

CursesUI::CursesUI(): UI(), message(""), m_endgame(false) {
}

CursesUI::~CursesUI() {
}

Direction CursesUI::getMoveDirection() {

  int ch;
  bool input = false;
  
  while (!input){
    ch=getch();
    switch(ch){
    case 'u':
      endwin();
      return Direction::UP;
    case 'd':
      endwin();
      return Direction::DOWN;
    case 'l':
      endwin();
      return Direction::LEFT;
    case 'r':
      endwin();
      return Direction::RIGHT;
    }
  }  
	return Direction::NONE;
}

void CursesUI::displayMessage(const std::string& msg, bool endgame) {
	m_endgame=endgame; //to avoid unused parameter compiling warning
	message = msg;
}

void CursesUI::render(Game* game) {

	int width = game->getMaze()->getWidth();
	int height = game->getMaze()->getHeight();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Position current(x,y);
			Entity* entity = game->getEntityAt(current);
			if (entity == nullptr) { //no entity at current position, tile glyph should be printed
			  mvaddstr(y,x,game->getMaze()->getTile(current)->getGlyph().c_str());
			}
			else { //entity glyph should be printed
			  mvaddstr(y,x,entity->getGlyph().c_str());
			}
		}	
	}
	refresh();
	//print the message if exists
	if (message != "") { //a message exists
	  move(height+2,0);
	  clrtoeol();
	  printw(message.c_str());
		message = ""; //clear message
	}
	if (m_endgame){
	  move(height+4,0);
	  printw("Game is done, press 'q' to quit");
	  
	  int c;
	  while((c=getch())!='q'){
	    printw("");
	  }
	}
	
}
