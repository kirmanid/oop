#include"maze.h"

using namespace std;

Maze::Maze(uint rows, uint cols, bool defaultTile):
    tileMap(rows,vector<bool>(cols, defaultTile)),
    visitMap(rows, vector<bool>(cols, false))
{}

void flipTile(uint row, uint col){
    tileMap[row][col] = !tileMap[row][col];
}

bool getTile(uint row, uint col) const{
    return tileMap[row][col];
}

void visitTile(uint row, uint col){
    visitMap[row][col] = true;
}

bool checkVisited(uint row, uint col) const{
    return visitMap[row][col];
}

uint getNumRows() const{
    return tileMap.size();
}

uint getNumCols() const{
    return tileMap[0].size();
}