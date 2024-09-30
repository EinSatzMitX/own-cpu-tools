

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
    if (input == NULL) {
        return NULL;
    }

    // Create a modifiable copy of the input
    char* trimmed = strdup(input);  // Copy the input string
    if (trimmed == NULL) {
        return NULL;  // Memory allocation failed
    }

    char *start = trimmed, *end, *dest = trimmed;

    // Step 1: Trim leading whitespaces
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // Step 2: Process the string, keeping only single spaces between words
    int in_space = 0;
    while (*start) {
        if (isspace((unsigned char)*start)) {
            if (!in_space) { // Only allow one space
                *dest++ = ' ';
                in_space = 1;
            }
        } else {
            *dest++ = *start;
            in_space = 0;
        }
        start++;
    }
    
    // Step 3: Trim trailing whitespace by removing the last space if any
    end = dest - 1;
    if (end >= trimmed && *end == ' ') {
        *end = '\0';  // Null-terminate after the last word
    } else {
        *dest = '\0'; // Null-terminate if no trailing space
    }

    return trimmed;
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
