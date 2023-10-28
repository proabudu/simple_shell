#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

int main() {
  char command[MAX_COMMAND_LENGTH];
  int pid;

  while (1) {
    // Display the prompt.
    printf("$ ");

    // Read the command line.
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // Check for the end of file condition.
    if (feof(stdin)) {
      break;
    }

    // Remove the trailing newline character.
    command[strlen(command) - 1] = '\0';

    // Try to find the executable.
    char *path = getenv("PATH");
    char *executable = strtok(path, ":");
    while (executable != NULL) {
      char full_path[strlen(executable) + strlen("/") + strlen(command) + 1];
      strcpy(full_path, executable);
      strcat(full_path, "/");
      strcat(full_path, command);

      if (access(full_path, X_OK) == 0) {
        // Found the executable.
        break;
      }

      executable = strtok(NULL, ":");
    }

    // If the executable was not found, print an error message.
    if (executable == NULL) {
      printf("Command not found: %s\n", command);
      continue;
    }

    // Create a child process to execute the command.
    pid = fork();
    if (pid < 0) {
      // Error forking.
      perror("fork");
      exit(1);
    } else if (pid == 0) {
      // Child process.
      execve(full_path, NULL, environ);
      // If execve fails, print an error message and exit.
      perror("execve");
      exit(1);
    } else {
      // Parent process.
      waitpid(pid, NULL, 0);
    }
  }

  return 0;
}
