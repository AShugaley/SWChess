#include "Chess_gameSettingsParser.h"

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

CHESSSettingCommand spParserSettingLine(const char* str)
{
	CHESSSettingCommand command;
	command.isValidArg = false;
	char currentStr[SP_MAX_LINE_LENGTH] = "\0";
	strcpy(currentStr, str);
	char* currentSetToken;
	char delimiter[] = " \t\r\n";

	currentSetToken = strtok(currentStr, delimiter);	//curtoken is the first part of the string 
	if (currentSetToken == '\0')	//doesn't suppose to get here, just in case ...
	{
		command.cmd = CHESS_INVALID_SETTING_LINE;
		return command;
	}

	else if (!strcmp(currentSetToken, "game_mode"))	//curtoken == game_mode (strcmp = 0 in this case) 
	{
		command.cmd = CHESS_MODE;
		currentSetToken = strtok(NULL, delimiter);
		if (currentSetToken != NULL)
		{
			if (spParserSettingIsInt(currentSetToken))
			{
				command.arg = atoi(currentSetToken);
				command.isValidArg = true;
			}
		}
	}

	else if (!strcmp(currentSetToken, "difficulty"))
	{
		command.cmd = CHESS_DIFFICULTY;
		currentSetToken = strtok(NULL, delimiter);
		if (currentSetToken != NULL)
		{
			if (spParserSettingIsInt(currentSetToken))
			{
				command.arg = atoi(currentSetToken);
				command.isValidArg = true;
			}
		}
	}

	else if (!strcmp(currentSetToken, "user_color"))
	{
		command.cmd = CHESS_COLOR;
		currentSetToken = strtok(NULL, delimiter);
		if (currentSetToken != NULL)
		{
			if (spParserSettingIsInt(currentSetToken))
			{
				command.arg = atoi(currentSetToken);
				command.isValidArg = true;
			}
		}
	}

	else if (!strcmp(currentSetToken, "load"))	//will check the file path later in the gameUtils functions 
	{
		command.cmd = CHESS_LOAD;
	}

	else if (!strcmp(currentSetToken, "default"))
	{
		command.cmd = CHESS_DEFAULT;
	}

	else if (!strcmp(currentSetToken, "print_setting"))
	{
		command.cmd = CHESS_PRINT_SETTINGS;
	}

	else if (!strcmp(currentSetToken, "quit"))
	{
		command.cmd = CHESS_SETTING_QUIT;
	}

	else if (!strcmp(currentSetToken, "start"))
	{
		command.cmd = CHESS_START;
	}

	else
	{
		command.cmd = CHESS_INVALID_SETTING_LINE;
	}

	//if there is additional text after the first& second parts  - invalid 
	currentSetToken = strtok(NULL, delimiter);
	if (currentSetToken != NULL)
	{
		command.cmd = CHESS_INVALID_SETTING_LINE;
		command.isValidArg = false;
	}

	return command;
}