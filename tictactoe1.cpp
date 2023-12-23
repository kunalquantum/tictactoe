#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

char board[3][3];
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void computerMoveEasy();
void computerMoveMedium();
void computerMoveHard();
void resetBoard();
void printBoard();
int checkFreeSpace();
void playerMove(char);
void computerMove(char, int);
char checkWinner();
void printWinner(char);
void playTicTacToe();

int main() {
    srand(time(0));
    
    printf("Welcome to Tic-Tac-Toe!\n");

    do {
        resetBoard();
        playTicTacToe();

        char playAgain;
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

        if (tolower(playAgain) != 'y') {
            break;
        }
    } while (1);

    printf("Thanks for playing! Goodbye!\n");
    return 0;
}

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n-------------\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n-------------\n");
    }
}

int checkFreeSpace() {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != PLAYER_X && board[i][j] != PLAYER_O) {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER_X) {
        printf("Player X wins!\n");
    } else if (winner == PLAYER_O) {
        printf("Player O wins!\n");
    } else {
        printf("It's a draw! Good game.\n");
    }
}

void playerMove(char currentPlayer) {
    int row, col;

    printf("%s's turn. Enter the row (1-3): ", (currentPlayer == PLAYER_X) ? "Player X" : "Player O");
    scanf("%d", &row);

    printf("%s's turn. Enter the column (1-3): ", (currentPlayer == PLAYER_X) ? "Player X" : "Player O");
    scanf("%d", &col);

    row--;
    col--;

    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        printf("Invalid move. Try again.\n");
        playerMove(currentPlayer);
    } else {
        board[row][col] = currentPlayer;
    }
}

void computerMove(char currentPlayer, int difficulty) {
    printf("%s's turn (Computer)\n", (currentPlayer == PLAYER_X) ? "Player X" : "Player O");

    switch (difficulty) {
        case 1: // Easy
            computerMoveEasy();
            break;
        case 2: // Medium
            computerMoveMedium();
            break;
        case 3: // Hard
            computerMoveHard();
            break;
        default:
            printf("Invalid difficulty level. Using easy level.\n");
            computerMoveEasy();
    }
}

void computerMoveEasy() {
    int x, y;
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');

    printf("Computer chose position %c.\n", board[x][y]);
    board[x][y] = PLAYER_O;
}

void computerMoveMedium() {
    // Check for a winning move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER_O;
                if (checkWinner() == PLAYER_O) {
                    printf("Computer chose position %c.\n", board[i][j]);
                    return;
                } else {
                    board[i][j] = ' '; // Undo the move
                }
            }
        }
    }

    // Check for a blocking move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER_X;
                if (checkWinner() == PLAYER_X) {
                    board[i][j] = PLAYER_O;
                    printf("Computer chose position %c.\n", board[i][j]);
                    return;
                } else {
                    board[i][j] = ' '; // Undo the move
                }
            }
        }
    }

    // If no winning or blocking move, choose randomly
    computerMoveEasy();
}

void computerMoveHard() {
    // Implementing a more advanced strategy for hard level
    // Prioritize: Win, Block, Fork, Block Fork, Center, Opposite Corner, Empty Corner, Empty Side
    if (board[1][1] == ' ') {
        board[1][1] = PLAYER_O; // Choose the center if available
    } else if (board[0][0] == PLAYER_X && board[2][2] == ' ' || board[0][2] == PLAYER_X && board[2][0] == ' ') {
        int cornerX, cornerY;
        do {
            cornerX = rand() % 2 * 2;
            cornerY = rand() % 2 * 2;
        } while (board[cornerX][cornerY] != ' ');
        board[cornerX][cornerY] = PLAYER_O; // Opposite corner
    } else {
        int priorityMoves[8][2] = {
            {0, 0}, {0, 2}, {2, 0}, {2, 2}, // Corners
            {0, 1}, {1, 0}, {1, 2}, {2, 1}  // Sides
        };

        for (int i = 0; i < 8; i++) {
            int moveX = priorityMoves[i][0];
            int moveY = priorityMoves[i][1];

            if (board[moveX][moveY] == ' ') {
                board[moveX][moveY] = PLAYER_O;
                if (checkWinner() == PLAYER_O) {
                    printf("Computer chose position %c.\n", board[moveX][moveY]);
                    return;
                } else {
                    board[moveX][moveY] = ' '; // Undo the move
                }
            }
        }
    }

    // If no winning move, block opponent's winning move
    computerMoveMedium();
}

void playTicTacToe() {
    char currentPlayer = PLAYER_X;
    int playerXStreak = 0;
    int playerOStreak = 0;
    int difficulty;

    printf("Enter the difficulty level (1: Easy, 2: Medium, 3: Hard): ");
    scanf("%d", &difficulty);

    do {
        printBoard();

        if (currentPlayer == PLAYER_X) {
            playerMove(currentPlayer);
        } else {
            computerMove(currentPlayer, difficulty);
        }

        char winner = checkWinner();
        if (winner != ' ' || checkFreeSpace() == 0) {
            printBoard();
            printWinner(winner);

            if (winner == PLAYER_X) {
                playerXStreak++;
            } else if (winner == PLAYER_O) {
                playerOStreak++;
            }

            printf("Player {You} Win Streak: %d\n", playerXStreak);
            printf("Player computer Win Streak: %d\n", playerOStreak);

            break;
        }

        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
    } while (1);
}

