

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
 * Chess_ConsoleFlowMain summary:
 *
 * A container includes the event loop of the settings stage in console mode 
 * after receiving the settings from the users, turns on onePlayerMode or
 * twoPlayerMode
 *
 * consoleMode           - initiates the console mode
 * settingsStateConsole  - The main loop of the settings stage

 */



/**
 * Init the console mode (calls the settingsStateConsole func)
 *
 * returns nothing
 */
void consoleMode();

/**
 * Init the setting mode of the console game - eventually may call onePlayer or twoPlayer
 * event loops, thus starting the game stage.
 *
 * returns nothing
 */
void settingsStateConsole();
#endif /* Chess_ConsoleFlowMain_h */
