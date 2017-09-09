//
//  Chess_FlowOnePlayer.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_FlowOnePlayer.h"

GAME_STATUS onePlayerGameFlow(chessGame* src){
    bool printBoard = true;
    GAME_STATUS status = EMPTY;
    char input[SP_MAX_LINE_LENGTH];
    CHESSCommand cmd;
    while (true){
        checkGameEnd(src);
        if(src->currentPlayer != src->humanPlayerColor){
            //compMove(src); // todo
            continue;
        }
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
            //todo
            continue;
        }
    }
}


bool humanMove(chessGame* src, CHESSCommand cmd){
    CHESS_GAME_MESSAGE message = setChessMove(src, (cmd.sourceRow -1), getIntFromColumnChar(cmd.sourceColl), (cmd.targertRow -1), getIntFromColumnChar(cmd.targetColl));
    if(message == CHESS_GAME_SUCCESS){
        return true;
    }
    if(message == CHESS_GAME_INVALID_ARGUMENT)
        printf("Invalid position on the board\n");
    if(message == CHESS_GAME_INVALID_POSITION)
        printf("The specified position does not contain your piece\n");
    if(message == CHESS_GAME_INVALID_MOVE)
        printf("Illegal move\n");
    return false;
}

        /*
         undo_move -> undomove
         CHESS_SAVE -> func saveGame(input), if true/false, printboard = false + continue,
         CHESS_MOVE -> func checkmove(isvalidmove + ERRORS), if true -> setMove; else -> printboard false + continue

         }

*/






/*
todo:

1. documentation
2. compMove
3. MinMax check
4. verify history array - we need to save both comp and player moves, and undoX2. Anyway we need to double historySize.
5. add CHESS_UNDO_MOVE
6. add load game
7. improve parser to include path arg
8. verify that both full and relative paths are fine by fopen
9. check isStealmate, isCheckmate, isCheck
10. 



known bugs:
 1. when doing the move command, <E,3> does not produce an error (despite being in the wrong format, the digit should be first).
 
 
 
 
 
bonuses:
1. add ROOKING
2. add CROWNINNG
3. add GET_ALL_MOVES FUNC - already have printing in format, just add where applicable
5. add better minmax


*/
