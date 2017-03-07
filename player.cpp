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

    //Weight table initialization prioritizing corners
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i==0 && j==0) or (i==0 && j==7) or (i==7 && j==0) or (i==7 && j==7))
            {
                weight[i][j] = 100;
            }

            else if ((i==1 && j ==1) or (i==1 && j==6) or (i==6 && j==1) or (i==6 && j==6))
            {
                weight[i][j] = -30;
            }

            else if ((i==0 && 1<j && j<6) or (i==7 && 1<j && j<6) or (j==0 && 1<i && i<6) or (j==7 && 1<i && i<6))
            {
                weight[i][j] = 35;
            }
            else
            {
                weight[i][j] = 1;
            }
        }
    }

    weight[0][1] = -15;
    weight[1][0] = -15;
    weight[6][0] = -15;
    weight[7][1] = -15;
    weight[0][6] = -15;
    weight[1][7] = -15;
    weight[6][7] = -15;
    weight[7][6] = -15;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}


int Player::find_score(Board * board, int x, int y)
{
    //Score-based heuristic based on weights and total score of player
    int score;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board->get(mside, i, j))
            {
                score += weight[j][i];
            }

            if (board->get(other, i, j))
            {
                score -= weight[j][i];
            }
        }
    }

    //Alternate Heuristic left for possible future testing
    /*
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

    return (mcount - ocount) + weight[y][x];*/

    return score;
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
	

    board->doMove(opponentsMove, other);

    //Initialization of score board and check board
    //Score_board keeps track of score values if a move is played
    int score_board[8][8];

    //Check board keeps track of if there is a possible move in the position
    int check[8][8];

    //Initialization of previously mentioned boards to 0
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            score_board[i][j] = 0;
            check[i][j] = 0;
        }
    }

    //If the player has no moves left or if time has ran out return nullptr
    if (board->hasMoves(mside) == false or msLeft == 0)
    {
        return nullptr;
    }
        
    //Testing of moves onto copies of the board and alloting values for the
    //player onto the scoreboard
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

    //For future testing
    /*
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

    std::cerr<<std::endl;*/
    
    int max = -999999999;
    Move *move_todo = new Move(0, 0);

    //Testing for maximum point value moves
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (score_board[i][j] > max && check[i][j] == 1)
            {
                move_todo->setX(i);
                move_todo->setY(j);
                max = score_board[i][j];
            }
        }
    }



    board->doMove(move_todo, mside);
    return move_todo;
}

