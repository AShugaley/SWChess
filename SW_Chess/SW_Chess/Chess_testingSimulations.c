
#include "Chess_testingSimulations.h"


//play comp vs comp, d1 - white comp difficulty, d2 - black comp difficulty

void testSimulation(int d1,int d2){
    runTestSim(d1,d2);
}


void runTestSim(int d1,int d2){
    int index = 0;
    time_t tot = 0;
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
        time_t t1 = clock();
        compMove(src);
        time_t t2 = clock();
        printf("comp move took %ld millis\n", t2-t1);
        tot = tot + (t2-t1);
        printf("move %d, avarage move time = %ld\n", ++index, (tot/index));
        chessConsolePrintBoard(src);

    }
    
}
