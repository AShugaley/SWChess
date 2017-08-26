#include "Chess_gameParser.h"


bool spParserSettingIsInt(const char* str)
{
	unsigned int i = 0;
	if (str[0] == '-' || (str[0]<58 && str[0]>47))  //first char is minus or digit 
	{
		for (i = 1; i < strlen(str); i++)
		{
			if (str[i] > 57 || str[i] < 48)  // not a digit 
				return false;
		}
		return true;
	}
	return false;
}


bool spParserIsLetter(const char* str)
{
	if (str[0] >= 65 && str[0] <= 90)
		return true;
	return false;
}


bool spParserIsValidOrederedPair(const char* currentToken, char* delimiter, MOVEArg* argstruct, CHESS_MOVE_ARG argPlace)//change to empty delimiter (chech chars and not words!!!!) 
{
	currentToken = strtok(NULL, delimiter); //should be "<"
	if (currentToken != "<")
		return false;

	currentToken = strtok(NULL, delimiter); //should be an int
	if (spParserSettingIsInt(currentToken))
	{
		if (argPlace == CHESS_SOURCE_MOVE)
		{

			argstruct->sourceRow = atoi(currentToken);
		}
		else if (argPlace == CHESS_TARGET_MOVE)
		{
			argstruct->targertRow = atoi(currentToken);
		}
	}
	else
		return false;

	currentToken = strtok(NULL, delimiter); //should be ","
	if (currentToken != ",")
		return false;


	currentToken = strtok(NULL, delimiter); //should be an uppercase letter 
	if (spParserIsLetter(currentToken))
	{
		if (argPlace == CHESS_SOURCE_MOVE)
		{
			argstruct->sourceColl = *currentToken; ///check this!!
		}
		else if (argPlace == CHESS_TARGET_MOVE)
		{
			argstruct->targetColl = *currentToken;
		}
	}
	else
		return false;


	currentToken = strtok(NULL, delimiter); //should be ">"
	if (currentToken != ">")
		return false;

	return true;
}

CHESSCommand spParserLine(const char* str)
{
	CHESSCommand command;
	command.isValidFirstPair = false;	//true only in case of "move" with valid numbers 
	command.isValidSecondPair = false;
	char currentStr[SP_MAX_LINE_LENGTH] = "\0";
	strcpy(currentStr, str);
	char* currentToken;
	char delimiter[] = " \t\r\n";
	MOVEArg argstruct;

	currentToken = strtok(currentStr, delimiter);	//curtoken is the first part of the string 
	if (currentToken == '\0')	//doesn't suppose to get here, just in case ...
	{
		command.cmd = CHESS_INVALID_LINE;
		return command;
	}

	if (!strcmp(currentToken, "undo"))	//curtoken == undo (strcmp = 0 in this case) 
	{
		command.cmd = CHESS_UNDO_MOVE;
	}

	if (!strcmp(currentToken, "quit"))
	{
		command.cmd = CHESS_QUIT;
	}

	if (!strcmp(currentToken, "reset"))
	{
		command.cmd = CHESS_RESTART;
	}

	if (!strcmp(currentToken, "save"))	//will check the file path later in the gameUtils functions 
	{
		command.cmd = CHESS_SAVE;
	}

	if (!strcmp(currentToken, "move"))
	{
		command.cmd = CHESS_MOVE;
		command.isValidFirstPair = spParserIsValidOrederedPair(currentToken, "", &argstruct, CHESS_SOURCE_MOVE);
		currentToken = strtok(NULL, delimiter);
		if (!strcmp(currentToken, "to"))
		{
			command.isValidSecondPair = spParserIsValidOrederedPair(currentToken, delimiter, &argstruct, CHESS_TARGET_MOVE);
		}
		else
		{
			command.cmd = CHESS_INVALID_LINE;
			command.isValidFirstPair = false;
			command.isValidSecondPair = false;
		}
	}

	else
	{
		command.cmd = CHESS_INVALID_LINE;
	}


	//if there is additional text after the first& second parts  - invalid 
	currentToken = strtok(NULL, delimiter);
	if (currentToken != NULL)
	{
		command.cmd = CHESS_INVALID_LINE;
		command.isValidFirstPair = false;
		command.isValidSecondPair = false;
	}

	return command;
}
