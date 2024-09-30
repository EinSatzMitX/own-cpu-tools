
#include "defines.h"
#include "file.h"
#include "token.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

  
  char* contents = (char*)malloc(FILE_SIZE);
  printf("Starting to read file...\n");
  contents = read_file("test.asm");

  char* trimmed = trim_file(contents);

  Token tokens[MAX_TOKENS];
  int token_count = 0;

  tokenize_string(trimmed, tokens, &token_count);

  for (int i = 0; i < token_count; i++){
    printf("Token %d: Type = %d, value '%d', register '%d'\n", i, tokens[i].type, tokens[i].val, tokens[i].reg);
  }

  write_tokens_to_file("output.bin", tokens, token_count);


  return 0;
}
