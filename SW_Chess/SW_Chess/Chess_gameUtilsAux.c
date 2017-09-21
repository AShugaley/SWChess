

#include "Chess_gameUtilsAux.h"
#include "Chess_gameUtils.h"
#include <stdbool.h>

/* In all functions, we assume that the arguments are legal - i.e. 0<=pos<=7. We check it elsewhere - the comp will do so by himself, and we will check arguments from the user on input.
*/


/* like all the following function, merely checks if a move is legal from figure movment perspective */
bool isValidPawnMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
  
    int first_row = 0;
    int operator = 1;
    if (src->gameBoard[prev_pos_row][prev_pos_col] == PAWN_BLACK){
        first_row = 7;
        operator = -1;
    }
   
    if (prev_pos_col != next_pos_col){ /* pawns move only on the same column, unless they take another figure - this is what we check here */
        if((next_pos_row == prev_pos_row+(1*operator))&&(src->gameBoard[next_pos_row][next_pos_col] != EMPTY_BOARD_POS)&&((prev_pos_col+1 == next_pos_col)||(prev_pos_col-1==next_pos_col))) /* the pawn took oponnent figure */
            return true;
        else
            return false; /* illigal move */
    }
    
    if ((prev_pos_row+(1*operator) == next_pos_row)&&(src->gameBoard[next_pos_row][next_pos_col] == EMPTY_BOARD_POS))
        return true; /* regular move */
    if ((prev_pos_row == first_row+(1*operator)) && (prev_pos_row+(2*operator) == next_pos_row) && (src->gameBoard[prev_pos_row+(1*operator)][prev_pos_col] == EMPTY_BOARD_POS) &&(src->gameBoard[next_pos_row][next_pos_col] == EMPTY_BOARD_POS))
        return true; /* first move */
  
    return false; /* that's not how pawns work, friend */
}


bool isValidBishopMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    if((prev_pos_row+prev_pos_col) != (next_pos_row+next_pos_col)){ /* bottom-left to top-right diagunal move */
        for (int i = 1; i<8; i++){ /* going top */
            if((prev_pos_row+i == next_pos_row) && (prev_pos_col+i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row+i][prev_pos_col+i] != EMPTY_BOARD_POS) /* Cant move through figures */
                break;

        }
        for (int i = 1; i<8; i++){ /* going bottom */
            if((prev_pos_row-i == next_pos_row) && (prev_pos_col-i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row-i][prev_pos_col-i] != EMPTY_BOARD_POS) /* Cant move through figures */
                break;
        }
    }
    else{ /* bottom-right to top-left diagunal move */
        for (int i = 1; i<8; i++){
            if((prev_pos_row+i == next_pos_row) && (prev_pos_col-i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row+i][prev_pos_col-i] != EMPTY_BOARD_POS) /* Cant move through figures */
                break;

        }
        for (int i = 1; i<8; i++){
            if((prev_pos_row-i == next_pos_row) && (prev_pos_col+i == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row-i][prev_pos_col+i] != EMPTY_BOARD_POS) /* Cant move through figures */
                break;

        }
    }
    return false; /* that's not how bishops work, girl */
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
    return '$'; /* Shouldn't get here - error symbol */
}


char getIntFromColumnChar(char col){
    switch (col) {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
    }
    return -1; /* Shouldn't get here - error symbol */
    
    
}


bool isValidRookMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){

    if(prev_pos_row == next_pos_row){  /* same row -> moving on column */
      
        int operator =1;
        if (prev_pos_col > next_pos_col)
            operator = -1;
        for(int i = 1; i<8; i++){
            if((prev_pos_col+(i*operator) == next_pos_col))
                return true;
            if(src->gameBoard[prev_pos_row][prev_pos_col+(i*operator)] != EMPTY_BOARD_POS)  /* Cant move through figures */
                break;

        }
    }
    
    if(prev_pos_col == next_pos_col){ /* same col -> moving on a row */
     
        int operator = 1;
        if (prev_pos_row > next_pos_row)
            operator = -1;
        for(int i = 1; i<8; i++){
         
            if((prev_pos_row+(i*operator) == next_pos_row))
                return true;
            if(src->gameBoard[prev_pos_row+(i*operator)][prev_pos_col] != EMPTY_BOARD_POS)  /* Cant move through figures */
                break;

        }
    }
    return false; /* that's not how rooks work, dude */
}





bool isValidKnightMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){

    /* CAN move through figures! */
    
    int operatorRow =1;
    if (prev_pos_row < next_pos_row)
        operatorRow = -1;
    
    
    int operatorCol =1;
    if (prev_pos_col < next_pos_col)
        operatorCol = -1;

    if(prev_pos_row == next_pos_row + (2*operatorRow))
        if(prev_pos_col == next_pos_col+ (1*operatorCol))
            return true;
    if(prev_pos_col == next_pos_col + (2*operatorCol))
        if(prev_pos_row == next_pos_row+ (1*operatorRow))
            return true;
    
    return false; /* that's not how knights work, player */
}



/* Queen moves like bishop and rook combined. */
bool isValidQueenMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    return (isValidRookMove(src,prev_pos_row,prev_pos_col,next_pos_row,next_pos_col) || isValidBishopMove(src,prev_pos_row,prev_pos_col,next_pos_row,next_pos_col));
    /* well that was short */
}






bool isValidKingMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    if (!(((prev_pos_col <= next_pos_col + 1)&&(prev_pos_col >= next_pos_col - 1))&&((prev_pos_row <= next_pos_row + 1)&&(prev_pos_row >= next_pos_row - 1)))) /* king can only move one cell */
         return false;
    return true; /* that IS how knights work! */
}

bool isValidDestenetion(PLAYER_COLOR player, char figure){
    if(figure == EMPTY_BOARD_POS)
        return true;
    if(isOpponentPosition(player, figure))
        return true;
    return false;
}


bool isOpponentPosition(PLAYER_COLOR player, char figure){
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
                    if(!(src->gameBoard[row][col] == KING_WHITE)){ /* unless it's a king, we need to check if a move is legal */
                        if(isLegalMove(src, i, j, row, col)){
                            return true;
                        }
                    }
                    /* But, if the destenation is a king, any VALID move will be LEGAL - refer to Chess_gameUtils.h for the difference between a LEGAL and a VALID move */
                    else{
                        if(isValidMove(src, i, j, row, col))
                            return true;
                    }
                }
            }
            
            if(isBlackFigure(src->gameBoard[row][col])){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(!(src->gameBoard[row][col] == KING_BLACK)){  /* unless it's a king, we need to check if a move is legal */
                        if(isLegalMove(src, i, j, row, col)){
                         
                            return true;
                        }
                    }
                    /* But, if the destenation is a king, any VALID move will be LEGAL - refer to Chess_gameUtils.h for the difference between a LEGAL and a VALID move */
                    else{
                        if(isValidMove(src, i, j, row, col))
                            return true;
                        
                    }
                }
            }
        }
    }
    return false;
}



/* this is used in case a check existed before this move. In such case, it means that:
 *   a) There is no checkmate (otherwise the game would terminate)
 *   b) The only legal move would be one preventing the check, i.e. a check cannot remain
 * thus we first check if there was a check, and if yes, we create a copy of the game, submit this new move
 * (that by now we know is legal from figure movment prespective), and check again if there's a check)
 */

bool checkAvoided(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    char prev_pos = src->gameBoard[next_pos_row][next_pos_col];
    src->gameBoard[next_pos_row][next_pos_col] = src->gameBoard[prev_pos_row][prev_pos_col];
    src->gameBoard[prev_pos_row][prev_pos_col] = EMPTY_BOARD_POS;
  
    bool check = isCheck(src);
    
    src->gameBoard[prev_pos_row][prev_pos_col] = src->gameBoard[next_pos_row][next_pos_col];
    src->gameBoard[next_pos_row][next_pos_col] = prev_pos;
    
    return !check;
}




