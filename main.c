#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void) 
{
    /* Start the read-eval-print loop. */
    repl();

    return 0;
}
void repl() {
    /* Allocate a buffer to store the command line. */
    char *cmdline = malloc(MAX_CMDLINE);
    if (cmdline == NULL) {
        perror("malloc");
        exit(1);
    }

    /* Read the command line from the user. */
    printf("$ ");
    fgets(cmdline, MAX_CMDLINE, stdin);

    /* Parse the command line. */
    command_t *cmd = parse_cmdline(cmdline);

    /* Execute the command. */
    execute(cmd);

    /* Free the command line buffer. */
    free(cmdline);
}
