#include<iostream>
#include"connectFour.h"

using namespace std;

void displayBoard(ConnectFour& cf){
    for (int r=cf.numRows()-1; r >= 0; r-- ){
        for (int c=0; c < cf.numCols(); c++){
            switch(cf.getBoard()[c][r]){
                case Token::none : cout << "_|"; break;
                case Token::player1 : cout << "O|"; break;
                case Token::player2 : cout << "@|"; break;
            }
        }
        cout << endl;
    }
}

int main(){
    ConnectFour cf{6,7};
    int n =4;
    for (int i=0; i<15; i++){
        cf.randMove(Token::player1);
        cf.randMove(Token::player2);
    }
    displayBoard(cf);
}