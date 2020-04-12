#include "connectFour.h"

 using namespace std;

 ConnectFour::ConnectFour(int rows, int cols): 
    board(cols,vector<Token>(rows, Token::none)),
    numConnect{4}{
    srand(time(NULL));
 }

 ConnectFour::ConnectFour(ConnectFour& cf){
    board = cf.board;
    numConnect = cf.numConnect;
    srand(time(NULL));
 }

int ConnectFour::numRows()const{
    return board[0].size();
}

int ConnectFour::numCols()const{
    return board.size();
}

void ConnectFour::clearBoard(){
    vector<Token> col(numCols(),Token::none);
    board = vector<vector<Token>>(numRows(), col);
}

vector<vector<Token>> ConnectFour::getBoard()const{
    return board;
}

bool ConnectFour::canAddToken(int columnIndex)const{
    /// check if columnindex is valid
    int topRowIndex = numRows() - 1;
    // if the topmost space of the given column is empty (has token 'none'), then you can add a token
    return (board[columnIndex][topRowIndex] == Token::none);
}

void ConnectFour::addToken(int columnIndex, Token token){
    if (!canAddToken(columnIndex)){return;}
    for (int rowIndex = 0; rowIndex < numRows(); rowIndex++){
        if (board[columnIndex][rowIndex] == Token::none){
            board[columnIndex][rowIndex] = token;
            break;
        }
    }
}

Token ConnectFour::whoWon()const{
    Token winner = Token::none;
    // check cols
    for (int colIndex = 0; colIndex < numCols(); colIndex++){
        if (board[colIndex][0] == Token::none){
            continue;
        }
        winner = checkSequence(0,colIndex, 0, 1, numRows());
        if (winner != Token::none){
            return winner;
        }
    }
    // check rows
    for (int rowIndex = 0; rowIndex < numRows(); rowIndex++){
        winner = checkSequence(rowIndex, 0, 1, 0, numCols());
        if (winner != Token::none){
            return winner;
        }
    }
    // check diagonal, up and to the right
    for (int colIndex = 0; colIndex < numCols() - numConnect + 1; colIndex++){
        winner = checkSequence(0, colIndex, 1, 1, min(numRows(), numCols() - colIndex));
        if (winner != Token::none){
            return winner;
        }
    }
    // check diagonal, up and to the left
    for (int colIndex = numConnect - 1; colIndex < numCols(); colIndex++){
        winner = checkSequence(0, colIndex, -1, 1, min(numRows(), colIndex + 1));
        if (winner != Token::none){
            return winner;
        }
    }
    return winner;
}

Token ConnectFour::checkSequence(int rowStart, int colStart, int deltaCol, int deltaRow, int seqLength)const{
    int row = rowStart;
    int col = colStart;
    int consecutive = 1;
    Token prevToken = Token::none;
    for (int i=0; i<seqLength; i++){
        if (prevToken == board[col][row] && prevToken != Token::none){
            consecutive++;
            if (consecutive == numConnect){
                return prevToken;
            }
        } else {
            if (seqLength - i < numConnect){
                return Token::none;
            }
            consecutive = 1;
        }
        prevToken = board[col][row]; 
        col += deltaCol;
        row += deltaRow;
    }
    return Token::none;
}

void ConnectFour::randMove(Token token){
    vector<int> possMoves = getPossMoves();
    if (possMoves.size() == 0){
        return;
    }
    addToken(possMoves[rand()%possMoves.size()], token);
}

vector<int> ConnectFour::getPossMoves(){
    vector<int> possMoves;
    for (int i=0; i < numCols(); i++){
        if(canAddToken(i)){
        possMoves.push_back(i);
        }
    }
    return possMoves;
}