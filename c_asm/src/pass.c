#include "pass.h"
#include "label.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Label label_table[MAX_LABELS];
int label_count = 0;

int get_label_address(const char *label){
  for (int i = 0; i < label_count; i++){
    if (strcmp(label_table[i].name, label) == 0){
      return label_table[i].address;
    }
  }
  return -1;
}

void first_pass(char *assembly_code){
  int address = 0;
  char* token = strtok(assembly_code, " \n\r\t,");


  while (token != NULL) {

    #ifdef DEBUG
    printf("first_pass() current tokens: %s \n", token);
    #endif

    // Check wether the token is a label or not
    if(token[strlen(token) - 1] == ':'){
      // Remove the ':' from the label
      token[strlen(token) - 1] = '\0';

      // Add the labal to the label table
      strcpy(label_table[label_count].name, token);
      label_table[label_count].address = address;
      label_count++;
    }else if (token[0] == '#') {
      // Now it is a value, which means it is 16-bit, so increment the address twice
      address += 2;
      printf("Number value registered; address will be incremented by 2\n");
    }
    else{
      // Otherwise its an instruction, so increment the address
      address++;
    }

    token = strtok(NULL, " \n\r\t,");
  }
}

void second_pass(char *assemblyCode, char *outputCode) {
    char *token = strtok(assemblyCode, " \n");
    
    while (token != NULL) {
        if (strcmp(token, "JMP") == 0) {
            // Next token will be the label name
            token = strtok(NULL, " \n\t\r,");
            int address = get_label_address(token);
            if (address != -1) {
                // Convert label to the actual address
                sprintf(outputCode + strlen(outputCode), "JMP %d\n", address);
            } else {
                printf("Error: Undefined label %s\n", token);
            }
        } else if (token[0] == '#') {
            // Handle immediate values (numbers) indicated by '#'
            int number = atoi(token + 1); // Convert the number string to integer (skip '#')
            sprintf(outputCode + strlen(outputCode), "%d ", number);  // Write as hex
        } else if (token[strlen(token) - 1] != ':') {
            // Handle other instructions normally (without labels)
            strcat(outputCode, token);
            strcat(outputCode, " ");
        }
        
        token = strtok(NULL, " \n\t\r,");
    }
}
