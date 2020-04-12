#ifndef CFAGENT_H
#define CFAGENT_H

#include"connectFour.h"
#include<vector>

struct moveOption{
    ConnectFour cf;
    int columnMove;
    unsigned int draws{0};
    unsigned int wins{0};
    unsigned int losses{0};
};

class CFAgent{
private:
    std::vector<moveOption> options;
    const double lossUtility;
    const double winUtility;
    const double drawUtility;
    void simGame(moveOption move);
    const Token agentPlayer;
    const Token enemy;
public:
    CFAgent(Token player, Token enemy);
    int bestMove(ConnectFour& game, int simsPerOption);
};

#endif