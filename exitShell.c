#include "shell.h"

/**
 * exitShell - Neatly exits the shell.
 * @exitArgument: The argument pased to the exit call
 * Return: 0 on success, 1 on error
 */
int exitShell(char *exitArgument)
{
	unsigned int shellStatus = 0;
	int currentIndex;

	for (currentIndex = 0; exitArgument[currentIndex] != '\0'; currentIndex++)
	{
		if (exitArgument[currentIndex] < '0' || exitArgument[currentIndex] > '9')
			return (-1);

		if (shellStatus > (UINT_MAX - (exitArgument[currentIndex] - '0')) / 10)
			return (-1);

		shellStatus = shellStatus * 10 + (exitArgument[currentIndex] - '0');
	}
	shellStatus = shellStatus % 256;
	return (shellStatus);
}
