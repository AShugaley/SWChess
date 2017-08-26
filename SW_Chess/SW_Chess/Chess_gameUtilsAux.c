//
//  Chess_gameUtilsAux.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//



#include "Chess_gameUtilsAux.h"
#include "Chess_gameUtils.h"
#include <stdbool.h>

//we assume that the arguments are legal - i.e. 0<=pos<=7 => need to check it elsewhere! - the comp will do so by himself, and we will check arguments from the user at input.

bool isValidPawnMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    int first_row = 0;
    int operator = 1;
    if (src->currentPlayer == BLACKS){
        first_row = 7;
        operator = -1;
    }
    printf("%d,%d,%d,%d,%d,%d",prev_pos_row,prev_pos_col,next_pos_row,next_pos_col,operator,operator);
    if (prev_pos_col != next_pos_col){
        if((next_pos_row == prev_pos_row+(1*operator))&&((prev_pos_col+1 == next_pos_col)||(prev_pos_col-1==next_pos_col)))
            return true;
        else
            return false;
    }
    if (prev_pos_row+(1*operator) == next_pos_row) // reg move
        return true;
    if ((prev_pos_row == first_row+(1*operator)) && (prev_pos_row+(2*operator) == next_pos_row) && (src->gameBoard[prev_pos_row+(1*operator)][prev_pos_col] == EMPTY_BOARD_POS)) // first move
        return true;
    return false;
}


bool isValidBishopMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    if((prev_pos_row+prev_pos_col) != (next_pos_row+next_pos_col)){ //LB to TR diag
        for (int i = 1; i<8; i++){
            if((prev_pos_row+i == next_pos_row) && (prev_pos_col+i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row+i][prev_pos_col+i] != EMPTY_BOARD_POS)
                break;

        }
        for (int i = 1; i<8; i++){
            if((prev_pos_row-i == next_pos_row) && (prev_pos_col-i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row-i][prev_pos_col-i] != EMPTY_BOARD_POS)
                break;
        }
    }
    else{
        for (int i = 1; i<8; i++){
            if((prev_pos_row+i == next_pos_row) && (prev_pos_col-i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row+i][prev_pos_col-i] != EMPTY_BOARD_POS)
                break;

        }
        for (int i = 1; i<8; i++){
            if((prev_pos_row-i == next_pos_row) && (prev_pos_col+i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row-i][prev_pos_col+i] != EMPTY_BOARD_POS)
                break;

        }
    }
    return false;
}


char getColumnChar(int col){
    switch (col) {
        case 0:
            return 'A';
        case 1:
            return 'B';
        case 2:
            return 'C';
        case 3:
            return 'D';
        case 4:
            return 'E';
        case 5:
            return 'F';
        case 6:
            return 'G';
        case 7:
            return 'H';
    }
    return '$';
}



bool isValidRookMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){

    if(prev_pos_row == next_pos_row){
      
        int operator =1;
        if (prev_pos_col > next_pos_col)
            operator = -1;
        for(int i = 1; i<8; i++){
            if((prev_pos_col+(i*operator) == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row][prev_pos_col+(i*operator)] != EMPTY_BOARD_POS)
                break;

        }
    }
    
    if(prev_pos_col == next_pos_col){
     
        int operator = 1;
        if (prev_pos_row > next_pos_row)
            operator = -1;
        for(int i = 1; i<8; i++){
         
            if((prev_pos_row+(i*operator) == next_pos_row))
                return true;
            if(src->gameBoard[prev_pos_row+(i*operator)][prev_pos_col] != EMPTY_BOARD_POS)
                break;

        }
    }
    return false;
}





bool isValidKnightMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){

    
    int operatorRow =1;
    if (prev_pos_row < next_pos_row)
        operatorRow = -1;
    
    
    int operatorCol =1;
    if (prev_pos_col < next_pos_col)
        operatorCol = -1;
//    printf("HERE + %d/n", prev_pos_row);
//    printf("HERE + %d/n", prev_pos_col);
//    printf("HERE + %d/n", next_pos_row);
//    printf("HERE + %d/n", next_pos_col);
//    printf("HERE + %d/n", operatorRow);
//    printf("HERE + %d/n", operatorCol);
//    printf("HERE + %d/n", next_pos_row + (2*operatorRow));
//    printf("HERE + %d/n", next_pos_col+ (1*operatorCol));
//    printf("HERE + %d/n", next_pos_col + (2*operatorCol));
//    printf("HERE + %d/n", next_pos_row+ (1*operatorRow));
    if(prev_pos_row == next_pos_row + (2*operatorRow))
        if(prev_pos_col == next_pos_col+ (1*operatorCol))
            return true;
    if(prev_pos_col == next_pos_col + (2*operatorCol))
        if(prev_pos_row == next_pos_row+ (1*operatorRow))
            return true;
    return false;
}



//queen moves like bishop and rook combined.
bool isValidQueenMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    return (isValidRookMove(src,prev_pos_row,prev_pos_col,next_pos_row,next_pos_col) || isValidBishopMove(src,prev_pos_row,prev_pos_col,next_pos_row,next_pos_col));
}






bool isValidKingMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    bool isNotCheck = true;
    if (!(((prev_pos_col <= next_pos_col + 1)&&(prev_pos_col >= next_pos_col - 1))&&((prev_pos_row <= next_pos_row + 1)&&(prev_pos_row >= next_pos_row - 1)))) // king can move one cell
         return false;
    
    char destenationCellFigure = src->gameBoard[next_pos_row][next_pos_col];
    src->gameBoard[next_pos_row][next_pos_col] = src->gameBoard[prev_pos_row][prev_pos_col];
    src->gameBoard[prev_pos_row][prev_pos_col] = EMPTY_BOARD_POS;
    
    if(isUnderPressure(src, next_pos_row, next_pos_col)){
        isNotCheck = false;
    }
    
    src->gameBoard[prev_pos_row][prev_pos_col] =src->gameBoard[next_pos_row][next_pos_col];
    src->gameBoard[next_pos_row][next_pos_col] = destenationCellFigure;

    
    return isNotCheck;
}

bool isValidDestenetion(CURRENT_PLAYER player, char figure){
    if(figure == EMPTY_BOARD_POS)
        return true;
    if(isOpponentPosition(player, figure))
        return true;
    return false;
}


bool isOpponentPosition(CURRENT_PLAYER player, char figure){
    if(player == WHITES)
        return isBlackFigure(figure);
    else
        return isWhiteFigure(figure);
}

void switchCurrentPlayer(chessGame* src){
    if(src->currentPlayer == WHITES)
        src->currentPlayer = BLACKS;
    else
        src->currentPlayer = WHITES;
}


bool isWhiteFigure(char figure){
    return (figure == PAWN_WHITE) || (figure == BISHOP_WHITE)||(figure == KNIGHT_WHITE)||(figure == ROOK_WHITE)||(figure == QUEEN_WHITE)||(figure == KING_WHITE);
}


bool isBlackFigure(char figure){
    return (figure == PAWN_BLACK) || (figure == BISHOP_BLACK)||(figure == KNIGHT_BLACK)||(figure == ROOK_BLACK)||(figure == QUEEN_BLACK)||(figure == KING_BLACK);
}


bool isValidBoardPosition(prev_pos_row, prev_pos_col, next_pos_row, next_pos_col){
    if((prev_pos_row<0)||(prev_pos_row>=BOARD_SIZE)){
        return false;
    }
    if((prev_pos_col<0)||(prev_pos_col>=BOARD_SIZE)){
        return false;
    }
    if((next_pos_row<0)||(next_pos_row>=BOARD_SIZE)){
        return false;
    }
    if((next_pos_col<0)||(next_pos_col>=BOARD_SIZE)){
        return false;
    }
    return true;
}



void initChessBoard(chessGame* src){
    for(int i = 0; i<BOARD_SIZE; i++)
        for(int j = 0; j <BOARD_SIZE; j++)
            src->gameBoard[i][j] = EMPTY_BOARD_POS;
    for(int i = 0; i < BOARD_SIZE; i++){
        src->gameBoard[1][i] = PAWN_WHITE;
        src->gameBoard[6][i] = PAWN_BLACK;
        
    }
    
    //whites
    src->gameBoard[0][0] = ROOK_WHITE;
    src->gameBoard[0][1] = KNIGHT_WHITE;
    src->gameBoard[0][2] = BISHOP_WHITE;
    src->gameBoard[0][3] = QUEEN_WHITE;
    src->gameBoard[0][4] = KING_WHITE;
    src->gameBoard[0][5] = BISHOP_WHITE;
    src->gameBoard[0][6] = KNIGHT_WHITE;
    src->gameBoard[0][7] = ROOK_WHITE;
    
    
    
    //blacks
    src->gameBoard[7][0] = ROOK_BLACK;
    src->gameBoard[7][1] = KNIGHT_BLACK;
    src->gameBoard[7][2] = BISHOP_BLACK;
    src->gameBoard[7][3] = QUEEN_BLACK;
    src->gameBoard[7][4] = KING_BLACK;
    src->gameBoard[7][5] = BISHOP_BLACK;
    src->gameBoard[7][6] = KNIGHT_BLACK;
    src->gameBoard[7][7] = ROOK_BLACK;
}



bool isUnderPressure(chessGame* src, int row, int col){
    
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
           
            if(isWhiteFigure(src->gameBoard[row][col])){
                if(isBlackFigure(src->gameBoard[i][j])){
                    if(isValidMove(src, i, j, row, col)){
                        return true;
                    }
                    
                }
            }
            
            if(isBlackFigure(src->gameBoard[row][col])){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(isValidMove(src, i, j, row, col))
                        return true;
                }
            }
        }
    }
    
    printf("Just checked empty filed - why did you do it?"); //delete
    return false;
}



///TEST

