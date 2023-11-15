#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

char *GETENV(const char *name);
int _env(void);

char **tokenizeString(char *input);
void freeTokenArray(char **tokens);
char *findAbsolutePath(char *filename);
void printErrorMessage(char *shellName, char *command, unsigned int number);
int customStrncmp(char *str1, char *str2, int n);
char *copyString(char *destination, char *source);
ssize_t getLine(char **lineptr, size_t *lineSize, FILE *stream);
void printExitErrorMessage(char *shellName, char *command, unsigned int number, char *errorArgument);
int exitShell(char *exitArgument);
extern char **environ;

#endif
