#ifndef MAZE_H
#define MAZE_H

#include<vector>

class Maze{
public:
    Maze(uint rows, uint cols, bool defaultTile);
    void createWall(uint row1, uint col1, uint row2, uint col2);
    bool wallExists(uint row1, uint col1, uint row2, uint col2) const;

    void setTile(bool tile, uint row, uint col);
    bool getTile(uint row, uint col) const;
    void visitTile(uint row, uint col);
    bool checkVisited(uint row, uint col) const;
    uint getNumRows() const;
    uint getNumCols() const;
private:
    std::vector<std::vector<bool>> tileMap;
    std::vector<std::vector<bool>> visitMap;
    bool checkValidWall(uint row1, uint col1, uint row2, uint col2) const;
};

#endif