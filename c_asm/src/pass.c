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
    }else if (token[0] == '#') {
      // Now it is a value, which means it is 16-bit, so increment the address twice
      address += 2;
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
            sprintf(outputCode + strlen(outputCode), "JMP %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BEQ") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BEQ %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BNQ") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BNQ %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BLT") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BLT %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BGT") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BGT %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BLQ") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BLQ %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BGQ") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BGQ %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BOC") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BOC %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "BOS") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "BOS %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (strcmp(token, "JSR") == 0) {
          // Next token will be the label name
          token = strtok(NULL, " \n\t\r,");
          int address = get_label_address(token);
          if (address != -1) {
            // Convert label to the actual address
            sprintf(outputCode + strlen(outputCode), "JSR %d ", address);
          } else {
            printf("Error: Undefined label %s\n", token);
          }
        } 
        else if (token[0] == '#') {
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
