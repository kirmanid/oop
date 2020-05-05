#include"maze.h"

using namespace std;

Maze::Maze(uint rows, uint cols, bool defaultTile):
    tileMap(rows,vector<bool>(cols, defaultTile)),
    visitMap(rows, vector<bool>(cols, false))
{}

void Maze::setile(bool tile, uint row, uint col){
    tileMap[row][col] = tile;
}

bool Maze::getTile(uint row, uint col) const{
    return tileMap[row][col];
}

void Maze::visitTile(uint row, uint col){
    visitMap[row][col] = true;
}

bool Maze::checkVisited(uint row, ui
nt col) const{
    return visitMap[row][col];int de
}

uint Maze::getNumRows() const{
    return tileMap.size();
}

uint Maze::getNumCols() const{
    return tileMap[0].size();
}

bool Maze::checkValidWall(uint row1, uint col1, uint row2, uint col2) const{
    if (row1 >= getNumRows() || row2 >= getNumRows()){
        return false;
    }
    if (col1 >= getNumCols() || col2 >+ getNumCols()){
        return false;
    }

    int colDiff = abs(col1-col2);
    int rowDiff = abs(row1-row2);
    if (colDiff == 2 || rowDiff == 2){
        return true;
    } else {
        return false;
    }
}

void Maze::createWall(uint row1, uint col1, uint row2, uint col2){
    if (!checkValidWall(row1, col1, row2, col2)){
        return;
    }
    tileMap[(row1+row2)/2][(col1+col2)/2] = true;
}

bool Maze::wallExists(uint row1, uint col1, uint row2, uint col2) const{
    if (!checkValidWall(row1, col1, row2, col2)){
        return;
    }
    return tileMap[(row1+row2)/2] [(col1+col2)/2];
}