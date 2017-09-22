

#include "SPMiniMax.h"
#include <stdio.h>
#include <limits.h>

SPArrayListNode* suggestMove(chessGame* src,  int depth){

    chessGame* gameCopy =copyChessGame(src);
    SPArrayListNode* i = initMinmaxTree(gameCopy, depth);
    destroyChessGame(gameCopy);
 
    return i;
}





SPArrayListNode* initMinmaxTree(chessGame* currentGame, int depth){
    SPArrayListNode* bestMaxMove = (SPArrayListNode*)malloc(sizeof(SPArrayListNode));
    SPArrayListNode* bestMinMove = (SPArrayListNode*)malloc(sizeof(SPArrayListNode));
    if((bestMaxMove == NULL) || (bestMaxMove == NULL)) /* mem alloc failure */
        return NULL;
    double bestMax = INT_MIN;
    double bestMin = INT_MAX;
    double alpha = INT_MIN;
    double beta = INT_MAX;
    double temp;
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

double minmaxTree(chessGame* currentGame, int depth, double alpha, double beta){
    if(depth == 0){ /* terminal node */

        return utilityFunction(currentGame);
    }
    if(isStalemate(currentGame)||isCheckmate(currentGame)){ /* terminal node */
        
        return utilityFunction(currentGame);
    }
    
    if(currentGame->currentPlayer == WHITES){
        double v = INT_MIN;
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
        double v = INT_MAX;
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


double maxFunc(double a, double b)
{
    if (a>=b)
        return a;
    return b;
}
double minFunc(double a, double b){
    if (a<=b)
        return a;
    return b;
}

/* expert mode functions */

//we DONT have a number of possible moves.
// add randomization
// add score for better positions
// iterative deepening
// add deepening for best moves


bool checkPawnIsoDouBlo(chessGame* src, int row, int col){

    //check if a pawn is isolated (i.e. check all 8 fields
    
    int pawnsNearby = -1;
    for(int i = row -1; i < (row + 2); i++ ){
        for(int j = col -1; j < (col + 2); j++){
            pawnsNearby += (src->gameBoard[i][j] == src->gameBoard[row][col]);
        }
    }
    
    if(pawnsNearby < 1)
        return true;
    
    
    int pawnsInSameCol = -1;
    for(int j =0; j< 8; j++)
        pawnsInSameCol += (src->gameBoard[row][j] == src->gameBoard[row][col]);
    if(pawnsInSameCol > 0)
        return true;
    
    if(!hasValidMove(src, row, col))
        return true;
    
    return false;
}

//int getMobilityScore(chessGame* src, int row, int col){
//    int counter = 0;
//    //get all moves array FOR ALL FIGURES(?!) - count moves.
//    return counter;
//}



double getCentralPositionBonus(int row, int col){
    if (row > 3){
        row = 7 - row;
    }
    if (col > 3){
        col = 7 - col;
    }
    return 0.05*row*col;
}


double utilityFunction(chessGame* src){
    char figure = '_';
    bool isExpertMode = true;
    if(src->difficulty != 5)
        isExpertMode = false;
    double pawmAdjustmentScore = 0;
    double centralPositionBonus = 0;
    int blackArray[5] = {0,0,0,0,0};
    int whiteArray[5] = {0,0,0,0,0};
    int blackTotal = 0;
    int whiteTotal = 0;
    
    
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            figure = src->gameBoard[i][j];
            switch (figure) {
                case PAWN_BLACK:
                    blackArray[0]++;
                    if(isExpertMode){ /* a few other things to dramaticaly improve the AI */
                        pawmAdjustmentScore += 0.5*checkPawnIsoDouBlo(src,i,j);
                        centralPositionBonus -= getCentralPositionBonus(i,j);
                    }
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
                    if(isExpertMode){ /* a few other things to dramaticaly improve the AI */
                        pawmAdjustmentScore -= 0.5*checkPawnIsoDouBlo(src,i,j);
                        centralPositionBonus += getCentralPositionBonus(i,j);
                    }
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
    
    double ret = whiteTotal-blackTotal;
    if(isExpertMode)
        ret += (pawmAdjustmentScore + centralPositionBonus + (rand() % 100)*0.00001);
    //printf("exp = %f\n", ret );
    return ret;

}

/*
 struct
 we need: new compFunc. that will -> receive scoring from old fucntion. Go over all positions, and recieve position bonus + get randomization
          pawn check will be in the OLD compFunc

 iterative deepening for our minmax, can use old minmax (?) for this purpose 
 
 
 maybe bonus pos for all? not just pawns?
 
 additionl check for promising moves.
 
 */
