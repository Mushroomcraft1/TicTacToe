#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

char getPlayerChar(int val)
{
    switch (val)
    {
    case 1:
        return 'X';
    case 2:
        return 'O';
    default:
        return ' ';
    }
}

void printBoard(int board[9])
{
    char string[] = "   |   |   \n-----------\n   |   |   \n-----------\n   |   |   \n\n";
    string[1] = getPlayerChar(board[0]);
    string[5] = getPlayerChar(board[1]);
    string[9] = getPlayerChar(board[2]);
    string[25] = getPlayerChar(board[3]);
    string[29] = getPlayerChar(board[4]);
    string[33] = getPlayerChar(board[5]);
    string[49] = getPlayerChar(board[6]);
    string[53] = getPlayerChar(board[7]);
    string[57] = getPlayerChar(board[8]);
    printf("%s", string);
}

int checkWin(int board[9], int player)
{
    int opponent = !(player - 1) + 1;
    if ((player == board[0] && player == board[1] && player == board[2]) ||
        (player == board[3] && player == board[4] && player == board[5]) ||
        (player == board[6] && player == board[7] && player == board[8]) ||
        (player == board[0] && player == board[3] && player == board[6]) ||
        (player == board[1] && player == board[4] && player == board[7]) ||
        (player == board[2] && player == board[5] && player == board[8]) ||
        (player == board[0] && player == board[4] && player == board[8]) ||
        (player == board[2] && player == board[4] && player == board[6]))
    {
        return 1;
    }
    else if ((opponent == board[0] && opponent == board[1] && opponent == board[2]) ||
             (opponent == board[3] && opponent == board[4] && opponent == board[5]) ||
             (opponent == board[6] && opponent == board[7] && opponent == board[8]) ||
             (opponent == board[0] && opponent == board[3] && opponent == board[6]) ||
             (opponent == board[1] && opponent == board[4] && opponent == board[7]) ||
             (opponent == board[2] && opponent == board[5] && opponent == board[8]) ||
             (opponent == board[0] && opponent == board[4] && opponent == board[8]) ||
             (opponent == board[2] && opponent == board[4] && opponent == board[6]))
    {
        return -1;
    }
    return 0;
}

void getMoves(bool moves[10], int board[9])
{
    moves[9] = false;
    for (int i = 0; i < 9; i++)
    {
        if (0 == board[i])
        {
            moves[i] = true;
            moves[9] = true;
        }
        else
        {
            moves[i] = false;
        }
    }
}

int negaMax(int board[9], int alpha, int beta, int player)
{
    int win = checkWin(board, player);
    if (0 != win)
    {
        return win;
    }
    bool moves[10];
    getMoves(moves, board);
    if (false == moves[9])
    {
        return 0;
    }
    for (int i = 0; i < 9; i++)
    {
        if (moves[i])
        {
            board[i] = player;
            int score = -negaMax(board, -beta, -alpha, !(player - 1) + 1);
            board[i] = 0;
            if (score >= beta)
            {
                return score;
            }
            if (score > alpha)
            {
                alpha = score;
            }
        }
    }
    return alpha;
}

int getBestMove(int board[9], int player)
{
    bool moves[10];
    getMoves(moves, board);
    int bestMove, bestScore = -INT_MAX, alpha = -INT_MAX, beta = INT_MAX;
    for (int i = 0; i < 9; i++)
    {
        if (moves[i])
        {
            board[i] = player;
            int score = -negaMax(board, alpha, beta, !(player - 1) + 1);
            board[i] = 0;
            if (bestScore < score)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

int main()
{
    int r = time(NULL) & 1;
    int board[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool moves[10];
    int player = r + 1, computer = !r + 1;
    int turn = 1;
    int move = 0;
    int win = 0;
    bool ended = false;
    printf("TicTacToe\n\nType the number corresponding to the relevant square on the grid to make your move.\n\n 1 | 2 | 3 \n-----------\n 4 | 5 | 6 \n-----------\n 7 | 8 | 9 \n\nYou are playing as %c\n\n", getPlayerChar(player));
    fflush(stdout);
    while (ended == false)
    {
        printBoard(board);
        if (turn == player)
        {
            bool valid = false;
            int value = -1;
            while (!valid)
            {
                printf("It is your turn: ");
                fflush(stdout);
                char input = getchar();
                while (input != '\n' && input != EOF)
                {
                    if ('9' >= input && '1' <= input)
                    {
                        value = input - '1';
                    }
                    input = getchar();
                }
                if (value == -1)
                {
                    printf("Invalid input, must be a number between 1 and 9.\n");
                }
                else if (0 == board[value])
                {
                    valid = true;
                    board[value] = player;
                }
                else
                {
                    printf("This square has already been taken.\n");
                }
            }
        }
        else
        {
            printf("It is the computer's turn:\n\n");
            move = getBestMove(board, computer);
            board[move] = computer;
        }
        turn = (turn & 1) + 1;
        win = checkWin(board, player);
        getMoves(moves, board);
        if (0 != win)
        {
            if (1 == win)
            {
                printf("You win!\n\n");
            }
            else
            {
                printf("Computer wins!\n\n");
            }
            ended = true;
        }
        else if (false == moves[9])
        {
            printf("It's a draw!\n\n");
            ended = true;
        }
        fflush(stdout);
    }
    printBoard(board);
    printf("Press Enter to exit...");
    fflush(stdout);
    getchar();
    return 0;
}