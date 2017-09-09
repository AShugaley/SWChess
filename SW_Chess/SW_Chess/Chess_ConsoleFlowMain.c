//
//  Chess_ConsoleFlowMain.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_ConsoleFlowMain.h"



void consoleMode(){
    settingsStateConsole();
}


void settingsStateConsole(){
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
    chessGame* src = createChessGame(4, ONE_PLAYER, WHITES, 2); // default arg
    char input[SP_MAX_LINE_LENGTH];
    CHESSSettingCommand setcmd;
    while(true){
        fgets(input,  SP_MAX_LINE_LENGTH, stdin);
        setcmd = spParserSettingLine(input);
        if(setcmd.cmd == CHESS_START){
            if(src->gameMode == ONE_PLAYER)
                onePlayerGameFlow(src);
            else
                twoPlayersGameFlow(src);
            break;
        }
        if(setcmd.cmd == CHESS_DIFFICULTY){
            if(src->gameMode == TWO_PLAYERS){
                printf("Illigal command\n");
                continue;
            }
            if((setcmd.arg > 5) || (setcmd.arg < 1)){
                printf("Wrong difficulty level. The value should be between 1 to 5\n");
                continue;
            }
            src->difficulty = setcmd.arg;
            continue;
        }
        if(setcmd.cmd == CHESS_MODE){
            if(setcmd.arg == 1){
                src->gameMode = ONE_PLAYER;
                printf("Game mode is set to 1 player\n");
                continue;
            }
            if(setcmd.arg == 2){
                src->gameMode = TWO_PLAYERS;
                printf("Game mode is set to 2 players\n");
                continue;
            }
            printf("Wrong game mode\n");
            continue;
        }
        if(setcmd.cmd == CHESS_COLOR){
            if(src->gameMode == TWO_PLAYERS){
                printf("Illigal command\n");
                continue;
            }
            if(setcmd.arg == 1){
                src->humanPlayerColor = WHITES;
                continue;
            }
            if(setcmd.arg == 0){
                src->humanPlayerColor = BLACKS;
                continue;
            }
            printf("Illigal color\n");
            continue;
        }
        if(setcmd.cmd == CHESS_DEFAULT){
            src->humanPlayerColor = WHITES;
            src->difficulty = 2;
            src->gameMode = ONE_PLAYER;
        }
        if(setcmd.cmd == CHESS_PRINT_SETTINGS){
            printf("SETTINGS:\n");
            if(src->gameMode == TWO_PLAYERS){
                printf("GAME_MODE: 2\n");
                continue;
            }
            printf("GAME_MODE: 1\n");
            printf("DIFFICULTY_LVL: %d\n", src->difficulty);
            if(src->humanPlayerColor == WHITES)
                printf("USER_CLR: WHITE\n");
            else
                printf("USER_CLR: BLACK\n");
            continue;
        }
        if(setcmd.cmd == CHESS_LOAD){
            //toadd
            continue;
        }
        if(setcmd.cmd == CHESS_INVALID_SETTING_LINE){
            printf("Illigal command\n");
            continue;
        }
        if(setcmd.cmd == CHESS_INVALID_SETTING_LINE){
            terminateGame(src);
            continue;
        }
    }
}

    
    
/*
main.c -> settings -> one/two -> setMove/compMove/save -> one/two
 one/two(restart) -> settings
*/
