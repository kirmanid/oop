#ifndef CFAGENT_H
#define CFAGENT_H

#include"connectFour.h"
#include<vector>

class moveOption{
public:
    moveOption(ConnectFour& game);
    ConnectFour cf;
    int columnMove;
    double moveUtility;
    unsigned int draws;
    unsigned int wins;
    unsigned int losses;
};

class CFAgent{
private:
    std::vector<moveOption> options;
    const double lossUtility;
    const double winUtility;
    const double drawUtility;
    void simGame(moveOption& move);
    const Token agentPlayer;
    const Token enemy;
    Token whoCanWin(ConnectFour& game, Token turn);
public:
    CFAgent(Token player, Token enemy);
    int bestMove(ConnectFour& game, int simsPerOption);
};

#endif