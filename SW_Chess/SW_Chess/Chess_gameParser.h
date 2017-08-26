#ifndef CHESS_GAMEPARSER_H_
#define CHESS_GAMEPARSER_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//specify the maximum line length
#define SP_MAX_LINE_LENGTH 1024

//a type used to represent a command
typedef enum {
	CHESS_INVALID_LINE,
	CHESS_UNDO_MOVE,
	CHESS_QUIT,
	CHESS_RESTART,
	CHESS_SAVE,
	CHESS_MOVE,
} CHESS_COMMAND;


typedef enum {
	CHESS_SOURCE_MOVE,
	CHESS_TARGET_MOVE,
} CHESS_MOVE_ARG;

typedef struct move_argument {
	int sourceRow;  char sourceColl;
	int targertRow; char targetColl;
} MOVEArg;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	CHESS_COMMAND cmd;
	bool isValidFirstPair; //is set to true if the line contains a valid argument
	bool isValidSecondPair;
	MOVEArg* arg;
} CHESSCommand;





/**
* Checks if a specified string represents a valid integer. It is recommended
* to use this function prior to calling the standard library function atoi.
*
* @return
* true if the string represents a valid integer, and false otherwise.
*/
bool spParserSettingIsInt(const char* str);


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
bool spParserIsValidOrederedPair(const char* str, char* delimiter, MOVEArg* argstruct, CHESS_MOVE_ARG argPlace);


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