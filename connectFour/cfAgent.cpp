#include"cfAgent.h"

using namespace std;

CFAgent::CFAgent(Token player, Token enemy):
    winUtility{1},
    drawUtility{0},
    lossUtility{-1},
    agentPlayer{player},
    enemy{enemy}
    {}

void CFAgent::simGame(moveOption move){
    move.cf.addToken(move.columnMove, agentPlayer);
    Token turn = enemy;
    while (move.cf.whoWon()==Token::none){
        if (move.cf.getPossMoves().size()==0){
            break;
        }
        move.cf.randMove(turn);
        if (turn == enemy){
            turn = agentPlayer;
        } else {
            turn = enemy;
        }
    }
    Token winner = move.cf.whoWon();
    if (winner == Token::none){
        move.draws++;
    } else if ( winner == agentPlayer){
        move.wins++;
    } else {
        move.losses++;
    }
}

int CFAgent::bestMove(ConnectFour& game, int simsPerOption){
    vector<int> possMoves = game.getPossMoves();
    if (possMoves.size() == 0){
        return -1; //board is full
    }
    vector<moveOption> options;
    for (int move : possMoves){
        // moveOption option;
        // ConnectFour cf{game};
        // option.cf = cf;
        // option.columnMove = move;
        // // options.push_back(option);
    }
    return 0;
}