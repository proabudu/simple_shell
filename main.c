#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

/**
 * main - A simple shell that executes commands
 * @argc: The number of arguments
 * @argv: The arguments
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
    char *line; /* The input line */
    char **args; /* The arguments */
    int status; /* The status of the execution */

    if (argc > 1) /* Check if there are any arguments */
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return (1);
    }

    do {
        printf("$ "); /* Print the prompt */
        line = read_line(); /* Read the input line */
        args = split_line(line); /* Split the line into arguments */
        status = execute(args); /* Execute the command */

        free(line); /* Free the allocated memory */
        free(args);
    } while (status); /* Loop until the status is 0 */

    return (0);
}

/**
 * read_line - Read a line from stdin
 * Return: The line as a string
 */
char *read_line(void)
{
    char *line = NULL; /* The line pointer */
    size_t bufsize = 0; /* The buffer size */
    ssize_t nread; /* The number of characters read */

    nread = getline(&line, &bufsize, stdin); /* Get the line from stdin */

    if (nread == -1) /* Check for errors or EOF */
    {
        if (feof(stdin)) /* If EOF, exit normally */
        {
            printf("\n");
            exit(0);
        }
        else /* If error, exit with error */
        {
            perror("read_line");
            exit(1);
        }
    }

    return (line); /* Return the line */
}

/**
 * split_line - Split a line into tokens
 * @line: The line to split
 * Return: An array of tokens
 */
char **split_line(char *line)
{
    char **tokens; /* The tokens array */
    char *token; /* The current token */
    size_t bufsize = BUFSIZE; /* The buffer size */
    int index = 0; /* The index of the array */

    tokens = malloc(bufsize * sizeof(char *)); /* Allocate memory for the array */

    if (tokens == NULL) /* Check for memory errors */
    {
        perror("split_line");
        exit(1);
    }

    token = strtok(line, DELIM); /* Get the first token */

    while (token != NULL) /* Loop through the tokens */
    {
        tokens[index] = token; /* Assign the token to the array */
        index++;

        if (index >= bufsize) /* If the buffer is full, reallocate more memory */
        {
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            
            if (tokens == NULL) /* Check for memory errors */
            {
                perror("split_line");
                exit(1);
            }
        }

        token = strtok(NULL, DELIM); /* Get the next token */
    }

    tokens[index] = NULL; /* Terminate the array with a NULL pointer */

    return (tokens); /* Return the array of tokens */
}

/**
 * execute - Execute a command with arguments
 * @args: The arguments array
 * Return: 1 to continue the loop, 0 to exit
 */
int execute(char **args)
{
    pid_t pid; /* The process ID */
    int status; /* The status of the execution */

    if (args[0] == NULL) /* If there is no command, do nothing */
        return (1);

    pid = fork(); /* Fork a child process */

    if (pid == 0) /* If child process, execute the command */
    {
        if (execve(args[0], args, NULL) == -1) /* Check for execution errors */
        {
            perror(args[0]);
            exit(1);
        }
    }
    else if (pid < 0) /* If fork error, exit with error */
    {
        perror("execute");
        exit(1);
    }
    else /* If parent process, wait for the child to finish */
    {
        wait(&status);
    }

    return (1); /* Return 1 to continue the loop */
}
