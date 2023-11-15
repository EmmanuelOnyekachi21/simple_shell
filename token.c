#include "shell.h"

/**
 * copyString -  copies the source string to the destination string
 * @destination: string that would be copied to
 * @source: string to be copied
 *
 * Return: a pointer to the destination string
 */
char *copyString(char *destination, char *source)
{
	char *pointer = destination;

	while (1)
	{
		*pointer = *source;
		if (!*source)
		{
			break;
		}
		source++;
		pointer++;
	}
	return (destination);
}

/**
 * countTokens - returns the number of token to be extracted
 * @input: string to extract token from
 *
 * Return: number of tokens to be extracted
 */
unsigned int countTokens(char *input)
{
	unsigned int numberOfTokens = 0, prev = 1;
	char *pointer = input;

	while (1)
	{
		if (*pointer == ' ')
		{
			if (prev != 1)
				numberOfTokens++;
			prev = 1;
		}
		else if (*pointer == '\0' || *pointer == '\n')
		{
			if (prev != 1)
				numberOfTokens++;
			break;
		}
		else
			prev = 0;
		pointer++;
	}
	return (numberOfTokens);
}

/**
 * tokenizeString - splits a string into tokens using ' ' as delimiter
 * @input: string to be splitted into tokens
 *
 * Return: returns a null terminated array of extracted tokens or NULL;
 */
char **tokenizeString(char *input)
{
	char **tokens;
	char *pointer = input, buffer[1024];
	unsigned int numberOfTokens, currentIndex, tokenLength, count;

	numberOfTokens = countTokens(input);
	if (numberOfTokens == 0)
		return (NULL);
	tokens = (char **) malloc((numberOfTokens + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	for (currentIndex = 0; currentIndex < numberOfTokens; currentIndex++)
	{
		count = 0;
		while (1)
		{
			if (*pointer != ' ' && *pointer != '\0' && *pointer != '\n')
			{
				buffer[count] = *pointer;
				pointer++;
				count++;
			}
			else if (count == 0)
				pointer++; /*incase it starts with a space*/
			else
				break;
		}
		buffer[count] = '\0';
		tokenLength = count + 1;
		tokens[currentIndex] = (char *) malloc(tokenLength * sizeof(char));
		if (tokens[currentIndex] == NULL)
		{
			freeTokenArray(tokens);
			return (NULL);
		}
		copyString(tokens[currentIndex], buffer);
		pointer++;
	}
	tokens[numberOfTokens] = NULL;
	return (tokens);
}

/**
 * freeTokenArray - releases the memory allocated for creating the argv[]
 * @tokens: argument vector to be freed
 */
void freeTokenArray(char **tokens)
{
	unsigned int currentIndex = 0;

	while (tokens[currentIndex] != NULL)
	{
		free(tokens[currentIndex]);
		currentIndex++;
	}
	free(tokens);
}
