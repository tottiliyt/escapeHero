//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//maze.cpp
#include "maze.h"
#include "position.h"
#include "tile.h"
#include "tilefactory.h"
#include<vector>
#include<iostream>

using std::vector;
using std::istream;
using std::fprintf;
using std::cout;


Maze::Maze(int width,int height):
  Width(width),Height(height),tile_collection(Width*Height){
}

Maze::~Maze(){

  for(Tile* obj: tile_collection){ delete obj; }
  tile_collection.clear();
}

int Maze::getWidth()const{
  return Width;
}

int Maze::getHeight()const{
  return Height;
}

bool Maze::inBounds(const Position &pos) const{
  return pos.getX()>=0&&pos.getX()<Width&&pos.getY()>=0&&pos.getY()<Height;
}

void Maze::setTile(const Position &pos,Tile *tile){
  int p=pos.getX()+pos.getY()*(Width);
  tile_collection[p]=tile;
}

const Tile *Maze::getTile(const Position &pos)const{
  return tile_collection[pos.getX()+pos.getY()*(Width)];
}

Maze* Maze::read(std::istream& in) {
    int x; int y; char c;
    if ((in >> x) && (in >> y) && x > 0 && y > 0) {
        TileFactory* fac = TileFactory::getInstance();
        Maze* new_maze = new Maze(x, y);
        //loop over the specified maze dimension
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (in >> c) {
                    //using tilefactory to change character into a tile

                    Tile* temp = fac->createFromChar(c);
                    //if createFromChar fails, return nullptr, otherwise set tile at position j,i
                    if (temp == nullptr) {
                        delete new_maze;
                        return nullptr;
                    }
                    else {
                        new_maze->setTile(Position(j, i), temp);
                    }
                }
                else { //the char is not read (maze does not match with its dimension)
                    delete new_maze;
                    return nullptr;
                }
            }
            in.get(c);
            if (c != '\n') { //dimension not match
                delete new_maze;
                return nullptr;
            }
        }
        return new_maze;
    }
    else { //dimension of the maze not specified, or have negative height or weight (invalid)
        return nullptr;
    }
}

