#include"maze.h"

using namespace std;

Maze::Maze(uint rows, uint cols, bool defaultTile):
    tileMap(rows,vector<bool>(cols, defaultTile)),
    visitMap(rows, vector<bool>(cols, false)),
    oldTiles(rows, vector<bool>(cols, false)),
    solverCol{0}, solverRow{0}{
}

void Maze::setTile(bool tile, uint row, uint col){
    tileMap[row][col] = tile;
}

bool Maze::getTile(uint row, uint col) const{
    return tileMap[row][col];
}

void Maze::visitTile(uint row, uint col){
    visitMap[row][col] = true;
}

bool Maze::checkVisited(uint row, uint col) const{
    return visitMap[row][col];
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

    int colDiff = abs(int(col1)-int(col2));
    int rowDiff = abs(int(row1)-int(row2));
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
        return false;
    }
    return tileMap[(row1+row2)/2] [(col1+col2)/2];
}

// Generate maze via cellular automaton with rule B2/S123 from randomized inital state
void Maze::generateMaze(int seed, uint iterations){
    srand (seed);
    for (uint colIndex = 0; colIndex < getNumCols(); colIndex++){
        for (uint rowIndex = 0; rowIndex < getNumRows(); rowIndex++){
            tileMap[rowIndex][colIndex] = bool(rand()%2);
        }
    }
    uint neighbors;
    for (uint i = 0; i <= iterations; i++){
        oldTiles = tileMap;
        for (uint rowIndex = 0; rowIndex < getNumRows(); rowIndex++){
            for (uint colIndex = 0; colIndex < getNumCols(); colIndex++){
                neighbors = 0;
                for (int deltaRow = -1; deltaRow <= 1; deltaRow++){
                    for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
                        if (deltaRow == 0 && deltaCol == 0){
                            continue;
                        }
                        if (rowIndex + deltaRow >= getNumRows() || rowIndex + deltaRow < 0){
                            continue;
                        }
                        if (colIndex + deltaCol >= getNumCols() || colIndex + deltaCol < 0){
                            continue;
                        }
                        if (oldTiles[rowIndex+deltaRow][colIndex+deltaCol]){
                            neighbors++;
                        }
                    }
                }
                if (neighbors > 3 || neighbors < 1){
                    tileMap[rowIndex][colIndex] = false;
                } 
                if (neighbors == 2){
                    tileMap[rowIndex][colIndex] = true;
                }
            }
        }

    }
}

void Maze::displayMaze() const{
    for (uint colIndex = 0; colIndex < getNumCols(); colIndex++){
        for (uint rowIndex = 0; rowIndex < getNumRows(); rowIndex++){
            if (rowIndex == solverRow && colIndex == solverCol){
                cout << '@';
                continue;
            }
            if (tileMap[rowIndex][colIndex]){
                cout << '%';
            } else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
}

void Maze::makeUserMove(){
    char keypress;
    keypress = getchar();
    switch (keypress){
    case 'a':
        if (tileMap[solverRow-1][solverCol] && !tileMap[solverRow][solverCol]){
            break;
        }
        solverRow--;
        break;
    case 'd':
        if (tileMap[solverRow+1][solverCol] && !tileMap[solverRow][solverCol]){
            break;
        }
        solverRow++;
        break;
    case 'w':
        if (tileMap[solverRow][solverCol-1] && !tileMap[solverRow][solverCol]){
            break;
        }
        solverCol--;
        break;
    case 's':
        if (tileMap[solverRow][solverCol+1] && !tileMap[solverRow][solverCol]){
            break;
        }
        solverCol++;
        break;
    default:
        break;
    }
}