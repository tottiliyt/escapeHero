//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//textui.cpp
#include "textui.h"
#include "game.h"
#include "maze.h"
#include "entity.h"
#include "tile.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

TextUI::TextUI(): UI(), message("") {
}

TextUI::~TextUI() {
}

Direction TextUI::getMoveDirection() {
	bool input = false;
	while (!input) {
		cout << "Your move (u/d/l/r): ";
		string str;
		getline(cin, str);
		if (str == "u") {
			return Direction::UP;
		}
		else if (str == "d") {
			return Direction::DOWN;
		}
		else if (str == "l") {
			return Direction::LEFT;
		}
		else if (str == "r") {
			return Direction::RIGHT;
		}
		else {
			cout << "Unknown direction" << endl;
		}
	}
	return Direction::NONE;
}

void TextUI::displayMessage(const std::string& msg, bool endgame) {
	(void)endgame; //to avoid unused parameter compiling warning
	message = msg;
}

void TextUI::render(Game* game) {
	int width = game->getMaze()->getWidth();
	int height = game->getMaze()->getHeight();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Position current(x,y);
			Entity* entity = game->getEntityAt(current);
			if (entity == nullptr) { //no entity at current position, tile glyph should be printed
				cout << game->getMaze()->getTile(current)->getGlyph();
			}
			else { //entity glyph should be printed
				cout << entity->getGlyph();
			}
		}
		cout << endl;
	}
	//print the message if exists
	if (message != "") { //a message exists
		cout << ": " << message << endl;
		message = ""; //clear message
	}
}