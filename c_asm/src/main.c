
#include "defines.h"
#include "file.h"
#include "token.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

  if (argc < 4){
    printf("Please follow this syntax: ./c_asm <input.asm> -o <output.bin>\n");
    return -1;
  }

  
  char* contents = (char*)malloc(FILE_SIZE);
  printf("Starting to read file...\n");
  contents = read_file(argv[1]);

  char* trimmed = trim_file(contents);

  Token tokens[MAX_TOKENS];
  int token_count = 0;

  tokenize_string(trimmed, tokens, &token_count);

  for (int i = 0; i < token_count; i++){
    printf("Token %d: Type = %d, value '%d', register '%d'\n", i, tokens[i].type, tokens[i].val, tokens[i].reg);
  }

  write_tokens_to_file(argv[argc -1], tokens, token_count);


  return 0;
}
