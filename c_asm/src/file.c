

#include "file.h"
#include "defines.h"
#include "token.h"
#include "typedef.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* read_file(const char* name){
  FILE* file = fopen(name, "r");
  if (!file){
    printf("Error opening file!");
    return NULL;
  }

    // Move file pointer to the end to get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);  // Reset file pointer to the beginning

    // Allocate memory for the file content (+1 for null terminator)
    char *content = malloc(file_size + 1);
    if (content == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Read the file into the content buffer
    fread(content, 1, file_size, file);
    content[file_size] = '\0';  // Null-terminate the string

    fclose(file);
    return content;
}

char* trim_file(const char* input){
  int i = 0, j = 0;
  int in_comment = 0;
  char* result = (char*)malloc(sizeof(char*) * (strlen(input) + 1));

  if (result == NULL){
    return NULL;
  }

  while (input[i] != '\0'){
    if (in_comment){
      // Skip characters until a newline is found
      if (input[i] == '\n'){
        result[j++] = ' ';
        in_comment = 0;
      }
      i++;
    }
    else if (input[i] == ';'){
      // ; indicates that a comment is started
      in_comment = 1;
      result[j++] = ' ';
      i++;
    }
    else if (isspace(input[i])){
      // Replace all whitespaces with a single charcter
      if (j == 0 || result[j - 1] != ' '){
        result[j++] = ' ';
      }
      i++;
    }
    else {
      // Everything else will just be copied from one string to another
      result[j++] = input[i++];
    }
  }

  result[j] = '\0';
  
  return result;
}


void write_tokens_to_file(const char* filename, Token tokens[], int token_count){
  FILE* file = fopen(filename, "wb");
  if (!file){
    printf("Error: Could not open file '%s' for writing.\n", filename);
  }

  // Iterate over the tokens and write them in hex format
  for (int i = 0; i < token_count; i++){
    switch (tokens[i].type) {
      case TOKEN_OPCODE:{
        fwrite(&tokens[i].opcode, sizeof(u8), 1, file);
        break;
      }
      case TOKEN_REGISTER:{
        fwrite(&tokens[i].reg, sizeof(u8), 1, file);
        break;
      }
      case TOKEN_IMMEDIATE:{
        fwrite(&tokens[i].val.low, sizeof(u8), 1, file);
        fwrite(&tokens[i].val.high, sizeof(u8), 1, file);
        break;
      }
    }

  }

  fclose(file);
  printf("Tokens succesfully written to '%s'\n", filename);

}
