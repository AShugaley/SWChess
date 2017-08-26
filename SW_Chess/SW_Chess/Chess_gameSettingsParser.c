#include "Chess_gameSettingsParser.h"

bool spParserIsInt(const char* str)
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

CHESSSettingCommand spParserPraseLine(const char* str)
{
	CHESSSettingCommand command;
	command.isValidArg = false;	
	char currentStr[SP_MAX_LINE_LENGTH] = "\0";
	strcpy(currentStr, str);
	char* currentToken;
	char delimiter[] = " \t\r\n";
	int arg;

	currentToken = strtok(currentStr, delimiter);	//curtoken is the first part of the string 
	if (currentToken == '\0')	//doesn't suppose to get here, just in case ...
	{
		command.cmd = CHESS_INVALID_LINE;
		return command;
	}

	if (!strcmp(currentToken, "game_mode"))	//curtoken == game_mode (strcmp = 0 in this case) 
	{
		command.cmd = CHESS_MODE;
		currentToken = strtok(NULL, delimiter);
		if (currentToken != NULL)
		{
			if (spParserIsInt(currentToken))
			{
				command.arg = atoi(currentToken);
				command.isValidArg = true;
			}
		}
	}
	
	if (!strcmp(currentToken, "difficulty"))	
	{
		command.cmd = CHESS_DIFFICULTY;
		currentToken = strtok(NULL, delimiter);
		if (currentToken != NULL)
		{
			if (spParserIsInt(currentToken))
			{
				command.arg = atoi(currentToken);
				command.isValidArg = true;
			}
		}
	}

	if (!strcmp(currentToken, "user_color"))
	{
		command.cmd = CHESS_COLOR;
		currentToken = strtok(NULL, delimiter);
		if (currentToken != NULL)
		{
			if (spParserIsInt(currentToken))
			{
				command.arg = atoi(currentToken);
				command.isValidArg = true;
			}
		}
	}

	if (!strcmp(currentToken, "load"))	//will check the file path later in the gameUtils functions 
	{
		command.cmd = CHESS_LOAD;
	}

	if (!strcmp(currentToken, "default"))	
	{
		command.cmd = CHESS_DEFAULT;
	}

	if (!strcmp(currentToken, "print_setting"))	
	{
		command.cmd = CHESS_PRINT_SETTINGS;
	}

	if (!strcmp(currentToken, "quit"))
	{
		command.cmd = CHESS_QUIT;
	}

	if (!strcmp(currentToken, "start"))
	{
		command.cmd = CHESS_START;
	}
}