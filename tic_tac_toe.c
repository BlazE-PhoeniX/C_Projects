#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//keep track of board
char square[11] = "           ";

//keep track of player turns
bool isPlayer1Turn=true;

//update the board if valid number is passed else returns error codes
int updateBoard(int position) {

    //invalid number
    if(position<1 || position>9)
        return -1;

    //already occupied position
    else if(square[position] != ' ')
        return 0;

    //valid position
    else {
        square[position] = (isPlayer1Turn)? 'X': 'O';
        return 1;
    }
}

//clears the screen and draws the board for each turn
void drawBoard() {

    //To show help board only the first time
    static int count = 1;

    //clears the screen
    system("clear");

    printf("\n--------------------------------------------------\n\n");
    printf("\tTIC - TAC - TOE\n\n");
    printf("Player 1 ( X )   -   Player 2 ( O )\n\n\n");

    //help board , displayed only the first time
    if(count == 1) {
        printf("   |   |   \n");
        for(int i=1; i<=9; i++) {
            printf(" %d ", i);
            if(i==3 || i==6) {
                printf("\n___|___|___\n");
                printf("   |   |   \n");
            } else if(i!=9) {
                printf("|");
            }
        }
        printf("\n   |   |   \n\n\n");
    }

    //Game Board 
    printf("   |   |   \n");
    for(int i=1; i<=9; i++) {
        printf(" %c ", square[i]);
        if(i==3 || i==6) {
            printf("\n___|___|___\n");
            printf("   |   |   \n");
        } else if(i!=9) {
            printf("|");
        }
    }
    printf("\n   |   |   \n\n\n");

    //increment static variable
    count++;
}

//Check is game has ended (win or draw)
// 1  for win, 0 for draw, -1 for progress
int checkWin() {

    //first row
    if(square[1] != ' ' && square[1] == square[2] && square[2] == square[3])
        return 1;

    //second row
    else if(square[4] != ' ' && square[4] == square[5] && square[5] == square[6])
        return 1;

    //third row
    else if(square[7] != ' ' && square[7] == square[8] && square[8] == square[9])
        return 1;

    //first column
    else if(square[1] != ' ' && square[1] == square[4] && square[4] == square[7])
        return 1;

    //second column
    else if(square[2] != ' ' && square[2] == square[5] && square[5] == square[8])
        return 1;

    //third column
    else if(square[3] != ' ' && square[3] == square[6] && square[6] == square[9])
        return 1;

    //main diagonal
    else if(square[1] != ' ' && square[1] == square[5] && square[5] == square[9])
        return 1;

    //side diagonal
    else if(square[3] != ' ' && square[3] == square[5] && square[5] == square[7])
        return 1;

    //check whether draw or progress
    else {

        //check is any box is unfilled (progress)
        for(int i=1; i<=9; i++) {
            if(square[i] == ' ')
                return -1;
        }

        //All boxes are filled but no one wins (draw)
        return 0;
    }
        
}

int main() {

    //keep track of match result at each turn
    int result = -1;
    int position, turn, updateResult;

    //while match in progress, draws board and asks for user input.
    while(result == -1) {
        drawBoard();
        turn = (isPlayer1Turn)? 1: 2;

        //get back here in case of invalid input
        playerInput:
            printf("=> Player %d, enter a number between 1-9 : ", turn);
            scanf("%d", &position);
            updateResult = updateBoard(position);

            //display error msg based on code and get back to playerInput stage
            if(updateResult==-1) {
                printf("\n<= Error: Number must be between 1-9. Try again.\n\n");
                goto playerInput;
            } else if(updateResult==0) {
                printf("\n<= Error: Position already occupied. Try again.\n\n");
                goto playerInput;
            }

            //get the game result and switch turns if it is in progress
            result = checkWin();
            if (result == -1)
                isPlayer1Turn=!isPlayer1Turn;
    }

    //draw board again if game ended and display appropriate msg.
    drawBoard();
    if(result == 1) {
        int winner = (isPlayer1Turn)? 1: 2;
        printf("=> Player %d wins.\n\n", winner);
    } else {
        printf("=> Match Draw.\n\n");
    }

    return 0;
}