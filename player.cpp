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


int Player::find_score(Board * board, int x, int y)
{
    int mcount;
    int ocount;

    if (mside == BLACK)
    {
        mcount = board->countBlack();
        ocount = board->countWhite();
    }

    else if (mside == WHITE)
    {
        mcount = board->countWhite();
        ocount = board->countBlack();
    }

    return mcount - ocount;
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

    int score_board[8][8];

    int check[8][8];

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            score_board[i][j] = 0;
            check[i][j] = 0;
        }
    }

    if (board->hasMoves(mside) == false)
    {
        return nullptr;
    }
    
    
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Move *move = new Move(i, j);
            if (board->checkMove(move, mside) == true)
            {
                Board * board_copy = board->copy();
                board_copy->doMove(move, mside);
                score_board[i][j] = find_score(board_copy, i, j);
                check[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (j == 0)
            {
            std::cerr<<std::endl;
            }
            std::cerr<<score_board[i][j];
        }
    }

    std::cerr<<std::endl;
    
    int max = -999999999;
    Move *move_todo = new Move(0, 0);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (score_board[i][j] > max && check[i][j] == 1)
            {
                move_todo->setX(i);
                move_todo->setY(j);
            }
        }
    }



    board->doMove(move_todo, mside);
    return move_todo;
}

