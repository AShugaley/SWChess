

#include "SPMiniMax.h"
#include <stdio.h>
#include <limits.h>

SPArrayListNode* suggestMove(chessGame* src,  int depth){

    chessGame* gameCopy =copyChessGame(src);
    SPArrayListNode* i = initMinmaxTree(gameCopy, depth);
    destroyChessGame(gameCopy);
 
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



SPArrayListNode* initMinmaxTree(chessGame* currentGame, int depth){
    SPArrayListNode* bestMaxMove = (SPArrayListNode*)malloc(sizeof(SPArrayListNode));
    SPArrayListNode* bestMinMove = (SPArrayListNode*)malloc(sizeof(SPArrayListNode));
    if((bestMaxMove == NULL) || (bestMaxMove == NULL)) /* mem alloc failure */
        return NULL;
    int bestMax = INT_MIN;
    int bestMin = INT_MAX;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int temp;
    if(currentGame->currentPlayer == WHITES){
        for(int i = 0; i<8;i++){
            for(int j = 0; j<8; j++){
                if(isWhiteFigure(currentGame->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(currentGame, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        SPArrayListNode* move = spArrayListGetFirst(moves);
            
                        setChessMove(currentGame, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false,true);

                        temp =minmaxTree(currentGame, depth-1, alpha, beta);
                        if(temp > bestMax){
                            *bestMaxMove = *move;
                            bestMax = temp;
                        }
                        spArrayListRemoveFirst(moves);
                        undoChessPrevMove(currentGame, false);
                    }
                    spArrayListDestroy(moves);
                }

            }
        }
        free(bestMinMove);
        return bestMaxMove;
    }
    else{
        for(int i = 0; i<8;i++){
            for(int j = 0; j<8; j++){
                if(isBlackFigure(currentGame->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(currentGame, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        SPArrayListNode* move = spArrayListGetFirst(moves);
                       
                        setChessMove(currentGame, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false,true);
                        temp = minmaxTree(currentGame, depth-1, alpha, beta);
            

                        if(temp < bestMin){
                            *bestMinMove = *move;
                            bestMin = temp;
                        }
                        spArrayListRemoveFirst(moves);
                        undoChessPrevMove(currentGame, false);
                    }
                    spArrayListDestroy(moves);
                }
                
            }
        }
        free(bestMaxMove);
        return bestMinMove;
    }
}












int minmaxTree(chessGame* currentGame, int depth, int alpha, int beta){
    if(depth == 0){ /* terminal node */

        return comFunc(currentGame);
    }
    if(isStalemate(currentGame)||isCheckmate(currentGame)){ /* terminal node */
        
        return comFunc(currentGame);
    }
    
    if(currentGame->currentPlayer == WHITES){
        int v = INT_MIN;
        for(int i = 0; i< 8; i++){
            for(int j = 0; j<8; j++){
                if(isWhiteFigure(currentGame->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(currentGame, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        SPArrayListNode* move = spArrayListGetFirst(moves);
                        
                        setChessMove(currentGame, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false,true);
                        v = maxFunc(v, minmaxTree(currentGame, depth-1, alpha, beta));
                        alpha = maxFunc(alpha, v);
                        undoChessPrevMove(currentGame, false);
                        if(beta <= alpha)
                            return v;
                        spArrayListRemoveFirst(moves);
                    }
                    spArrayListDestroy(moves);
                }
            }
        }
        return v;
    }
    else{
        int v = INT_MAX;
        for(int i = 0; i< 8; i++){
            for(int j = 0; j<8; j++){
                if(isBlackFigure(currentGame->gameBoard[i][j])){
                    SPArrayList* moves = allPossibleMoves(currentGame, i, j);
                    while(!spArrayListIsEmpty(moves)){
                        SPArrayListNode* move = spArrayListGetFirst(moves);
                        
                        setChessMove(currentGame, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false,true);
                        v = minFunc(v, minmaxTree(currentGame, depth-1, alpha, beta));
                        alpha = minFunc(beta, v);
                        undoChessPrevMove(currentGame, false);
                        if(beta <= alpha)
                            return v;
                        spArrayListRemoveFirst(moves);
                    }
                    spArrayListDestroy(moves);
                }
            }
        }

        return v;
    }
    

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

