#ifndef CHESS_GAMEPARSER_H_
#define CHESS_GAMEPARSER_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Chess_gameParser summary:
 *
 * A container that includes a set of structures and functions that used
 * to read and parse human commands in console mode during the game stage.
 *
 * spParserIsInt                 - Checks if a string is an int.
 * spParserIsLetter              - Creates if a string is a letter.
 * spParserIsValidOrederedPair   - Checks if a <x,y> move input is in valid format - x is an in
 * and y is a letter.
 * spParserLine                  - Given a string checks if it is a valid command, and if yes
 * parses it for further use.
 */


/* sepcifies the maximum input length */
#define SP_MAX_LINE_LENGTH 1024

/* Enum representing the possible human commands in the game stage */
typedef enum {
	CHESS_INVALID_LINE,
	CHESS_UNDO_MOVE,
	CHESS_QUIT,
	CHESS_RESTART,
	CHESS_SAVE,
	CHESS_MOVE,
} CHESS_COMMAND;


/* Enum, that represents if a given <x,y> set is a source or target move (<x,y> -> <v,w>) */

typedef enum {
	CHESS_SOURCE_MOVE,
	CHESS_TARGET_MOVE,
} CHESS_MOVE_ARG;



/* Struct that represents a various human commands in the game stage
 * @param - command type
 * @isValidFirstPair,isValidSecondPair - is the first/sedond <x,y> in valid 
 * format - a number followed by a letter (used in move commands)
 * @param sourceRow,sourceColl,targertRow,targetColl - <x,y> -> <v,w>, repsectively
 * @param path - a string representing the file path in save/load commands
 */
typedef struct command_t {
	CHESS_COMMAND cmd;
	bool isValidFirstPair; //is set to true if the line contains a valid argument
	bool isValidSecondPair;
	int sourceRow;  char sourceColl;
	int targertRow; char targetColl;
    char* path[SP_MAX_LINE_LENGTH];
} CHESSCommand;





/**
* Checks if a specified string represents a valid integer. It is recommended
* to use this function prior to calling the standard library function atoi.
*
* @return
* true if the string represents a valid integer, and false otherwise.
*/
bool spParserIsInt(const char* str);


/**
* Checks if a specified string represents a valid uppercase letter.
*
* @return
* true if the string represents a valid uppercase letter, and false otherwise.
*/
bool spParserIsLetter(const char* str);


/**
* Checking the move section- if the user pressed "<int,upper case letter>"
* return false
*
* @return
* true if the string represents a valid ordered pair, and false otherwise.
*/
bool spParserIsValidOrederedPair(const char* str, char* delimiter, CHESSCommand* command, CHESS_MOVE_ARG argPlace);


/**
* Parses a specified line. If the line is a command which has an
* argument then the argument is parsed and is saved in the field arg and the
* validation fields are set to true. In any other case then
*'isValidFirstPair' & 'isValidSecondPair' are set to
* false and the value 'arg' is undefined
*
* @return
* A parsed line such that:
*   cmd					- contains the command type, if the line is invalid then this field is
*						  set to INVALID_LINE
*	isValidFirstPair	- is set to true if the command is move and the argument is valid
*	isValidSecondPair	- is set to true if the command is move and the argument is valid
*   arg				    - the argument in case isValidFirstPair & isValidSecondPair are set to true
*/
CHESSCommand spParserLine(const char* str);

#endif
