#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Board {
    int size;
    int squares[4][4];
    int gameOver;
    int blankRow;
    int blankCol;
    int totalNumbers;
};

// declarations
void scrambleNumbers(struct Board* board);
void printBoard(struct Board* board);
void printTitle();
void printDivider(char separator, int size);
void getInput(int input[2], struct Board* board);
int isUppercase(char c);
void printInputError();
void processBoard(struct Board* board, int row, int col);
int checkValidTile(int row, int column, int size);
void checkWin(struct Board* board);

int main() {
    int input[2];

    struct Board* board = (struct Board *) malloc(sizeof(struct Board));
    board->size=4;

    scrambleNumbers(board);

    while(!board->gameOver) {
        printBoard(board);
        getInput(input, board);
        processBoard(board, input[0], input[1]);
    }
}

int checkValidTile(int row, int column, int size) {
    return ((row >= 0 && row < size) && (column >= 0 && column < size));
}

void scrambleNumbers(struct Board* board) {
    srand(time(0));

    board->totalNumbers = board->size * board->size - 1;

    for(int i=1; i<=board->totalNumbers;) {
        int row = rand() % board->size;
        int column = rand() % board->size;
        if(board->squares[row][column] == 0) {
            board->squares[row][column] = i;
            i++;
        }
    }

    for(int i=0; i<board->size; i++) {
        for(int j=0; j<board->size; j++) {
            if(board->squares[i][j] == 0) {
                board->blankRow = i;
                board->blankCol = j;
            }
        }
    }
}

void printTitle() {
    system("clear");
    printf("P U Z Z L E   O F   1 5   << Have Fun :) >>\n\n");
}

void printDivider(char separator, int size) {
    for(int i=0; i<size; i++) {
        printf("%c____", separator);
    }
    printf("%c\n", separator);
}

void printBoard(struct Board* board) {
    printTitle();
    printDivider(' ', board->size);
    for(int i=0; i<board->size; i++) {
        for(int j=0; j<board->size; j++) {
            if(board->squares[i][j]==0) {
                printf("|    ");
            } else if(board->squares[i][j]<10) {
                printf("|  %d ", board->squares[i][j]);
            } else {
                printf("| %d ", board->squares[i][j]);
            }
        }
        printf("|\n");
        printDivider('|', board->size);
    }
    printf("\n\n");
}

int isUppercase(char c) {
    return (c >= 65 && c <= 90); 
}

void getInput(int input[2], struct Board *board) {
    char inputChar;

    int neighbors[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

    printf(">>> Input instructions :\n\n");
    printf("\t1. Use J, I, K, L\n\n");
    printf("\t2. J: Swap blank with left square\tI: Swap blank with top square\n\n");
    printf("\t   K: Swap blank with down square\tL: Swap blank with right square\n\n\n");

    while(1) {
        printf(">>> Enter one of the above keys: ");
        
        inputChar = getc(stdin);
        getc(stdin);

        if( (inputChar>='i' && inputChar<='l') || (inputChar>='I' && inputChar<='L')) {
            int neighborIndex = isUppercase(inputChar) ? inputChar - 'I' : inputChar - 'i';

            input[0] = board->blankRow + neighbors[neighborIndex][0];
            input[1] = board->blankCol + neighbors[neighborIndex][1];

            if(checkValidTile(input[0], input[1], board->size)) {
                break;
            } else {
                printf("    No square to swap there\n\n");
            }
        } else {    
            printf("    Invalid input, Try again.\n\n");
        }
    }
}

void checkWin(struct Board* board) {
    board->gameOver = 1;

    for(int i=1; i<=board->totalNumbers; i++) {
        int row = (i-1) / board->size;
        int col = (i-1) % board->size;

        if(board->squares[row][col] != i) {
            board->gameOver = 0;
        }
    }

    if(board->gameOver) {
        printBoard(board);
        printf("Hurray!!! All the sqaures are in place, Great play...\n\n");
    }
}

void processBoard(struct Board* board, int row, int col) {
    int temp = board->squares[row][col];
    board->squares[row][col] = board->squares[board->blankRow][board->blankCol];
    board->squares[board->blankRow][board->blankCol] = temp;
    board->blankRow = row;
    board->blankCol = col;
    checkWin(board);
}

