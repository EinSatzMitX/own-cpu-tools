#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "token.h"
#include "typedef.h"


u8 get_opcode(const char *str){
    if (strcmp(str, "LRI") == 0) {
        return OPCODE_LOAD_REG_IMM;  // Example: LRI opcode is 0x00
    }
    // Add more opcodes as needed
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
    return (u16)atoi(str + 1);  // Convert the substring after '#' to an integer
}

int is_register(const char* str) {
    return (str[0] == 'R' && isdigit(str[1]));  // Format: "R0", "R1", etc.
}

// Function to check if the string is an immediate value (e.g., #5, #123)
int is_immediate(const char* str) {
    return (str[0] == '#' && isdigit(str[1]));  // Format: "#5", "#123", etc.
}

// Function to tokenize the string and store it in the token array
void tokenize_string(const char* input, Token tokens[], int* token_count) {
    char buffer[100];  // Local copy of the input
    strcpy(buffer, input);
    
    // Split the input string by whitespace
    char* token = strtok(buffer, " ");
    *token_count = 0;

    // Process each token
    while (token != NULL) {
        if (is_register(token)) {
            // Register token
            tokens[*token_count].type = TOKEN_REGISTER;
            tokens[*token_count].reg = get_register(token);  // Convert register string to numeric value
        } else if (is_immediate(token)) {
            // Immediate value token
            tokens[*token_count].type = TOKEN_IMMEDIATE;
            tokens[*token_count].val = get_immediate(token);  // Convert immediate string to numeric value
        } else {
            // Opcode token
            tokens[*token_count].type = TOKEN_OPCODE;
            tokens[*token_count].opcode = get_opcode(token);  // Convert opcode string to numeric value
        }

        (*token_count)++;
        token = strtok(NULL, " ");
    }
}
