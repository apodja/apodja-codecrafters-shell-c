#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char input[100];

  while (1)
  {
    printf("$ ");
    fflush(stdout);
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;

    if (strncmp(input, "exit", 4) == 0)
    {
      exit(EXIT_SUCCESS);
    } else {
      printf("%s: command not found\n", input);
      fflush(stdout);
    }
    

    
  }
    
  return 0;
}
