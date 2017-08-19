//
//  main.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 17/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Chess_gameUtils.h"
#include "Chess_gameUtilsAux.h"
#include "SPMiniMax.h"

#include <stdbool.h>


void TestBoard(chessGame* src);

int main(int argc, const char * argv[]) {
    printf("Hello, World!\n");
    chessGame* src = createChessGame(5, TWO_PLAYERS);
    TestBoard(src);
    chessConsolePrintBoard(src);
    printf("hello\n");
    printf("\n%d\n",isValidMove(src, 1, 5, 3, 7) == true);
    printf("\n%d\n",isValidMove(src, 1, 5, 2, 6) == true);
    

    
    
    return 0;
}


void TestBoard(chessGame* src){
    for(int i = 0; i<BOARD_SIZE; i++)
        for(int j = 0; j <BOARD_SIZE; j++)
            src->gameBoard[i][j] = EMPTY_BOARD_POS;
    
    
    //whites
    src->gameBoard[1][5] = QUEEN_WHITE;
    //src->gameBoard[0][1] = KING_WHITE;
    //    src->gameBoard[0][1] = KNIGHT_WHITE;
    //    src->gameBoard[0][2] = BISHOP_WHITE;
    //    src->gameBoard[0][3] = QUEEN_WHITE;
    //    src->gameBoard[0][4] = KING_WHITE;
    //    src->gameBoard[0][5] = BISHOP_WHITE;
    //    src->gameBoard[0][6] = KNIGHT_WHITE;
    //    src->gameBoard[0][7] = ROOK_WHITE;
    
    
    
    //blacks
    src->gameBoard[2][6] = QUEEN_BLACK;
    //src->gameBoard[5][0] = KING_BLACK;
    //    src->gameBoard[7][1] = KNIGHT_BLACK;
    //    src->gameBoard[7][2] = BISHOP_BLACK;
    //    src->gameBoard[7][3] = QUEEN_BLACK;
    //    src->gameBoard[7][4] = KING_BLACK;
    //    src->gameBoard[7][5] = BISHOP_BLACK;
    //    src->gameBoard[7][6] = KNIGHT_BLACK;
    //    src->gameBoard[7][7] = ROOK_BLACK;
}

