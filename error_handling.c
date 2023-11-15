#include "shell.h"

/**
 * recursiveNumToString - Recursively converts an unsigned integer to a string
 * @num: Number to be converted.
 * @strBuffer: buffer to write string into
 *
 * Return: returns a string representation of number
 */
unsigned int recursiveNumToString(unsigned int num, char *strBuffer)
{
        unsigned int currentIndex = 0;

        if ((num / 10) > 0)
                currentIndex += recursiveNumToString((num / 10), strBuffer);
        strBuffer[currentIndex] = (num % 10) + 48;
        return (currentIndex++);
}

/**
 * convertNumToString - Converts a number to a string representation.
 * @number: The number to be converted.
 *
 * Return: a string representation of number
 */
char *convertNumToString(unsigned int number)
{
        char *strBuffer;
        unsigned int len = 1, num = number;

        while (num > 9)
        {
                num /= 10;
                len++;
        }
        strBuffer = (char *) malloc((len + 1) * sizeof(char));
        if (strBuffer == NULL)
                return (NULL);
        recursiveNumToString(number, strBuffer);
        strBuffer[len] = '\0';
        return (strBuffer);
}

/**
 * printErrorMessage - prints error message to the console
 * @shellName: name of the shell being run
 * @command: name of the command that error occurred
 * @number: number of program executed in this shell session
 *
 * Return: void (nothing)
 */
void printErrorMessage(char *shellName, char *command, unsigned int number)
{
        char errorMessage[128], *count_strBuffer = convertNumToString(number);
        unsigned int currentIndex, n = 0;

        if (count_strBuffer == NULL)
                exit(EXIT_FAILURE);
        for (currentIndex = 0; shellName[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = shellName[currentIndex];
        errorMessage[n++] = ':';
        errorMessage[n++] = ' ';
        for (currentIndex = 0; count_strBuffer[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = count_strBuffer[currentIndex];
        errorMessage[n++] = ':';
        errorMessage[n++] = ' ';
        for (currentIndex = 0; command[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = command[currentIndex];
        errorMessage[n++] = '\0';
        free(count_strBuffer);
        perror(errorMessage);
}

/**
 * printExitErrorMessage - prints error message to the terminal.
 * @shellName: name of the shell being run
 * @command: name of the command that error occurred in
 * @number: number of program executed in this shell session
 * @errorArgument: The exit errorArgument that caused error
 *
 * Return: void (nothing)
 */
void printExitErrorMessage(char *shellName, char *command, unsigned int number, char *errorArgument)
{
        char errorMessage[BUFSIZE], *count_strBuffer = convertNumToString(number);
        char errorPrint[] = "Illegal number: ";
        unsigned int currentIndex;
        size_t n = 0;

        if (count_strBuffer == NULL)
                exit(EXIT_FAILURE);
        for (currentIndex = 0; shellName[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = shellName[currentIndex];
        errorMessage[n++] = ':';
        errorMessage[n++] = ' ';
        for (currentIndex = 0; count_strBuffer[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = count_strBuffer[currentIndex];
        errorMessage[n++] = ':';
        errorMessage[n++] = ' ';
        for (currentIndex = 0; command[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = command[currentIndex];
        errorMessage[n++] = ':';
        errorMessage[n++] = ' ';
        for (currentIndex = 0; errorPrint[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = errorPrint[currentIndex];
        for (currentIndex = 0; errorArgument[currentIndex] != '\0'; currentIndex++)
                errorMessage[n++] = errorArgument[currentIndex];
        errorMessage[n++] = '\n';
        free(count_strBuffer);
        write(STDERR_FILENO, errorMessage, n);
}
