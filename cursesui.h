#ifndef CURSESUI_H
#define CURSESUI_H

#include "ui.h"

// A CursesUI object implements the virtual functions of UI
class CursesUI : public UI {
private:
  // TODO: add fields
    std::string message;
    bool m_endgame;
  // copy constructor and assignment operator disallowed
  CursesUI(const CursesUI &);
  CursesUI &operator=(const CursesUI &);

public:
  CursesUI();
  virtual ~CursesUI();

  virtual Direction getMoveDirection();

  virtual void displayMessage(const std::string &msg, bool endgame);

  virtual void render(Game *game);
};

#endif // TEXTUI_H
