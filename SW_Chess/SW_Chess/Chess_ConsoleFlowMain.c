//
//  Chess_ConsoleFlowMain.c
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#include "Chess_ConsoleFlowMain.h"


/*

settings:
print first line("entered game settings");
create game with default settings
while(true)
    input = fgets
    setcmd = settingsParser(input)
    setcmd == CHESS_START -> startone/starttwo + break
    setcmd == CHESS_DIFFICULTY -> check not checked before + check if valid + print error/set difficulty + continue -> func
    setcmd == CHESS_MODE -> check if valid + print error/set mode + continue -> func
    setcmd == CHESS_COLOR -> setcolor (same as previous commands)
    setcmd == CHESS_DEFAULT -> reset settings
    setcmd == CHESS_PRINT_SETTINGS -> print + continue
    setcmd == CHESS_SETTING_QUIT -> quit
    setcmd == CHESS_INVALID_SETTING_LINE -> print error + continue
    setcmd == load -> loadGame + continue
end




startGame:
 
 
 
 
 
 
main.c -> settings -> one/two -> setMove/compMove/save -> one/two
 one/two(restart) -> settings
    
