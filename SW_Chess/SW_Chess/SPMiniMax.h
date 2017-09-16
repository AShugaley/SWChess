#ifndef SPMiniMax_h
#define SPMiniMax_h

#include <stdio.h>
#include "Chess_gameUtilsAux.h"
#include "SPMiniMax.h"
#include "Chess_gameUtils.h"
SPArrayListNode* suggestMove(chessGame* src, int depth);
int comFunc(chessGame* currentGame);
SPArrayListNode* initMinmaxTree(chessGame* currentGame, int depth);
int minmaxTree(chessGame* currentGame, int depth, int alpha, int beta);
int maxFunc(int a, int b);
int minFunc(int a, int b);



#endif /* SPMiniMax_h */
