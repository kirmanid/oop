#include<iostream>
#include"connectFour.h"
#include"cfAgent.h"
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

void displayBoard(ConnectFour& cf){
    for (int r=cf.numRows()-1; r >= 0; r--){
        for (int c=0; c < cf.numCols(); c++){
            switch(cf.getBoard()[c][r]){
                case Token::none : cout << "_|"; break;
                case Token::player1 : cout << "O|"; break;
                case Token::player2 : cout << "@|"; break;
            }
        }
        cout << endl;
    }
    cout << endl;
}


int main(){
    Canvas canv {768, 1024, Scalar{0,0,0}, "Connect Four"}
    ConnectFour cf{6,7,4};
    CFAgent agent1{Token::player1, Token::player2};
    CFAgent agent2{Token::player2, Token::player1};

    int a1best, a2best;
    while(cf.whoWon() == Token::none && cf.getPossMoves().size() > 0){
        a1best = agent1.bestMove(cf, 100000);
        cf.addToken(a1best, Token::player1);
        displayBoard(cf);
        cout << "0 1 2 3 4 5 6" << endl;
        cout << "Player 1 placed a token in column " << a1best << endl;

        // one of the two following lines should be commented out:
        // a2best = agent2.bestMove(cf, 500);
        cin >> a2best;
        cf.addToken(a2best, Token::player2);
        displayBoard(cf);
        cout << "Player 2 placed a token in column " << a2best << endl;

        canv.drawAndWipe();
        pan.checkPressed();
        
        pan.draw(canv.mat);
    }
    cout << endl;
    switch (cf.whoWon()){
        case Token::none:
            cout << "DRAW!";
            break;
        case Token::player1:
            cout << "PLAYER 1 WINS!";
            break;
        case Token::player2:
            cout << "PLAYER 2 WINS!";
            break;
    }
    cout << endl;
}