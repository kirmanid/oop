#ifndef MAZE_H
#define MAZE_H

#include<vector>

class Maze{
public:
    Maze(uint rows, uint cols, bool defaultTile);
    void flipTile(uint row, uint col);
    bool getTile(uint row, uint col) const;
    void visitTile(uint row, uint col);
    bool checkVisited(uint row, uint col) const;
    uint getNumRows() const;
    uint getNumCols() const;
private:
    std::vector<std::vector<bool>> tileMap;
    std::vector<std::vector<bool>> visitMap;
};

#endif