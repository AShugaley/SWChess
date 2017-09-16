//
//  Chess_FlowOnePlayer.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_FlowOnePlayer_h
#define Chess_FlowOnePlayer_h
#include "SPMiniMax.h"
#include <stdio.h>
#include "Chess_def.h"
#include "Chess_gameParser.h"
#include "Chess_gameUtils.h"


/**
 * The main event loop for onePlayer game, when using the console mode
 *
 * @return an enum represnting the game outcome.
 */
GAME_STATUS onePlayerGameFlow(chessGame* src);

/**
 * Human player move -> checks that the input is valid, and if yes, submites the move (updates the game)
 *
 * @return true on sucessful move, else false
 */
bool humanMove(chessGame* src, CHESSCommand cmd);

/**
 * AI player move -> uses the suggestMove function in order to determine the best possible move
 * executes this move.
 *
 * @return true on sucessful move, else false
 */
bool compMove(chessGame* src);


#endif /* Chess_FlowOnePlayer_h */
