
#include "defines.h"
#include "file.h"
#include "pass.h"
#include "token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

  if (argc < 4){
    printf("Please follow this syntax: ./c_asm <input.asm> -o <output.bin>\n");
    return -1;
  }

  
  char* contents = (char*)malloc(FILE_SIZE);
  printf("Starting to read file...\n");
  contents = read_file(argv[1]);

  // char contents[] = "_start:\nLDI R1, #7\nJMP _end\n_end:\nJMP _start";

  char output_code[1024] = {0};

  char assemblyCodeCopy1[1024];
  char assemblyCodeCopy2[1024];
  strcpy(assemblyCodeCopy1, contents);
  strcpy(assemblyCodeCopy2, contents);

  first_pass(assemblyCodeCopy1);

  second_pass(assemblyCodeCopy2, output_code);

  printf("Final output before tokenizing: %s\n", output_code);

  Token tokens[MAX_TOKENS];
  int token_count = 0;

  tokenize_string(output_code, tokens, &token_count);
  
  for (int i = 0; i < token_count; i++){
    printf("Token %d: Type = %d, value '%d', register '%d'\n", i, tokens[i].type, tokens[i].val, tokens[i].reg);
  }

  printf("Now writing tokens to file\n");
  write_tokens_to_file(argv[argc - 1], tokens, token_count);

  return 0;
}
