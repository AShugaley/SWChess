#include "Chess_gameParser.h"


bool spParserIsInt(const char* str)
{
	unsigned int i = 0;
	if ((str[0] == '-') || ((str[0]<58) && (str[0]>47)))  /* first char is minus or digit  */
	{
		for (i = 1; i < strlen(str); i++)
		{
			if ((str[i] > 57) || (str[i] < 48))  /* not a digit  */
				return false;
		}
		return true;
	}
	return false;
}


bool spParserIsLetter(const char* str)
{
	if ((str[0] >= 65) && (str[0] <= 90))
		return true;
	return false;
}


bool spParserIsValidOrederedPair(const char* currentToken, char* delimiter, CHESSCommand* command, CHESS_MOVE_ARG argPlace)//change to empty delimiter (chech chars and not words!!!!)
{
	char chToken;
	char currentstr[2] = { '\0' };
	if ((currentToken[0] != '<'))  /* currentToken[0] should be "<" */
		return false;

	/* should be an int */


	chToken = currentToken[1];

	currentstr[0] = currentToken[1];
	if (spParserIsInt(currentstr))
	{
		if (argPlace == CHESS_SOURCE_MOVE)
		{
			command->sourceRow = chToken - '0';
		}
		else if (argPlace == CHESS_TARGET_MOVE)
		{
            command->targertRow =chToken - '0';
		}
	}
	else
		return false;

	chToken = currentToken[2];
	/* should be "," */
	if (chToken != ',')
		return false;


	/*should be an uppercase letter  */
	chToken = currentToken[3];
	currentstr[0] = currentToken[3];
	if (spParserIsLetter(currentstr))
	{
		if (argPlace == CHESS_SOURCE_MOVE)
		{
			command->sourceColl = chToken; 
		}
		else if (argPlace == CHESS_TARGET_MOVE)
		{
			command->targetColl = chToken;
		}
	}
	else
		return false;
	chToken = currentToken[4]; /* should be ">" */
	if (chToken != '>')
		return false;

	return true;
}

CHESSCommand spParserLine(const char* str)
{
	CHESSCommand command;
	command.isValidFirstPair = false;	/* true only in case of "move" with valid numbers */
	command.isValidSecondPair = false;
	char currentStr[SP_MAX_LINE_LENGTH] = "\0";
	strcpy(currentStr, str);
	char* currentToken;
	char delimiter[] = " \t\r\n";
	

	currentToken = strtok(currentStr, delimiter);	/* curtoken is the first part of the string */
    if(!currentToken){
        command.cmd = CHESS_INVALID_LINE;
        return command;
    }
	if (currentToken == '\0')	/* doesn't suppose to get here, just in case ... */
	{
		command.cmd = CHESS_INVALID_LINE;
		return command;
	}

	if (!strcmp(currentToken, "undo"))	/* curtoken == undo (strcmp = 0 in this case) */
	{
		command.cmd = CHESS_UNDO_MOVE;
	}

	else if (!strcmp(currentToken, "quit"))
	{
		command.cmd = CHESS_QUIT;
	}

	else if (!strcmp(currentToken, "reset"))
	{
		command.cmd = CHESS_RESTART;
	}

	else if (!strcmp(currentToken, "save"))	/* will check the file path later in the gameUtils functions */
	{
		command.cmd = CHESS_SAVE;
	}

	else if (!strcmp(currentToken, "move"))
	{
        
		command.cmd = CHESS_MOVE;
		currentToken = strtok(NULL, delimiter);
        if(!currentToken){
            command.cmd = CHESS_INVALID_LINE;
            return command;
        }


		command.isValidFirstPair = spParserIsValidOrederedPair(currentToken, delimiter,&command, CHESS_SOURCE_MOVE);
		currentToken = strtok(NULL, delimiter);
        if(!currentToken){
            command.cmd = CHESS_INVALID_LINE;
            return command;
        }

		if (!strcmp(currentToken, "to"))
		{
			currentToken = strtok(NULL, delimiter);
			command.isValidSecondPair = spParserIsValidOrederedPair(currentToken, delimiter, &command, CHESS_TARGET_MOVE);
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
    


	/* if there is additional text after the first& second parts  - invalid  */
	currentToken = strtok(NULL, delimiter);
	if ((currentToken != NULL) && (command.cmd != CHESS_SAVE))
	{
		command.cmd = CHESS_INVALID_LINE;
		command.isValidFirstPair = false;
		command.isValidSecondPair = false;
	}
    
	return command;
}
