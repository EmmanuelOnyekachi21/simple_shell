#include "shell.h"

/**
 * updateErrno - updates the errno and returns NULL
 *
 * Return: returns NULL to the calling process
 */
char *updateErrno(void)
{
	errno = ENOENT;
	return (NULL);
}

/**
 *customStrncmp - compares the value of two strings up to 'n' characters.
 *@str1: main string in the comparison
 *@str2: string that is compared to the main string
 *@n: number of bytes to compare
 *
 *Return: 0 if equal, a positive value if str1 is greater than
 * str2 and negative otherwise
 */
int customStrncmp(char *str1, char *str2, int n)
{
	int comparisonResult = 0, index;
	char *ptr1 = str1;
	char *ptr2 = str2;

	for (index = 0; index < n; index++)
	{
		if (*ptr1 == *ptr2)
		{
			ptr1++;
			ptr2++;
			continue;
		}
		else
		{
			comparisonResult = *ptr1 - *ptr2;
			break;
		}
	}
	return (comparisonResult);
}

/**
 * concat_str - concatenates two strings.
 * @string1: first string.
 * @string2: second string.
 *
 * Return: pointer to the concatenated string.
 */
char *concat_str(char *string1, char *string2)
{
	int length = 0;
	int index = 0;
	char *concat;
	char *ptr1 = string1;
	char *ptr2 = string2;

	while (ptr1 && *ptr1)
	{
		length++;
		ptr1++;
	}
	while (ptr2 && *ptr2)
	{
		length++;
		ptr2++;
	}
	concat = malloc(length + 1);
	ptr1 = string1;
	ptr2 = string2;
	while (concat != NULL)
	{
		if (ptr1 && *ptr1)
		{
			concat[index] = *ptr1;
			ptr1++;
		}
		else if (ptr2 && *ptr2)
		{
			concat[index] = *ptr2;
			ptr2++;
		}
		else
		{
			concat[index] = '\0';
			break;
		}
		index++;
	}
	return (concat);
}

/**
 * findAbsolutePath - returns the valid  path for a given filename if present in PATH
 * @filename: Name to be checked if present in PATH folders
 *
 * Return: Returns the absolute path where the filename is found, validPath.
 */
char *findAbsolutePath(char *filename)
{
	char *pathEnv = NULL, buffer[TOK_BUFSIZE], *validPath = NULL, *token = "PATH=";
	unsigned int index = 5, x, count;
	struct stat fileStat;

	for (count = 0; (environ && environ[index] != NULL); count++)
	{
		if ((customStrncmp(environ[count], token, 5) == 0))
		{
			pathEnv = environ[count];
			break;
		}
	}
	if (pathEnv == NULL)
		return (updateErrno());
	while (pathEnv[index] != '\0')
	{
		x = 0;
		while (1)
		{
			if (pathEnv[index] == ':' || pathEnv[index] == '\0')
			{
				buffer[x] = '/';
				buffer[x + 1] = '\0';
				if (pathEnv[index] == ':')
					index++;
				break;
			}
			buffer[x] = pathEnv[index];
			index++;
			x++;
		}
		validPath = concat_str(buffer, filename);
		if ((stat(validPath, &fileStat)) == 0)
			break;
		free(validPath);
		validPath = NULL;
	}
	if (validPath == NULL)
		errno = ENOENT;
	return (validPath);
}
