//
//  Chess_FlowTwoPlayers.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_FlowTwoPlayers.h"


GAME_STATUS two_players_flow(chessGame* src){
    bool printBoard = true;
     GAME_STATUS status = NULL;
    while (true){
        if(printBoard)
            chessConsolePrintBoard(src);
        else
            printBoard = true;
        printf("%s player - enter your move:\n", getCurrentPlayerStringName(src));
        char input[SP_MAX_LINE_LENGTH];
        fgets(input,  SP_MAX_LINE_LENGTH, stdin);
        CHESSCommand cmd = spParserLine(input);
        /*
         quit -> RETURN QUIT
         reset -> RETURN RESET
         invalidline -> printboard = false + continue
         undo_move -> error + printboard = false + continur
         CHESS_SAVE -> func saveGame(input), if true/false, printboard = false + continue,
         CHESS_MOVE -> func checkmove(isvalidmove + ERRORS), if true -> setMove; else -> printboard false + continue
         chck if checkmate -> print check + return GAMEOVER
         check if tie -> print +return GAMEOVER
         check is check -> print check // all three in one func
    }
         
        */
     
     
     
     
     
     
     
     
     
     
     */
  
    return status;
    
}




