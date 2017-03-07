#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"

class Player {

public:
    Player(Side side);
    ~Player();
    Side mside;
    Side other;
    Board *board;
    int weight[8][8];

    Move *doMove(Move *opponentsMove, int msLeft);
    int find_score(Board * board, int x, int y);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
