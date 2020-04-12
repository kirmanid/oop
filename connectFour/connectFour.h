#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <vector>
#include <random>
#include <time.h> 

enum class Token {
    none,
    player1,
    player2
};

class ConnectFour{
private:
    std::vector<std::vector<Token>> board; // column-major, [0][0] is bottom left corner of board
    int numConnect;
    Token checkSequence(int rowStart, int colStart, int deltaCol, int deltaRow, int seqLength) const;
public:
    int numCols() const;
    int numRows() const;
    ConnectFour(int rows, int cols);
    ConnectFour(ConnectFour& cf);
    void clearBoard();
    std::vector<std::vector<Token>> getBoard() const;
    bool canAddToken(int columnIndex) const;
    void addToken(int columnIndex, Token token);
    void randMove(Token token); 
    std::vector<int> getPossMoves();
    Token whoWon() const;
};

#endif