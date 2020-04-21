#include"cfAgent.h"

using namespace std;

moveOption::moveOption(ConnectFour& game):
    cf{game},
    draws{0},
    wins{0},
    losses{0}
    {}

CFAgent::CFAgent(Token player, Token enemy):
    winUtility{1},
    drawUtility{0},
    lossUtility{-5},
    agentPlayer{player},
    enemy{enemy}
    {}

Token CFAgent::whoCanWin(ConnectFour& game, Token turn){
    vector<int> possMoves = game.getPossMoves();
    for (int move : possMoves){
        ConnectFour cf{game};
        cf.addToken(move, turn);
        Token winner = cf.whoWon();
        if (winner != Token::none){
            return winner;
        }
    }
    return Token::none;
}

void CFAgent::simGame(moveOption& move){
    move.cf.addToken(move.columnMove, agentPlayer);
    Token turn = enemy;
    while (whoCanWin(move.cf, turn)==Token::none){
        if (move.cf.getPossMoves().size()==0){
            break;
        }
        move.cf.randMove(turn);
        turn = (turn == enemy)? agentPlayer : enemy;
    }
    // at this point, the winner is the current turn-holder
    if (turn == Token::none){
        move.draws++;
    } else if (turn == agentPlayer){
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
    int bestMove = 0;
    double topUtility = simsPerOption*lossUtility - 1;
    for (int move : possMoves){
        moveOption option{game};
        option.columnMove = move;
        for (int i=0; i < simsPerOption; i++){
            simGame(option);
        }
        option.moveUtility = winUtility * option.wins + lossUtility * option.losses + drawUtility * option.draws;
        if (option.moveUtility > topUtility){
            topUtility = option.moveUtility;
            bestMove = option.columnMove;
        }
    }
    return bestMove;
}