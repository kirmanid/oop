#ifndef MAZE_H
#define MAZE_H

#include<iostream>
#include<vector>
#include<random>
#include<time.h> 

class Maze{
public:
    Maze(uint rows, uint cols, bool defaultTile);
    void createWall(uint row1, uint col1, uint row2, uint col2);
    bool wallExists(uint row1, uint col1, uint row2, uint col2) const;

    void setTile(bool tile, uint row, uint col);
    bool getTile(uint row, uint col) const;
    void visitTile(uint row, uint col);
    bool checkVisited(uint row, uint col) const;
    void generateMaze(int seed, uint iterations);
    uint getNumRows() const;
    uint getNumCols() const;
    void displayMaze() const;
    void makeUserMove();
private:
    std::vector<std::vector<bool>> tileMap;
    std::vector<std::vector<bool>> visitMap;
    std::vector<std::vector<bool>> oldTiles;
    uint solverRow;
    uint solverCol;
    bool checkValidWall(uint row1, uint col1, uint row2, uint col2) const;
};

#endif