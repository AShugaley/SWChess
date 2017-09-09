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
            printf("Illigal command");
            printBoard = false;
            continue;
        }
        if(cmd.cmd == CHESS_SAVE){
            saveGame(src, input); //tochange to cmd.arg
            printBoard = false;
            continue;
        }
        if(cmd.cmd == CHESS_MOVE){
            //todo
        }
        if(cmd.cmd == CHESS_UNDO_MOVE){
            //todo
        }
        
    }
    return status;
}
        /*
         undo_move -> error + printboard = false + continur
         CHESS_MOVE -> func checkmove(isvalidmove + ERRORS), if true -> setMove; else -> printboard false + continue
    }
         
        */
     
     
     
     
     
     
     
     
     
     



