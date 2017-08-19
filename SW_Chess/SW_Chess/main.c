//
//  main.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 17/08/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include <stdio.h>
#include "Chess_gameUtils.h"



int main(int argc, const char * argv[]) {
    printf("Hello, World!\n");
    chessGame* src = createChessGame(5, TWO_PLAYERS);
    chessConsolePrintBoard(src);
    
    
    return 0;
}
