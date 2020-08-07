#ifndef CHASEHERO_H
#define CHASEHERO_H

#include "entitycontroller.h"

class ChaseHero : public EntityController {
private:
  // disallow copy constructor and assignment operator
  ChaseHero(const ChaseHero &);
  ChaseHero &operator=(const ChaseHero &);

public:
  ChaseHero();
  virtual ~ChaseHero();
  // return the proposed direction
  // return Direction::NONE if no hero exists
  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;

private:
  // Add your own private member functions...
    // find the closest entity with "h" (Hero) property
    // return nullptr if no Hero exists
    static Entity* findClosestHero(Game* game, Entity* entity);
    //check if an entity at position pos can move in direction dir
    static bool canMove(Game* game, Entity* entity, Position pos, Direction dir);
};

#endif // CHASEHERO_H
