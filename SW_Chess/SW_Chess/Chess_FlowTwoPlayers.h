//
//  Chess_FlowTwoPlayers.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_FlowTwoPlayers_h
#define Chess_FlowTwoPlayers_h
#include "Chess_def.h"
#include "Chess_gameParser.h"
#include "Chess_gameUtils.h"
#include "Chess_FlowOnePlayer.h"


#include <stdio.h>

/**
 * The main event loop for twoPlayer game, when using the console mode
 *
 * @return an enum represnting the game outcome.
 */
GAME_STATUS twoPlayersGameFlow(chessGame* src);


#endif /* Chess_FlowTwoPlayers_h */
