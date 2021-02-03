#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Tile {
    int nearByBombs;
    int isBomb;
    int opened;
};

struct Board {
    int size;
    struct Tile tile[20][20];
    int noOfBombs;
    int totalOpened;
    int gameOver;
};

// declarations
int getBoardSize();
void plantBombs(struct Board* board);
void printBoard(struct Board* board);
void printTitle();
void printDivider(char separator, int size);
void printColumnName(int size);
void getInput(int input[2], int size);
int isNumber(char c);
int isUppercase(char c);
int isLowecase(char c);
void printInputError();
void openTile(struct Board* board, int row, int col);
void checkTile(struct Board* board, int row, int col);
int getNearbyBombs(struct Board* board, int row, int col);
int checkValidTile(int row, int column, int size);
void checkNeigbours(struct Board* board, int row, int col);
void checkWin(struct Board* board);
void printLose(struct Board* board, int row, int col);

int main() {
    int input[3];
    struct Board* board = (struct Board*) malloc(sizeof( struct Board));

    board->size = getBoardSize();
    plantBombs(board);

    while(!board->gameOver) {
        printBoard(board);
        getInput(input, board->size);
        openTile(board, input[0], input[1]);
    }
}

int checkValidTile(int row, int column, int size) {
    return ((row >= 0 && row < size) && (column >= 0 && column < size));
}

void plantBombs(struct Board* board) {
    srand(time(0));

    board->noOfBombs = 2*board->size;
    for(int i=0; i<board->noOfBombs;) {
        int row = rand() % board->size;
        int column = rand() % board->size;
        if(!board->tile[row][column].isBomb) {
            board->tile[row][column].isBomb = 1;
            i++;
        }
    }
}

void printTitle() {
    system("clear");
    printf("M I N E   S W E E P E R   << Have Fun :) >>\n\n");
}

void printDivider(char separator, int size) {
    printf("   ");
    for(int i=0; i<size; i++) {
        printf("%c___", separator);
    }
    printf("%c\n", separator);
}

void printColumnName(int size) {
    printf("   ");
    for(int i=1; i<=size; i++) {
        if(i<10) {
            printf("  %d ", i);
        } else {
            printf(" %d ", i);
        }
    }
    printf(" \n");
}

void printBoard(struct Board* board) {
    printTitle();

    printColumnName(board->size);
    printDivider(' ', board->size);
    for(int i=0; i<board->size; i++) {
        printf(" %c ", i+65);
        for(int j=0; j<board->size; j++) {
            char toPrint;
            if(board->tile[i][j].opened) {
                int value = board->tile[i][j].nearByBombs;
                if(value == -1) {
                    toPrint = '@';
                } else {
                    toPrint = value+48;
                }
            } else {
                toPrint = ' ';
            }

            printf("| %c ", toPrint);
        }
        printf("|\n");
        printDivider('|', board->size);
    }
    printf("\n");
}

void printInputError() {
    printf("Invalid input, Try again.\n\n");
}

int getBoardSize() {
    int size;
    char extra[10];

    printTitle();

    while(1) {
        printf("Enter Board Size (8 - 20): ");
        scanf("%d", &size);
        fgets(extra, 10, stdin);

        if(size>7 && size<21) {
            return  size;
        } else {
            printInputError();
        }
    }
}

int isNumber(char c) {
    return (c >= 48 && c <= 90); 
}

int isUppercase(char c) {
    return (c >= 65 && c <= 90); 
}

int isLowercase(char c) {
    return (c >= 97 && c <= 122); 
}

void getInput(int input[2], int size) {
    char inputStr[10];

    while(1) {
        printf("Enter the tile no ( eg. A1, C4 ) : ");
        scanf("%s", inputStr);

        if(isNumber(inputStr[1]) && isUppercase(inputStr[0]) || isLowercase(inputStr[0])) {
            input[0] = isUppercase(inputStr[0]) ? inputStr[0] - 65 : inputStr[0]-97; 
            input[1] = (inputStr[1]-48) - 1;

            if(size > 9 &&  isNumber(inputStr[2])) {
                input[1] = (inputStr[1]-48) * 10 + (inputStr[2]-48) - 1;
            }

            if(checkValidTile(input[0], input[1], size)) {
                break;
            } else {
                printInputError();
            }
        } else {    
            printInputError();
        }
    }
}

void printLose(struct Board* board, int row, int col) {
    printBoard(board);
    printf("Oops!!! Bomb in %c%d , You lose :(\n\n", row+65, col+1);
    board->gameOver = 1;
}

void checkWin(struct Board* board) {
    if(board->size * board->size - board->noOfBombs == board->totalOpened) {
        printBoard(board);
        printf("Hurray!!! All tiles without bomb are open, You win...\n\n");
        board->gameOver=1;
    }
}

int getNearbyBombs(struct Board* board, int row, int col) {
    int neighbors[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    int bombs = 0;

    for(int i=0; i<8; i++) {
        int r = row + neighbors[i][0];
        int c = col + neighbors[i][1];

        if(checkValidTile(r, c, board->size) && board->tile[r][c].isBomb) {
            bombs++;
        }
    }

    return bombs;
}

void checkNeigbours(struct Board* board, int row, int col) {
    int neighbors[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

    for(int i=0; i<8; i++) {
        int r = row + neighbors[i][0];
        int c = col + neighbors[i][1];

        if(checkValidTile(r, c, board->size) && !board->tile[r][c].opened) {
            checkTile(board, r, c);
        }
    }
}

void checkTile(struct Board* board, int row, int col) {
    if(!board->tile[row][col].opened) {
        board->tile[row][col].opened = 1;
        board->totalOpened++;

        board->tile[row][col].nearByBombs = getNearbyBombs(board, row, col);

        if(board->tile[row][col].nearByBombs == 0) {
            checkNeigbours(board, row, col);
        }
    }
}

void openTile(struct Board* board, int row, int col) {
    if(board->tile[row][col].isBomb) {
        board->tile[row][col].nearByBombs = -1;
        board->tile[row][col].opened = 1;
        board->totalOpened++;
        printLose(board, row, col);
    } else {
        checkTile(board, row, col);
        checkWin(board);
    }
}

