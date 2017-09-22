
#ifndef Chess_FlowTwoPlayers_h
#define Chess_FlowTwoPlayers_h
#include "Chess_def.h"
#include "Chess_gameParser.h"
#include "Chess_gameUtils.h"
#include "Chess_FlowOnePlayer.h"
#include <stdio.h>

/**
 * Chess_FlowOnePlayer summary:
 *
 * A container that includes the main event loop for the two player mode, uses some auxilary 
 * functions from OnePlayerFlow as well.
 * well).
 *
 * twoPlayersGameFlow    - The main loop of the two player mode, in console, in game stage.
 */



/**
 * The main event loop for twoPlayer game, when using the console mode
 *
 * @return an enum represnting the game outcome.
 */
GAME_STATUS twoPlayersGameFlow(chessGame* src);


#endif /* Chess_FlowTwoPlayers_h */
