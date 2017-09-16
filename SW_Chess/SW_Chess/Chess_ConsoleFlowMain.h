//
//  Chess_ConsoleFlowMain.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_ConsoleFlowMain_h
#define Chess_ConsoleFlowMain_h

#include <stdio.h>
#include "Chess_def.h"
#include "Chess_gameParser.h"
#include "Chess_gameUtils.h"
#include "Chess_gameSettingsParser.h"
#include "Chess_FlowTwoPlayers.h"
#include "Chess_FlowOnePlayer.h"

/**
 * Init the console mode (calls the settingsStateConsole func)
 *
 * @returns nothing
 */
void consoleMode();

/**
 * Init the setting mode of the console game - eventually may call onePlayer or twoPlayer
 * event loops, thus starting the game stage.
 *
 * @returns nothing
 */
void settingsStateConsole();
#endif /* Chess_ConsoleFlowMain_h */
