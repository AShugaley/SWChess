//
//  Chess_gameUtils.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_gameUtils.h"
#include "Chess_gameUtilsAux.h"
#include <assert.h>

#include <stdlib.h>




chessGame* createChessGame(int historySize, GAME_MODE mode)
{

    if (historySize <= 0)
        return NULL;
    
    chessGame *gameSt = (chessGame *)malloc(sizeof(chessGame));
    if (gameSt == NULL)
        return NULL;
    

    gameSt->currentPlayer = WHITES;
   // gameSt->historyArray = spArrayListCreate(historySize);
    gameSt->gameMode = mode;
    
    initChessBoard(gameSt);
    
    return gameSt;
    
}


chessGame* copyChessGame(chessGame* src){ // INCOMPLETE!!
    chessGame *gameSt = (chessGame *)malloc(sizeof(chessGame));
    if (gameSt == NULL)
        return NULL;
    for(int i = 0; i<BOARD_SIZE; i++)
        for(int j = 0; j<BOARD_SIZE; j++)
            gameSt->gameBoard[i][j] = src->gameBoard[i][j];
    gameSt->currentPlayer = src->currentPlayer;
    
    //NEED ADD COPY OF HISTORY ARRAY!!
    
    gameSt->gameMode = src->gameMode;
    
    return gameSt;
    
}

void destroyChessGame(chessGame* src){
    if (src != NULL)
    {
   //     spArrayListDestroy(src->historyArray);
        free(src);
    }
}


CHESS_GAME_MESSAGE chessConsolePrintBoard(chessGame* src) {
    if (src == NULL)
        return CHESS_GAME_INVALID_ARGUMENT;
    for (int i = BOARD_SIZE - 1; i>-1; i--) {
        printf("%d| ", i+1 );
        for (int j = 0; j<BOARD_SIZE; j++) {
            printf("%c ", src->gameBoard[i][j]);
        }
        printf("|\n");
    }
    printf("  -----------------  \n");
    printf("   A B C D E F G H   \n");
    return CHESS_GAME_SUCCESS;
}



bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    
    char figure = src->gameBoard[prev_pos_row][prev_pos_col];
    assert(figure != EMPTY_BOARD_POS);
    CURRENT_PLAYER player;
    
    
    if(isWhiteFigure(figure))
        player = WHITES;
    else
        player = BLACKS;
    
    
    if(!isValidDestenetion(player, src->gameBoard[next_pos_row][next_pos_col]))
        return false;
    
    switch(figure){
        case PAWN_BLACK:
        case PAWN_WHITE:
              return isValidPawnMove(src, prev_pos_row, prev_pos_row, next_pos_row, next_pos_col);
        case BISHOP_BLACK:
        case BISHOP_WHITE:
              return isValidBishopMove(src, prev_pos_row, prev_pos_row, next_pos_row, next_pos_col);
        case KNIGHT_BLACK:
        case KNIGHT_WHITE:
              return isValidKnightMove(src, prev_pos_row, prev_pos_row, next_pos_row, next_pos_col);
        case ROOK_BLACK:
        case ROOK_WHITE:
              return isValidRookMove(src, prev_pos_row, prev_pos_row, next_pos_row, next_pos_col);
        case QUEEN_BLACK:
        case QUEEN_WHITE:
              return isValidQueenMove(src, prev_pos_row, prev_pos_row, next_pos_row, next_pos_col);
        case KING_WHITE:
        case KING_BLACK:
              return isValidKingMove(src, prev_pos_row, prev_pos_row, next_pos_row, next_pos_col);
    }
    printf("should not get here #453"); // delete
    return false;
}


CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col){
    if(src->gameBoard[prev_pos_row][prev_pos_col] == EMPTY_BOARD_POS)
        return CHESS_GAME_INVALID_ARGUMENT;
    if(!isValidBoardPosition(prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
        return CHESS_GAME_INVALID_ARGUMENT;
    if(!isValidMove(src, prev_pos_row, prev_pos_col, next_pos_row, next_pos_col))
        return CHESS_GAME_INVALID_MOVE;
    src->gameBoard[next_pos_row][next_pos_col] = src->gameBoard[prev_pos_row][prev_pos_col];
    src->gameBoard[prev_pos_row][prev_pos_col] = EMPTY_BOARD_POS;
    return CHESS_GAME_SUCCESS;
}































bool isCheckmate(chessGame* src){
    bool checkmate = false;
    switchCurrentPlayer(src);
    if(isCheck(src))
       checkmate = true;
    switchCurrentPlayer(src);
    return checkmate;
}

bool hasValidMove(chessGame* src, int row, int col){
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(isValidMove(src, row, col, i, j))
                return true;
        }
    }
    return false;
}


bool isStalemate(chessGame* src){
    bool has_valid_move = false;
    bool under_pressure = false;
    if(src->currentPlayer == WHITES){
        for(int i = 0; i<BOARD_SIZE; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(src->gameBoard[i][j] == KING_WHITE){
                        under_pressure = isUnderPressure(src, i, j);
                    }
                    has_valid_move = hasValidMove(src, i, j);
                }
            }
        }
    }
    else{
        for(int i = 0; i<BOARD_SIZE; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(isWhiteFigure(src->gameBoard[i][j])){
                    if(src->gameBoard[i][j] == KING_WHITE){
                        under_pressure = isUnderPressure(src, i, j);
                    }
                has_valid_move = hasValidMove(src, i, j);
                }
            }
        }
    }
    return (!under_pressure && !has_valid_move);
            
        
}


bool isCheck(chessGame* src){
    
    int king_row = -1, king_col = -1;
    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(src->currentPlayer == WHITES){
                if(src->gameBoard[i][j] == KING_WHITE){
                    king_row = i;
                    king_col = j;
                }
            }
            else{
                if(src->gameBoard[i][j] == KING_BLACK){
                    king_row = i;
                    king_col = j;
                }
            }
        }
    }
    
    
    assert((king_col != -1) && (king_row != -1));
    return (isUnderPressure(src, king_row, king_col));

}
