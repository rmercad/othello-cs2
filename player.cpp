#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    mside = side;
    other = (side == BLACK) ? WHITE : BLACK;

    //list pattern (j-1)*8+i-1



    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i==0 && j==0) or (i==0 && j==7) or (i==7 && j==0) or (i==7 && j==7))
            {
                weight[i][j] = 3;
            }

            else if ((i==1 && j ==1) or (i==1 && j==6) or (i==6 && j==1) or (i==6 && j==6))
            {
                weight[i][j] = -3;
            }

            else if ((i==0 && 1<j && j<6) or (i==7 && 1<j && j<6) or (j==0 && 1<i && i<6) or (j==7 && 1<i && i<6))
            {
                weight[i][j] = 2;
            }

            else
            {
                weight[i][j] = 1;
            }
        }
    }

    weight[0][1] = -1;
    weight[1][0] = -1;
    weight[6][0] = -1;
    weight[7][1] = -1;
    weight[0][6] = -1;
    weight[1][7] = -1;
    weight[6][7] = -1;
    weight[7][6] = -1;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
	
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board->doMove(opponentsMove, other);


    if (board->hasMoves(mside) == false)
    {
        return nullptr;
    }
    
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                Move *move = new Move(i, j);
                if (board->checkMove(move, mside) == true)
                {
                    board->doMove(move, mside);
                    return move;
                }
            }
        }
    }
}