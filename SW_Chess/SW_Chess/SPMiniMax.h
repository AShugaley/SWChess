//
//  SPMiniMax.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 19/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef SPMiniMax_h
#define SPMiniMax_h

#include <stdio.h>
#include "Chess_gameUtilsAux.h"
#include "SPMiniMax.h"

int suggestMove(chessGame* src, int depth);
int comFunc(chessGame* currentGame);
int initMinmaxTree(chessGame* currentGame, int depth);
int minmaxTree(chessGame* currentGame, int depth, int alpha, int beta);
int maxFunc(int a, int b);
int minFunc(int a, int b);



#endif /* SPMiniMax_h */
