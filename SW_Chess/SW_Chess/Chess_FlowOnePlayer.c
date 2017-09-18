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
            compMove(src);
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
            if(undoChessPrevMove(src, true) == CHESS_GAME_NO_HISTORY)
                printf("Empty history, move cannot be undone\n");
            if(undoChessPrevMove(src, true) == CHESS_GAME_NO_HISTORY)
                printf("Empty history, move cannot be undone\n");
            continue;
        }
    }
}


bool humanMove(chessGame* src, CHESSCommand cmd){
    CHESS_GAME_MESSAGE message = setChessMove(src, (cmd.sourceRow -1), getIntFromColumnChar(cmd.sourceColl), (cmd.targertRow -1), getIntFromColumnChar(cmd.targetColl), true);
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


bool compMove(chessGame* src){
    SPArrayListNode* move = suggestMove(src, src->difficulty);
    if(move == NULL){
        printf("ERROR");
        return false;
    }
    setChessMove(src, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false);
    free(move);
    return false;
}







/*
todo:

1. documentation
3. MinMax check - mostly done
6. add/fix load game



known bugs:
 1. when doing the move command, <E,3> does not produce an error (despite being in the wrong format, the digit should be first).
 3. MinMax tends to come to a loop - maybe add a randomization factor? Generally it works I think. Give some people a chance to play against it and see if a basic improvment needed.
 5. there's a memory leak - not sure where, but it appears in compVcomp, maybe in mainGame as well.
 6. spParserIsValidOrederedPair - when I just enter move (game stage) - prgram is teminated. 
 
 
bonuses:
1. add ROOKING
2. add CROWNINNG
3. add GET_ALL_MOVES FUNC - already have printing in format, just add where applicable
5. add better minmax
6. conbine isStealmate && isCheckmate && isCheck


*/
