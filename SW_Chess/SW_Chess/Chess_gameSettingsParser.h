#ifndef CHESS_GAMESETTINGSPARSER_H_
#define CHESS_GAMESETTINGSPARSER_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//default 
//print_setting
//quit
//start

//specify the maximum line length
#define SP_MAX_LINE_LENGTH 1024

//a type used to represent a command
typedef enum {
	CHESS_INVALID_SETTING_LINE,
	CHESS_MODE,
	CHESS_DIFFICULTY,
	CHESS_COLOR,
	CHESS_LOAD,
	CHESS_DEFAULT,
	CHESS_PRINT_SETTINGS,
	CHESS_SETTING_QUIT,
	CHESS_START,
} CHESS_SETTING;


// a new type that is used to encapsulate a parsed line
typedef struct commandSet_t {
	CHESS_SETTING cmd;
	bool isValidArg; //is set to true if the command needs a number and the user entered a valid number
	int arg;
} CHESSSettingCommand;


/**
* Checks if a specified string represents a valid integer. It is recommended
* to use this function prior to calling the standard library function atoi.
*
* @return
* true if the string represents a valid integer, and false otherwise.
*/
bool spParserSettingIsInt(const char* str);


/**
* Parses a specified line. If the line is a command which has an
* argument then the argument is parsed and is saved in the field arg and the
* validation field is set to true. In any other case then
*'isValidArg' field is set to
* false and the value 'arg' is undefined
*
* @return
* A parsed line such that:
*   cmd			- contains the command type, if the line is invalid then this field is
*				  set to INVALID_LINE
*   isValidArg  - is set to true if the command is one that has to contain argument
*				  and the argument is valid
*   arg			- the argument in case isValidArg is set to true
*/
CHESSSettingCommand spParserSettingLine(const char* str);

#endif