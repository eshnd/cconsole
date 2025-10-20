#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct {
  char* str;
  size_t size;
} dstring;

char* current_filename;
char* compiler;

int exec(char* input){
  char result[strlen(input) + 2];
  strcpy(result, input);

  result[strlen(input)] = '}';
  result[strlen(input) + 1] = '\0';

  FILE *code_file = fopen(current_filename, "w");
  fprintf(code_file, "%s", result); 

  char command[strlen(current_filename) + strlen(compiler) + 35]; // gcc current_filename -o .cconsole_compiled
  sprintf(command, "%s %s -o .cconsole_compiled", compiler, current_filename);

  fclose(code_file);
  int out_result = system(command);
  system("./.cconsole_compiled");
  remove(".cconsole_compiled");

  return out_result;
}

int main(int argc, char** argv){
  printf("cconsole v0.0.4 by Eshaan Desh\n\"cconsole exit;\" to exit and \"cconsole save <filename>;\" to save code\n");
  current_filename = ".cconsole_code.c";
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
    add_history(input);

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

    if (strcmp(to_run.str, "\ncconsole exit;\n") == 0){
      if (access(".cconsole_code.c", F_OK) == 0){
        remove(".cconsole_code.c");
      }

      exit(0);
    } else if (strcmp(check_for_save, "\ncconsole save ") == 0){
      char* filename = malloc(strlen(to_run.str) + 1);
      strcpy(filename, to_run.str);
      filename[strlen(filename) - 2] = '\0';

      rename(current_filename, filename + 13);

      free(filename);
      continue;
    }

    free(check_for_save);
    
    char old_full_code[strlen(full_code.str) + 1];
    strcpy(old_full_code, full_code.str);

    strcpy(full_code.str + strlen(full_code.str), to_run.str);
    int out_result = exec(full_code.str);
    if (out_result != 0){
      strcpy(full_code.str, old_full_code);
    } 

    free(to_run.str);
  }

  free(full_code.str);
}
