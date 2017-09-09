//
//  SPMiniMax.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//


#include "SPMiniMax.h"
#include <stdio.h>
#include <limits.h>

int suggestMove(chessGame* src,  int depth){
    //printf("START MINMAXTREE\n");
    int i =initMinmaxTree(src, depth);
    //printf("END MINMAXTREE\n");
    return i;
}





int comFunc(chessGame* currentGame){
    char figure = '_';
    
    
    int blackArray[5] = {0,0,0,0,0};
    int whiteArray[5] = {0,0,0,0,0};
    int blackTotal = 0;
    int whiteTotal = 0;

    
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            figure = currentGame->gameBoard[i][j];
            switch (figure) {
                case PAWN_BLACK:
                    blackArray[0]++;
                    break;
                case BISHOP_BLACK:
                case KNIGHT_BLACK:
                    blackArray[1]++;
                    break;
                case ROOK_BLACK:
                    blackArray[2]++;
                    break;
                case QUEEN_BLACK:
                    blackArray[3]++;
                    break;
                case KING_BLACK:
                    blackArray[4]++;
                    break;
                case PAWN_WHITE:
                    whiteArray[0]++;
                    break;
                case BISHOP_WHITE:
                case KNIGHT_WHITE:
                    whiteArray[1]++;
                    break;
                case ROOK_WHITE:
                    whiteArray[2]++;
                    break;
                case QUEEN_WHITE:
                    whiteArray[3]++;
                    break;
                case KING_WHITE:
                    whiteArray[4]++;
                    break;
                default:
                    break;
            }
        }
    }

    whiteTotal = whiteArray[0]*1 + whiteArray[1]*3 + whiteArray[2]*5 + whiteArray[3]*9 + whiteArray[4]*100;
    blackTotal = blackArray[0]*1 + blackArray[1]*3 + blackArray[2]*5 + blackArray[3]*9 + blackArray[4]*100;
    
    return (whiteTotal - blackTotal) ;
}





int initMinmaxTree(chessGame* currentGame, int depth){
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int max = INT_MIN;
    int min = INT_MAX;
    int temp = 0;
    int bestMoveMax[4]  = {-1,-1,-1,-1};
    int bestMoveMin[4]  = {-1,-1,-1,-1};
    movesArray* moves;
    int index = 0;
    
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(isBlackFigure(currentGame->gameBoard[i][j])){
                moves = allPossibleMoves(currentGame, i, j);
                while(moves->moves[index][0] != -1){
                    index++;
                    setChessMove(currentGame, moves->moves[index][0], moves->moves[index][1], moves->moves[index][2], moves->moves[index][3]);
                    temp = minmaxTree(currentGame, depth-1, alpha, beta);
                    undoChessPrevMove(currentGame);
                    
                    if(temp>max){
                        bestMoveMax[0] = moves->moves[index][0];
                        bestMoveMax[1] = moves->moves[index][1];
                        bestMoveMax[2] = moves->moves[index][2];
                        bestMoveMax[3] = moves->moves[index][3];
                        max = temp;
                    }
                    if(temp<min){
                        bestMoveMin[0] = moves->moves[index][0];
                        bestMoveMin[1] = moves->moves[index][1];
                        bestMoveMin[2] = moves->moves[index][2];
                        bestMoveMin[3] = moves->moves[index][3];
                        min = temp;
                    }
                }
            }
        }
    }
    
    if (currentGame->currentPlayer==WHITES)
        return bestMoveMax[0];
    return bestMoveMin[0];
}




int minmaxTree(chessGame* currentGame, int depth, int alpha, int beta){
    if ((depth == 0) || isCheckmate(currentGame) || isStalemate(currentGame)){
        return comFunc(currentGame);
    }
    movesArray* moves;
    int index = 0;
    if (currentGame->currentPlayer==WHITES){
        int v = INT_MIN;
        for(int i = 0; i<BOARD_SIZE; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(isWhiteFigure((currentGame->gameBoard[i][j]))){
                    moves = allPossibleMoves(currentGame, i, j);
                    while(moves->moves[index][0] != -1){
                        index++;
                        
                        setChessMove(currentGame, moves->moves[index][0], moves->moves[index][1], moves->moves[index][2], moves->moves[index][3]);
                        
                        v = maxFunc(v, minmaxTree(currentGame, depth-1, alpha, beta));
                        undoChessPrevMove(currentGame);
                        alpha = maxFunc(alpha, v);
                        if (beta <= alpha)
                            break;
                    }
                    return v;
                
                }
            }
        }
    }
    else{
        int v = INT_MAX;
        for(int i = 0; i<BOARD_SIZE; i++){
            for(int j = 0; j<BOARD_SIZE; j++){
                if(isBlackFigure((currentGame->gameBoard[i][j]))){
                    moves = allPossibleMoves(currentGame, i, j);
                    while(moves->moves[index][0] != -1){
                        index++;
                        
                        setChessMove(currentGame, moves->moves[index][0], moves->moves[index][1], moves->moves[index][2], moves->moves[index][3]);
                        v = minFunc(v, minmaxTree(currentGame, depth-1, alpha, beta));
                        undoChessPrevMove(currentGame);
            
                        beta = minFunc(beta, v);
                        if(beta <= alpha)
                                break;
                    }
                    return v;

                }
            }
        }
    }
    printf("if we are here - we have a problem with minmax :( \n");
    return 0;
}


int maxFunc(int a, int b)
{
    if (a>=b)
        return a;
    return b;
}
int minFunc(int a, int b){
    if (a<=b)
        return a;
    return b;
}
