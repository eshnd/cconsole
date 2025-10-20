#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char* str;
  size_t size;
} dstring;

char* current_filename;

void exec(char* input){
  

  char result[strlen(input) + 2];
  strcpy(result, input);

  result[strlen(input)] = '}';
  result[strlen(input) + 1] = '\0';

  FILE *code_file = fopen(current_filename, "w");
  fprintf(code_file, "%s", result); 

  char command[strlen(current_filename) + 30]; // gcc current_filename -o .cshell_compiled
  sprintf(command, "gcc %s -o .cshell_compiled", current_filename);

  fclose(code_file);
  system(command);
  system("./.cshell_compiled");
  remove(".cshell_compiled");

}

int main(){
  current_filename = ".cshell_code.c";

  dstring full_code;
  full_code.size = 12;
  full_code.str = malloc(full_code.size);
  strcpy(full_code.str, "int main(){");

  printf(">>> ");
  while (1){
    dstring to_run;
    to_run.size = 2;
    to_run.str = malloc(to_run.size);
    to_run.str[0] = '\n';
    to_run.str[1] = '\0';

    int input_char = 0;

    while (input_char != -1 && input_char != '\n'){
      input_char = getchar();
      if (to_run.size == strlen(to_run.str) + 1){
        to_run.size *= 2;
        to_run.str = realloc(to_run.str, to_run.size);
      }
      
      size_t to_run_current_index = strlen(to_run.str);
      to_run.str[to_run_current_index] = (char) input_char;
      to_run.str[to_run_current_index + 1] = '\0';
    }

    while (full_code.size < strlen(full_code.str) + strlen(to_run.str) + 1) {
      full_code.size *= 2;
      full_code.str = realloc(full_code.str, full_code.size);
    }
    
    if (strcmp(to_run.str, "\ncshell exit;\n") == 0){
      if (access(".cshell_code.c", F_OK) == 0){
        remove(".cshell_code.c");
      }

      exit(0);
    } else if (strcmp(to_run.str, "\ncshell save;\n") == 0){
      printf("please provide a filename (less than 50 chars, please): ");
      
      char filename[55];
      scanf("%s", filename);
      rename(current_filename, filename);
      continue;
    }
    
    strcpy(full_code.str + strlen(full_code.str), to_run.str);
    exec(full_code.str);

    free(to_run.str);
    printf("\n>>> ");
  }

  free(full_code.str);
}
