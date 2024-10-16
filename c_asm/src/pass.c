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


void first_pass(char *assembly_code, int addr){
  int address = addr;
  char* token = strtok(assembly_code, " \n\r\t,");


  while (token != NULL) {

    // Check wether the token is a label or not
    if(token[strlen(token) - 1] == ':'){
      // Remove the ':' from the label
      token[strlen(token) - 1] = '\0';

      // Add the labal to the label table
      strcpy(label_table[label_count].name, token);
      label_table[label_count].address = address;
      label_count++;

    } else if (token[0] == ':') {
      // Now it's not a label but a reference to a label
      token[0] = '\0';

      address += 2; 
    }
    else if (token[0] == '#') {
      // Now it is a value, which means it is 16-bit, so increment the address twice
      address += 2;
    }
    else{
      // Otherwise its an instruction, so increment the address
      address++;
    }
    


    printf("first_pass:() Current address: 0x%04x\n", address);
    token = strtok(NULL, " \n\r\t,");
  }
}

void second_pass(char *assemblyCode, char *outputCode) {
    char *token = strtok(assemblyCode, " \n");
    char instruction[3];

    while (token != NULL) {
        if (strcmp(token, "JMP") == 0 || strcmp(token, "JSR") == 0 || 
            strcmp(token, "BEQ") == 0 || strcmp(token, "BNQ") == 0 || 
            strcmp(token, "BLT") == 0 || strcmp(token, "BGT") == 0 || 
            strcmp(token, "BLQ") == 0 || strcmp(token, "BGQ") == 0) {

            // Save the Opcode
            strcpy(instruction, token);

            // Handle jump or branch instructions
            token = strtok(NULL, " \n\t\r,");
            if (token[0] == ':') {
                // This token indicates a label reference
                token++; // Skip the ':' character
                int address = get_label_address(token);  // Get the address for the label
                if (address != -1) {
                    // If address is valid, append the instruction and address to outputCode
                    sprintf(outputCode + strlen(outputCode), "%s %d ", instruction, address);
                } else {
                    printf("Error: Undefined label %s\n", token);
                }
            } else {
                // Handle case where the token is not a label reference (it might be a direct label name)
                int address = get_label_address(token); // This assumes token is now the label name
                if (address != -1) {
                    // If address is valid, append the instruction and address to outputCode
                    sprintf(outputCode + strlen(outputCode), "%s %d ", token, address);
                } else {
                    printf("Error: Undefined label %s\n", token);
                }
            }
        } else if (token[0] == '#') {
            // Handle immediate values (numbers) indicated by '#'
            int number = atoi(token + 1); // Convert the number string to integer (skip '#')
            sprintf(outputCode + strlen(outputCode), "%d ", number);  // Write as decimal or hex if needed
        } else if (token[strlen(token) - 1] != ':') {
            // Handle other instructions normally (without labels)
            strcat(outputCode, token);
            strcat(outputCode, " ");
        }

        token = strtok(NULL, " \n\t\r,");
    }
}
