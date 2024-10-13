#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "defines.h"
#include "token.h"
#include "typedef.h"


u8 get_opcode(const char *str){
  /* 0x00 Opcodes: Load instructions */
  if (strcmp(str, "LDI") == 0) {
    return OPCODE_LOAD_REG_IMM;  // Example: LDI opcode is 0x00
  }
  else if (strcmp(str, "LDR") == 0){
    return OPCODE_LOAD_REG_REG;
  }
  else if (strcmp(str, "LDM") == 0) {
    return OPCODE_LOAD_REG_ZPG; 
  }
  /* 0x10 Opcodes: Store instructions */
  else if (strcmp(str, "SLR") == 0) {
    return OPCODE_STORE_LOW_MEM; 
  }
  else if (strcmp(str, "SHR") == 0) {
    return OPCODE_STORE_HIGH_MEM; 
  }
  else if (strcmp(str, "SWR") == 0) {
    return OPCODE_STORE_REG_MEM; 
  }
  /* 0x20 Opcodes: Compare instructions */
  else if (strcmp(str, "CRR") == 0) {
    return OPCODE_CMP_REG_REG; 
  }
  else if (strcmp(str, "CRM") == 0) {
    return OPCODE_CMP_REG_MEM; 
  }
  else if (strcmp(str, "CRI") == 0) {
    return OPCODE_CMP_REG_IMM; 
  }
  /* 0x30 Opcodes: Branch instructions*/
  //
  else if (strcmp(str, "BEQ") == 0) {
    return OPCODE_BRANCH_EQUAL;
  }
  else if (strcmp(str, "BNQ") == 0) {
    return OPCODE_BRANCH_NOT_EQUAL;
  }
  else if (strcmp(str, "BLT") == 0) {
    return OPCODE_BRANCH_LESS_THAN;
  }
  else if (strcmp(str, "BGT") == 0) {
    return OPCODE_BRANCH_GREATER_THEN;
  }
  else if (strcmp(str, "BLQ") == 0) {
    return OPCODE_BRANCH_LESS_OR_EQUAL;
  }
  else if (strcmp(str, "BGQ") == 0) {
    return OPCODE_BRANCH_GREATER_OR_EQUAL;
  }
  else if (strcmp(str, "BOC") == 0) {
    return OPCODE_BRANCH_OVERFLOW_CLEAR;
  }
  else if (strcmp(str, "BOS") == 0) {
    return OPCODE_BRANCH_OVERFLOW_SET;
  }
  else if (strcmp(str, "JMP") == 0) {
    return OPCODE_BRANCH_ALWAYS;
  }
  else if (strcmp(str, "JSR") == 0){
    return OPCODE_JSR;
  }
  else if (strcmp(str, "RET") == 0){
    return OPCODE_RET;
  }
  /* 0x40 Opcodes: Arithmetical instructions */
  /* Signed Arithmetic*/
  else if (strcmp(str, "ASI") == 0) {
    return OPCODE_ADD_SIGNED_REG_IMM; 
  }
  else if (strcmp(str, "SSI") == 0) {
    return OPCODE_SUB_SIGNED_REG_IMM; 
  }
  //
  
  /* Unsigned Arithmetic */
  else if (strcmp(str, "AUI") == 0) {
    return OPCODE_ADD_UNSIGNED_REG_IMM; 
  }
  else if (strcmp(str, "SUI") == 0) {
    return OPCODE_SUB_UNSIGNED_REG_IMM; 
  }

  /* 0x50 Opcodes: logic instructions */
  else if (strcmp(str, "XRI") == 0) {
    return OPCODE_XOR_REG_IMM; 
  }
  else if (strcmp(str, "XRM") == 0) {
    return OPCODE_XOR_REG_MEM; 
  }
  else if (strcmp(str, "XRR") == 0) {
    return OPCODE_XOR_REG_REG; 
  }

  else if (strcmp(str, "ANI") == 0) {
    return OPCODE_AND_REG_IMM; 
  }
  else if (strcmp(str, "ANM") == 0) {
    return OPCODE_AND_REG_MEM; 
  }
  else if (strcmp(str, "ANR") == 0) {
    return OPCODE_AND_REG_REG; 
  }

  else if (strcmp(str, "NOT") == 0) {
    return OPCODE_NOT_REG; 
  }

  else if (strcmp(str, "ORI") == 0) {
    return OPCODE_OR_REG_IMM; 
  }
  else if (strcmp(str, "ORM") == 0) {
    return OPCODE_OR_REG_MEM; 
  }
  else if (strcmp(str, "ORR") == 0) {
    return OPCODE_OR_REG_REG; 
  }

  else if (strcmp(str, "LSI") == 0) {
    return OPCODE_LEFT_SHIFT_REG_IMM; 
  }
  else if (strcmp(str, "LSM") == 0) {
    return OPCODE_LEFT_SHIFT_REG_MEM; 
  }
  else if (strcmp(str, "LSR") == 0) {
    return OPCODE_LEFT_SHIFT_REG_REG; 
  }

  else if (strcmp(str, "RSI") == 0) {
    return OPCODE_RIGHT_SHIFT_REG_IMM; 
  }
  else if (strcmp(str, "RSM") == 0) {
    return OPCODE_RIGHT_SHIFT_REG_MEM; 
  }
  else if (strcmp(str, "RSR") == 0) {
    return OPCODE_RIGHT_SHIFT_REG_REG; 
  }


  // Add more opcodes as needed
  //
  else if (strcmp(str, "HLT") == 0){
    return OPCODE_HALT;
  }
  else if (strcmp(str, "NOP") == 0){
    return OPCODE_NOOP;
  }

  /* 0x60 Opcodes: Stack instructions 0x60 Opcodes: Stack instructions */
  else if (strcmp(str, "PSH") == 0){
    return OPCODE_PUSH_REG;
  }  
  else if (strcmp(str, "POP") == 0){
    return OPCODE_POP_REG;
  }  

  printf("Unknown Opcode: %s.  ", str);
  printf("Value 0xFF is being added to the string.\n");
  return 0xFF; // NOOP
}

u8 get_register(const char *str){
    if (str[0] == 'R') {
        // Convert the number part (starting at str[1]) to an integer
        return (u8)atoi(str + 1);  // Converts the substring starting at str[1] into a number
    } else {
        // Handle invalid register format
        printf("Error: Invalid register format '%s'\n", str);
        return 0xFF;  // Return an error value (you can change this as needed)
    }
}

u16 get_immediate(const char* str) {
    return (u16)atoi(str);  // Convert the substring to an integer
}

int is_register(const char* str) {
    return (str[0] == 'R' && isdigit(str[1]));  // Format: "R0", "R1", etc.
}

// Function to check if the string is an immediate value (e.g., #5, #123)
int is_immediate(const char* str) {
    return (str[0] == '#' && isdigit(str[1]));  // Format: "#5", "#123", etc.
}

int is_label(const char* str){
  return (str[strlen(str) - 1] == ':' ? 1 : 0);
}

// Function to tokenize the string and store it in the token array
void tokenize_string(const char* input, Token tokens[], int* token_count) {
    char buffer[FILE_SIZE];  // Local copy of the input
    strcpy(buffer, input);
    printf("Successfully copied input to buffer\n");
    
    // Split the input string by whitespace
    char* token = strtok(buffer, " ");
    *token_count = 0;
    printf("Successfully converted buffer to token\n");

  // Process each token
  while (token != NULL) {
    if (*token_count >= MAX_TOKENS){
      perror("Maximum token count exceeded");
      return;
    }


    if (is_register(token)) {
      // Register token
      tokens[*token_count].type = TOKEN_REGISTER;
      tokens[*token_count].reg = get_register(token);  // Convert register string to numeric value
    } else if (isdigit(token[0])) {
      // Immediate value token
      tokens[*token_count].type = TOKEN_IMMEDIATE;
      tokens[*token_count].val.value = get_immediate(token);  // Convert immediate string to numeric value
    }
    else if (is_label(token)){
             
    } else {
      // Opcode token
      tokens[*token_count].type = TOKEN_OPCODE;
      tokens[*token_count].opcode = get_opcode(token);  // Convert opcode string to numeric value
    }
    (*token_count)++;
    token = strtok(NULL, " ");
    }
}
