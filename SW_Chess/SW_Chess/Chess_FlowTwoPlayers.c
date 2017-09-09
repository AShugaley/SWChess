//
//  Chess_FlowTwoPlayers.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_FlowTwoPlayers.h"


GAME_STATUS twoPlayersGameFlow(chessGame* src){
    bool printBoard = true;
    GAME_STATUS status = EMPTY;
    CHESSCommand cmd;
    char input[SP_MAX_LINE_LENGTH];
    while (true){
        checkGameEnd(src);
        if(printBoard)
            chessConsolePrintBoard(src);
        else
            printBoard = true;
        printf("%s player - enter your move:\n", getCurrentPlayerStringName(src));
        fgets(input,  SP_MAX_LINE_LENGTH, stdin);
        cmd = spParserLine(input);
        if(cmd.cmd == CHESS_QUIT){
            printf("Exiting...\n");
            terminateGame(src);
        }
        if(cmd.cmd == CHESS_RESTART){
            printf("Restarting...\n");
            return status;
        }
        if(cmd.cmd == CHESS_INVALID_LINE){
            printf("Illigal command\n");
            printBoard = false;
            continue;
        }
        if(cmd.cmd == CHESS_SAVE){
            saveGame(src, input); //tochange to cmd.arg
            printBoard = false;
            continue;
        }
        if(cmd.cmd == CHESS_MOVE){
            printBoard = humanMove(src, cmd);
            continue;
        }
        if(cmd.cmd == CHESS_UNDO_MOVE){
            printf("Undo command not available in 2 players mode\n");
            continue;
        }
    }
    return status;
}

     
     
     
     
     
     
     
     
     
     



