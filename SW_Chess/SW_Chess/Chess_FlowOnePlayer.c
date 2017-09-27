
#include "Chess_FlowOnePlayer.h"

GAME_STATUS onePlayerGameFlow(chessGame* src){
    bool printBoard = true; /* should we print the game board on next iretation */
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
            printBoard = true; /* default = true */
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
        printf("JJ");
        if(cmd.cmd == CHESS_SAVE){
            saveGame(src, input); 
            printBoard = false;
            continue;
        }
        if(cmd.cmd == CHESS_MOVE){
            if((!cmd.isValidFirstPair) || (!cmd.isValidSecondPair)){
                printf("Illigal argument\n");
                printBoard = false;
                continue;
            }
            printBoard = humanMove(src, cmd);
            continue;
        }
        if(cmd.cmd == CHESS_UNDO_MOVE){
            if(undoChessPrevMove(src, true) == CHESS_GAME_NO_HISTORY){
                printf("Empty history, move cannot be undone\n");
                printBoard = false;
                continue;
            }
            if(undoChessPrevMove(src, true) == CHESS_GAME_NO_HISTORY){
                printf("Empty history, move cannot be undone\n");
                printBoard = false;
                continue;
            }
            continue;
        }
    }
}


bool humanMove(chessGame* src, CHESSCommand cmd){
    
    CHESS_GAME_MESSAGE message = setChessMove(src, (cmd.sourceRow -1), getIntFromColumnChar(cmd.sourceColl), (cmd.targertRow -1), getIntFromColumnChar(cmd.targetColl), true, true);
    if(message == CHESS_GAME_SUCCESS){
        return true; /*  perfect! */
    }
    /* an error took place */
    if(message == CHESS_GAME_INVALID_ARGUMENT)
        printf("Invalid position on the board\n");
    if(message == CHESS_GAME_INVALID_POSITION)
        printf("The specified position does not contain your piece\n");
    if(message == CHESS_GAME_INVALID_MOVE)
        printf("Illegal move\n");
    return false;
}


bool compMove(chessGame* src){
    int depth = minFunc(src->difficulty, 4); /* if difficulty == 5, depth is stil 40 */
    
    SPArrayListNode* move = suggestMove(src, depth);
    if(!move){
        printf("ERROR - cannot suggest move");
        return false;
    }
    setChessMove(src, move->prev_pos_row, move->prev_pos_col, move->current_pos_row, move->current_pos_col, false, true);

    printf("Computer: move %s at <%d,%c> to <%d,%c>\n",getFigureStringName(src->gameBoard[move->current_pos_row][move->current_pos_col]),move->prev_pos_row+1,getColumnChar(move->prev_pos_col),move->current_pos_row+1,getColumnChar(move->current_pos_col));
    
    free(move);
    
    return true;
}





