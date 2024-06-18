#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void do_echo(char* input);
bool isBuiltIn(char* cmd);
char* get_nth_arg(char* input, int n);

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
      
    } else if (strncmp(input, "type", 4) == 0) {
      char* cmdType = get_nth_arg(input, 2);
      if (isBuiltIn(cmdType))
      {
        printf("%s is a shell builtin\n", cmdType);
      } else {
        printf("%s: not found\n", cmdType);
      }
      
    }  else {
      printf("%s: command not found\n", input);
    }
    fflush(stdout);
  }
    
  return 0;
}

void do_echo(char* input) {
  char* temp = strchr(input, ' ');
  printf("%s\n", temp + 1);
}

bool isBuiltIn(char* cmd) {
  char* builtInCmds[] = {"echo", "exit", "type"};

  for(int i = 0; i < 3; i++) {
    if (strcmp(builtInCmds[i], cmd) == 0)
    {
      return true;
    }
  }

  return false;
}

char* get_nth_arg(char* input, int n) {
  const char* delim = " ";
  char* input_cpy = strdup(input);
  int i = 1;
  char* ret;

  char* token = strtok(input_cpy, delim);
  if (token != NULL)
  {
    if (n == 1)
    {

      ret = strdup(token);
      free(input_cpy);
      return ret;
    } else {
      while (token != NULL)
      {
        if (i == n)
        {
          ret = strdup(token);
          free(input_cpy);
          return ret;
        }
        token = strtok(NULL, delim);
        i++;
      }
    }
  }
   
  return NULL;
}

