#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "input_validation.h"

char* getInput(void)
{
	// Create string to hold input and ensure that malloc() does not fail
	char *input = malloc(sizeof(char) * MAX_INPUT_LENGTH);
	if(input == NULL)
	{
		return NULL;
	}

	fgets(input,MAX_INPUT_LENGTH,stdin);

	// Use a copy of string so validation can use strtok() since strtok() inserts null terminators into strings
	char* tempString = malloc(sizeof(char) * MAX_INPUT_LENGTH);
	if(tempString == NULL)
	{
		free(input);
		return NULL;	
	}
	strcpy(tempString, input);

	// Ensure input was valid, if not, change first token to I to signal invalid input
	if(isValidInput(tempString) != 1)
	{
		printf("Invalid Instruction: Please enter a valid command\n");
		*input = 'I';
	}

	free(tempString);
	return input;
}

int isValidInput(char* input)
{
	char *delim = " \n";

	char *token = strtok(input,delim);
	if(token != NULL)
	{
		if(strcmp(token,"X") == 0)
		{
			// If first token is "X", make sure there are no additional tokens
			if(strtok(NULL,delim) == NULL)
			{
				return 1;
			}	
		}
		else if(strcmp(token,"P") == 0)
		{
			// If first token is "P", make sure there is exactly one additional token
			if(strtok(NULL,delim) != NULL)
			{
				if(strtok(NULL,delim) == NULL)
				{
					return 1;
				}
			}
		}
		else if(strcmp(token,"F") == 0)
		{
			// If first token is "F", make sure there are exactly two additional token
			if(strtok(NULL,delim) != NULL)
			{
				if(strtok(NULL,delim) != NULL)
				{
					if(strtok(NULL,delim) == NULL)
					{
						return 1;
					}
				}
			}
		}
		else if(strcmp(token,"U") == 0)
		{
			// If first token is "U", make sure there are exactly two additional token
			if(strtok(NULL,delim) != NULL)
			{
				if(strtok(NULL,delim) != NULL)
				{
					if(strtok(NULL,delim) == NULL)
					{
						return 1;
					}
				}
			}		
		}
		else if(strcmp(token,"L") == 0)
		{
			// If first token is "L", make sure there is exactly one additional token
			if(strtok(NULL,delim) != NULL)
			{
				if(strtok(NULL,delim) == NULL)
				{
					return 1;
				}
			}
		}
		else if(strcmp(token,"Q") == 0)
		{
			// If first token is "Q", make sure there are exactly two additional token
			if(strtok(NULL,delim) != NULL)
			{
				if(strtok(NULL,delim) != NULL)
				{
					if(strtok(NULL,delim) == NULL)
					{
						return 1;
					}
				}
			}
		}
	}
	// If first token is not a valid command or is not followed by the correct argurment(s), return 0 for false
	return 0;
}