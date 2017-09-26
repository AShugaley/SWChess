
#ifndef Chess_gameUtils_h
#define Chess_gameUtils_h
#include <stdio.h>
#include <string.h>

#include "Chess_gameUtilsAux.h"
#include "Chess_ArrayList.h"

#include <stdbool.h>

//mine

/**
 * Chess_gameUtils summary:
 *
 * A container that includes the major set of functuins used during the chess game. Uses the gameUtilsAux as
 * an auxiliary extension file.
 *
 *
 * createChessGame             - Creates a chess game
 * copyChessGame               - Copies a chess game
 * destroyChessGame            - Destroies a chess game
 * setChessMove                - Sets the move ((x,y) -> (v,w))
 * isValidMove                 - Checks if a move ((x,y) -> (v,w)) is valid (from chess figure movments perspective.
 * hasValidMove                - Checks if a figure has any legal move
 * chessConsolePrintBoard      - Prints the game board in console mode
 * isCheck                     - Checks for a chess check
 * allPossibleMoves            - Returns all legal moves for a figure
 * isCheckmate                 - Checks for a chess checkmate
 * isStalemate                 - Checks for a chess tie
 * saveGame                    - saves the game to XML file
 * loadGame                    - loads a game from XML file
 * get_moves                   - Prints all the moves from allPossibleMoves func in a readble format
 * getCurrentPlayerStringName  - Retunes a string represenitg the current player (white/black)
 * checkGameEnd                - Checks if there's a check\tie\checkmate
 * terminateGame               - Ends the game
 * isLegalMove                 - Checks if a move ((x,y) -> (v,w)) is legal - both valid and not against chess rules (like
   avoding a check and so on).
 * getFigureStringName         - Returns the string name of a figure
 */


/* A simple explanation of the words we use here and in other parts of the code:
 * a VALID move is a move that is OK from figure movment perspective (i.e. rooks move in a straight line, cannot go through figures and have to land on an empty field of an oponnent figure.
 * on the other hand, a LEGAL move is a move that is both VALID and legal (i.e. does not create a check for the moving player
 */

/**
 * Creates a new chess game with the following params: historySize, mode (1 or 2 players)
 * humanColor, difficulty. The last two are always defined by not used in 2 player mode.
 * CurrentPlayer defaults to WHITES. 
 * The also draws the initial board and sets it
 *
 * @return a chess game
 */
chessGame* createChessGame(int historySize, GAME_MODE_PLAYER mode, PLAYER_COLOR humanColor, int difficulty); //D

/**
 * Copies a chess game
 *
 * @return a chess game
 */
chessGame* copyChessGame(chessGame* src); //D Not Tested


/**
 * Frees the memory used by the chess game
 *
 * returns nothing
 */
void destroyChessGame(chessGame* src); // D Not Tested

/**
 * Sets move <x,y> -> <v,w>
 * Checks if it is a legal move, updates the board.
 *
 * @param needToCheckMoveValidiy a special boolen used to simplfy tasks - in some cases we know that a certian rule is valid (as it was
 * already check somewhere along the stack tree), and hence we can skip those checks (and improve the running time)
 *
 * @return message representing the result of the command (sucess, invalid move etc)
 */
CHESS_GAME_MESSAGE setChessMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col, bool needToCheckMoveValidiy, bool isValidForCrowning); // D Not Tested

/**
 * Checks if move <x,y> -> <v,w> is valid, from the perspective of how the figures move (accoring to chess rules)
 *
 * @return true if yes, no otherwise
 */
bool isValidMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col); // D


/**
 * Undoes the previous move.
 *
 * @return message representing the result of the command (sucess, invalid move etc)
 */
CHESS_GAME_MESSAGE undoChessPrevMove(chessGame* src, bool shouldPrint); //NT

/**
 * Checks if the figure located at <x,y> has any legal moves
 *
 * @return true/false
 */
bool hasValidMove(chessGame* src, int row, int col); // D kinda tested

/**
 * Prints the board as specified in the guidelines
 *
 * @returns nothing
 */
CHESS_GAME_MESSAGE chessConsolePrintBoard(chessGame* src); // D tested

/**
 * Checks if there's a check. 
 * i.e. finds the king of the current player, and checks if it is threated by any opponent figure.
 *
 * @return true/false
 */
bool isCheck(chessGame* src); // D tested

/**
 * Findes all legal moves for figure located at <x,y>.
 *
 * @return a two demensional array representing all moved
 */
SPArrayList* allPossibleMoves(chessGame* src, int row, int col); //D Not Tested

/**
 * Checks if there's a checkmate.
 * i.e. finds the king of the current player, and checks if it is threated by any opponent figure and has no legal moves
 *
 * @return true/false
 */
bool isCheckmate(chessGame* src); // D Not Tested

/**
 * Checks for a tie situation in chess
 * i.e. finds all the figures of the current player, and verifies that they have no legal moves.
 * but the king it NOT is threated by any opponent figure
 *
 * @return true/false
 */
bool isStalemate(chessGame* src); // D Not Tested

/**
 * Saves the game to a file specified in the filename
 *
 * @return success/failure
 */
bool saveGame(chessGame* src, const char* filename);


/**
* Rotates the saved slotes
* i.e, if all 5 slots are full, saves src to slot_1, while copying what was in slot_1 to slot_2 etc
* The game in slot_5 will be overwriten.
*
* returns nothing
*/
void saveGameInLastestSlot(chessGame* src);


/**
* Loads a new game to src (same place in memory)
*
* returns nothing
*/
void loadGameInPlace(const char* filename, chessGame* src);


/**
 * Prints all possible moves by figure at <x,y>, in the requested format.
 *
 * returns nothing
 */
void get_moves(chessGame* src, int row, int col);

/**
 * Returns a string with the name of the current player.
 *
 * @return "white" if WHITES and "black" otherwise
 */
char* getCurrentPlayerStringName(chessGame* src);

/**
 * Checks if there's a check/checkmate/tie. 
 * If yes, prints and/or terminates the game
 *
 * returns nothing
 */
void checkGameEnd(chessGame* src);

/**
 * terminates the game, freeing all memory resources.
 *
 * returns nothing
 */
void terminateGame(chessGame* src);

/**
 * Checks if a given (x,y) -> (v,w) is legal (incl all chess rules):
 * If all 4 ints are between 0 and 7
 * If (v,w) represents a valid destenation for the figure in (x,y)
 * If the figure in (x,y) can do this move (is it valid)
 * If no other rules are broken (e.g. no check created for the moving player
 *
 *
 * returns nothing
 */
bool isLegalMove(chessGame* src, int prev_pos_row, int prev_pos_col, int next_pos_row, int next_pos_col);


void crowning(chessGame* src,int row,int col); //todo


/**
 * Loads a chess game from an XML file at filename
 *
 *
 * returns chess game
 */
chessGame* loadGame(const char* filename);


/**
 * Given the char representation of a figure, returns the string name
 *
 *
 * returns string figure name
 */
char* getFigureStringName(char figure);

#endif /* Chess_gameUtils_h */
