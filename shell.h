#ifndef SHELL_H
#define SHELL_H

/*
 * Define the maximum length of a command line.
 */
#define MAX_CMDLINE 1024

/*
 * Define the maximum number of arguments in a command.
 */
#define MAX_ARGS 32

/*
 * Define the maximum number of built-in commands.
 */
#define MAX_BUILTINS 16

/*
 * Define the structure of a command.
 */
typedef struct command {
    char *name;
    char **args;
} command_t;

/*
 * Define the prototype for the `execute()` function.
 * This function takes a command structure as input and executes the command.
 */
extern void execute(command_t *cmd);

/*
 * Define the prototype for the `parse_cmdline()` function.
 * This function takes a command line as input and parses it into a command structure.
 */
extern command_t *parse_cmdline(char *cmdline);

/*
 * Define the prototype for the `repl()` function.
 * This function implements the read-eval-print loop of the shell.
 */
extern void repl();

#endif /* SHELL_H */
