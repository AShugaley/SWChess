//
//  Chess_FlowOnePlayer.h
//  SW_Chess
//
//  Created by Alexander Shugaley on 08/09/2017.
//  Copyright © 2017 Alexander Shugaley. All rights reserved.
//

#ifndef Chess_FlowOnePlayer_h
#define Chess_FlowOnePlayer_h

#include <stdio.h>
#include "Chess_def.h"
#include "Chess_gameParser.h"
#include "Chess_gameUtils.h"

GAME_STATUS onePlayerGameFlow(chessGame* src);

bool humanMove(chessGame* src, CHESSCommand cmd);
#endif /* Chess_FlowOnePlayer_h */
