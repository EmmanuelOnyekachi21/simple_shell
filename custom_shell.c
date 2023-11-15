#include "shell.h"

/**
 * printPrompt - Prints the shell prompt
 * @isInteractive: Indicative if the shell is in interactive mode.
 */
void printPrompt(int isInteractive)
{
	if (isInteractive)
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * runCommand - executes a given program from the argument vector
 * @shellName: name which the shell program was called
 * @arguments: argument vector for the argument to be excuted
 * @programCount: the current count of the programs sthe shell has executed
 * @status: statusus returned from child process
 *
 * Return: 0 if no errors otherwise -1
 */
int runCommand(char *shellName, char **arguments, int programCount, int *status)
{
	pid_t processID;
	int waitStatus;

	processID = fork();
	if (processID == -1)
	{
		printErrorMessage(shellName, arguments[0], programCount);
		return (-1);
	}
	else if (processID == 0)
	{
		if ((execve(arguments[0], arguments, environ)) < 0)
		{
			printErrorMessage(shellName, arguments[0], programCount);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&waitStatus);
		if (!WIFEXITED(waitStatus))
			return (-1);
		*status = WEXITSTATUS(waitStatus);
	}
	return (0);
}


/**
 * handleSpecialCase - Handles cases when command is not 
 * a relative or absolute path.
 * @shellName: name the shell was called for error printing
 * @arguments: argument vector
 * @programCount: pointer to the counter for programs executed by the shell
 * @status: statusus to exit if necessary
 *
 * Return: 0 if program should continue normally, 1 if loop should be restarted
 * and 2 if loop should be broken.
 */
int handleSpecialCase(char *shellName, char **arguments, int programCount, int *status)
{
	char *programPath;
	int exitStatus;

	if (customStrncmp(arguments[0], "exit", 5) == 0)
	{
		if (arguments[1] != NULL)
		{
			exitStatus = exitShell(arguments[1]);
			if (exitStatus == -1)
			{
				printExitErrorMessage(shellName, arguments[0], programCount, arguments[1]);
				*status = 2;
				return (1);
			}
			*status = exitStatus;
		}
		return (2);
	}
	else if (customStrncmp(arguments[0], "env", 4) == 0)
	{
		_env();
		return (1);
	}
	programPath = findAbsolutePath(arguments[0]);
	if (programPath == NULL)
	{
		printErrorMessage(shellName, arguments[0], programCount);
		return (1);
	}
	else
	{
		free(arguments[0]);
		arguments[0] = programPath;
	}
	return (0);
}

/**
 * main - Runs the shell program.
 * @argumentCount: argument count
 * @argumentVector: argument vector
 *
 * Return: 0 if executes with no error, otherwise 1
 */
int main(int argumentCount, char **argumentVector)
{
	char **arguments, *shellName = argumentVector[0], *inputBuffer = (char *) malloc(BUFSIZE);
	int programCount = 0, feedback, isInteractive = 1, exitStatus = 0;
	size_t bufferSize = BUFSIZE;

	if (argumentCount > 1 || inputBuffer == NULL)
	{
		printErrorMessage(shellName, argumentVector[1], programCount);
		exit(EXIT_FAILURE);
	}
	if (!isatty(STDIN_FILENO))
		isInteractive = 0;
	else
		write(STDOUT_FILENO, "$ ", 2);
	while ((getLine(&inputBuffer, &bufferSize, stdin)) != -1)
	{
		arguments = tokenizeString(inputBuffer);
		if (arguments == NULL)
			continue;
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
		{
			feedback = handleSpecialCase(shellName, arguments, ++programCount, &exitStatus);
			if (feedback == 2)
			{
				freeTokenArray(arguments);
				break;
			}
			else if (feedback == 1)
			{
				freeTokenArray(arguments);
				printPrompt(isInteractive);
				continue;
			}
			programCount--;
		}
		runCommand(shellName, arguments, ++programCount, &exitStatus);
		freeTokenArray(arguments);
		printPrompt(isInteractive);
	}
	free(inputBuffer);
	exit(exitStatus);
}
