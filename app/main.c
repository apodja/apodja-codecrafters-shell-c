#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_echo(char* input);

int main() {

  char input[100];

  while (1)
  {
    printf("$ ");
    fflush(stdout);
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;

    if (strncmp(input, "exit", 4) == 0) {
      exit(EXIT_SUCCESS);
    } else if (strncmp(input, "echo", 4) == 0) {
      do_echo(input);
      fflush(stdout);
    } else {
      printf("%s: command not found\n", input);
      fflush(stdout);
    }
  }
    
  return 0;
}

void do_echo(char* input) {
  char* temp = strchr(input, ' ');
  printf("%s\n", temp + 1);
}
