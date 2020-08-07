#ifndef ASTARCHASEHERO_H
#define ASTARCHASEHERO_H

#include "entitycontroller.h"
#include <vector>

//g is the exact distance of the path from source to a certain position
//h is the estimated distance from the certain position to destination (using distanceFrom function)
//f = g + h
struct Node {
    Position pos; //position of current node
    int f, g, h;
    Node* prev; //previous node in the path
};

class AStarChaseHero : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  AStarChaseHero(const AStarChaseHero &);
  AStarChaseHero &operator=(const AStarChaseHero &);

public:
  AStarChaseHero();
  virtual ~AStarChaseHero();
 
  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;

private:
    // find the closest entity with "h" (Hero) property
    // return nullptr if no Hero exists
    static Entity* findClosestHero(const Game* game, const Entity* entity);
    // create a dynamically allocated Node
    static Node* create_Node(Position pos, int f = 0, int g = 0, int h = 0, Node* prev = nullptr);
    // find the node with lowest f in openNode, remove it from openNode and add it to closedNode
    static Node* findLowestF(std::vector<Node*>& openNode, std::vector<Node*>& closedNode);
    //find a node according to its Posotion and return its index within the vector<Node*>
    //return -1 if not found
    static int findNode(Position pos, std::vector<Node*>& nodes);
    // update a neighbour node
    // skip the node if it cannot be moved onto or if it's in closedNode
    // update fields of the node if it's already in openNode and new path to it has smaller f
    // add the node to openNode if it's neither in openNode or closedNode
    static void updateNode(Game* game, Entity* entity, Node* current, Direction dir, Position target, std::vector<Node*>& openNode, std::vector<Node*>& closedNode);
    //get movement direction from closedNode if path is found
    static Direction getDirectionFromClosedNode(std::vector<Node*>& closedNode);
};

#endif // ASTARCHASEHERO_H
