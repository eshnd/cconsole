#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

typedef struct {
  char* str;
  size_t size;
} dstring;

char* current_filename;
char* compiler;

void exec(char* input){
  char result[strlen(input) + 2];
  strcpy(result, input);

  result[strlen(input)] = '}';
  result[strlen(input) + 1] = '\0';

  FILE *code_file = fopen(current_filename, "w");
  fprintf(code_file, "%s", result); 

  char command[strlen(current_filename) + strlen(compiler) + 30]; // gcc current_filename -o .cshell_compiled
  sprintf(command, "%s %s -o .cshell_compiled", compiler, current_filename);

  fclose(code_file);
  system(command);
  system("./.cshell_compiled");
  remove(".cshell_compiled");

}

int main(int argc, char** argv){
  printf("cshell v0.0.3 by Eshaan Desh\n\"cshell exit;\" to exit and \"cshell save <filename>;\" to save code\n");
  current_filename = ".cshell_code.c";
  if (argc > 1){
    compiler = argv[1];
  } else {
    compiler = "gcc";
  }

  dstring full_code;
  full_code.size = 12;
  full_code.str = malloc(full_code.size);
  strcpy(full_code.str, "int main(){");

  while (1){
    dstring to_run;
    char* input = readline(">>> ");

    to_run.size = strlen(input) + 4;
    to_run.str = malloc(to_run.size);
    to_run.str[0] = '\n';
    strcpy(to_run.str + 1, input);
    to_run.str[strlen(input) + 1] = '\n';
    to_run.str[strlen(input) + 2] = '\0';
    free(input);

    // int input_char = 0;
    //
    // while (input_char != -1 && input_char != '\n'){
    //   input_char = getchar();
    //   if (to_run.size == strlen(to_run.str) + 1){
    //     to_run.size *= 2;
    //     to_run.str = realloc(to_run.str, to_run.size);
    //   }
    //   
    //   size_t to_run_current_index = strlen(to_run.str);
    //   to_run.str[to_run_current_index] = (char) input_char;
    //   to_run.str[to_run_current_index + 1] = '\0';
    // }

    while (full_code.size < strlen(full_code.str) + strlen(to_run.str) + 1) {
      full_code.size *= 2;
      full_code.str = realloc(full_code.str, full_code.size);
    }

    char* check_for_save = malloc(strlen(to_run.str) + 1);
    strcpy(check_for_save, to_run.str);
    if (strlen(check_for_save) > 13){
      check_for_save[13] = '\0';
    }

    if (strcmp(to_run.str, "\ncshell exit;\n") == 0){
      if (access(".cshell_code.c", F_OK) == 0){
        remove(".cshell_code.c");
      }

      exit(0);
    } else if (strcmp(check_for_save, "\ncshell save ") == 0){
      char* filename = malloc(strlen(to_run.str) + 1);
      strcpy(filename, to_run.str);
      filename[strlen(filename) - 2] = '\0';

      rename(current_filename, filename + 13);

      free(filename);
      continue;
    }

    free(check_for_save);
    
    strcpy(full_code.str + strlen(full_code.str), to_run.str);
    exec(full_code.str);

    free(to_run.str);
  }

  free(full_code.str);
}
