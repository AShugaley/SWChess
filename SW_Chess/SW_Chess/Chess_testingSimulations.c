//
//  Chess_testingSimulations.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 16/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_testingSimulations.h"
void testSimulation(int d1,int d2){
    runTestSim(d1,d2);
}


void runTestSim(int d1,int d2){
    chessGame* src = createChessGame(8, ONE_PLAYER, WHITES, 2);
    int v = 1;
    while (true){
        checkGameEnd(src);
        if(v == 1){
            src->difficulty = d1;
            v = 2;
        }
        else{
            src->difficulty = d2;
            v = 1;
        }
        compMove(src);
        chessConsolePrintBoard(src);
        }

}
