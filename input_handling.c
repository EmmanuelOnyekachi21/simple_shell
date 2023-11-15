#include "shell.h"

/**
 * assignInputBuffer - assigns the line pointer for getLine
 * @lineptr: pointer to the buffer that store the input string.
 * @buffer: str that is been called to line
 * @lineSize: size of line buffer
 * @bufferSize: The size of the buffer
 */
void assignInputBuffer(char **lineptr, size_t *lineSize, char *buffer, size_t bufferSize)
{

	if (*lineptr == NULL)
	{
		if  (bufferSize > BUFSIZE)
			*lineSize = bufferSize;

		else
			*lineSize = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*lineSize < bufferSize)
	{
		if (bufferSize > BUFSIZE)
			*lineSize = bufferSize;
		else
			*lineSize = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		copyString(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * getLine - Read inpt from stream
 * @lineptr: buffer that stores the input string.
 * @lineSize: size of line buffer.
 * @stream: stream to read from
 * Return: The number of bytes, returnValue
 */
ssize_t getLine(char **lineptr, size_t *lineSize, FILE *stream)
{
	int bytesRead;
	static ssize_t bytesReadTotal;
	ssize_t returnValue;
	char *buffer;
	char currentChar = 'z';

	if (bytesReadTotal == 0)
		fflush(stream);
	else
		return (-1);
	bytesReadTotal = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (currentChar != '\n')
	{
		bytesRead = read(STDIN_FILENO, &currentChar, 1);
		if (bytesRead == -1 || (bytesRead == 0 && bytesReadTotal == 0))
		{
			free(buffer);
			return (-1);
		}
		if (bytesRead == 0 && bytesReadTotal != 0)
		{
			bytesReadTotal++;
			break;
		}
		if (bytesReadTotal >= BUFSIZE)
			buffer = realloc(buffer, bytesReadTotal);
		buffer[bytesReadTotal] = currentChar;
		bytesReadTotal++;
	}
	buffer[bytesReadTotal] = '\0';
	assignInputBuffer(lineptr, lineSize, buffer, bytesReadTotal);
	returnValue = bytesReadTotal;
	if (bytesRead != 0)
		bytesReadTotal = 0;
	return (returnValue);
}
