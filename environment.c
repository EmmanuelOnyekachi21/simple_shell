#include "shell.h"

/**
 * CompareEnvName - Compares environment variable names to the provided name.
 * @EnvName: Name of the environment variable.
 * @name: Name to compare.
 *
 * Return:  Returns 0 if they don't match, or another value if they do.
 */
int CompareEnvName(const char *EnvName, const char *name)
{
	int i = 0;

	while (EnvName[i] != '=')
	{
		if (EnvName[i] != name[i])
		{
			return (0);
		}
		i++;
	}
	return (i + 1);
}

/**
 * GETENV - Retrieve an environment variable's value.
 * @name: The name of the environment variable.
 *
 * Return: value of the environment variable if is found.
 */
char *GETENV(const char *name)
{
	char *PtrEnv;

	int i, mv;

	PtrEnv = NULL;
	mv = 0;
	for (i = 0; environ[i]; i++)
	{
		mv = CompareEnvName(environ[i], name);
		if (mv)
		{
			PtrEnv = environ[i];
			break;
		}
	}
	return (PtrEnv + mv);
}

/**
 * _env - prints the evironment variables
 *
 * Return: 1 on success.
 */
int _env(void)
{
	int i, j;

	if (environ == NULL)
		return (1);
	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j]; j++)
			;
		write(STDOUT_FILENO, environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
