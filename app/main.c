#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct {
  char** path_list;
  int path_list_len;
} PathList;

void do_echo(char* input);
bool isBuiltIn(char* cmd);
char* get_nth_arg(char* input, int n);
PathList* parse_path(char* path);
void free_pl(PathList* pl);
void print_list(PathList* pl);
char* file_exists(PathList* pl, char* cmd);

int main() {
  char input[100];
  PathList* pl = parse_path(getenv("PATH"));

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
      if (cmdType != NULL)
      {
        if (isBuiltIn(cmdType))
        {
          printf("%s is a shell builtin\n", cmdType);
        } else if(pl != NULL) {
          char* fpath = file_exists(pl, cmdType);
          if (fpath != NULL)
          {
            printf("%s is %s\n", cmdType, fpath);
            free(fpath);
          } else {
            printf("%s: not found\n", cmdType);
          }
        }
        else {
          printf("%s: not found\n", cmdType);
        }
      } else {
        printf("Command type expects an argument\n");
      }
    } else {
      char* cmdType = get_nth_arg(input, 1);
      if (file_exists(pl, cmdType) != NULL)
      {
        system(input);
      } else {
        printf("%s: not found\n", cmdType);
      }
    }
    fflush(stdout);
  }
  free_pl(pl);
    
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

PathList* parse_path(char* path) {
  PathList* pl = malloc(sizeof(PathList));
  pl->path_list = malloc(10 * sizeof(char*));
  pl->path_list_len = 0;

  char* start = path;
  char* next;
  int i = 0 , j = 0;
  int path_len = strlen(path);

  while (i < path_len)
  {
    if (path[i] == ':')
    {
      next = &(path[i+1]);
      path[i] = '\0';
      pl->path_list[j] = malloc(strlen(start) + 1);
      strcpy(pl->path_list[j++], start); 
      start = next;
    }
    i++;
  }
  pl->path_list[j] = malloc(strlen(start) + 1);
  strcpy(pl->path_list[j++], start);
  pl->path_list_len = j;

  return pl;
}

void print_list(PathList* pl) {
  printf("(%d) : [", pl->path_list_len);
  if (pl->path_list_len > 0)
  {
    for (int i = 0; i < pl->path_list_len; i++)
    {
      printf("%s, ", pl->path_list[i]);
    }
  } 
  printf("]\n");
  
}

void free_pl(PathList* pl) {
  if (pl->path_list_len > 0)
  {
    for (int i = 0; i < pl->path_list_len; i++)
    {
      free(pl->path_list[i]);
    }
  } 
  free(pl);
}

char* file_exists(PathList* pl, char* cmd) {
  if (cmd == NULL) return NULL;
  char temp[50];

  for (int i = 0; i < pl->path_list_len; i++)
  {
    sprintf(temp, "%s/%s", pl->path_list[i], cmd);
    if (access(temp, F_OK) == 0)
    {
      return strdup(temp);
    }
  }

  return NULL;
}