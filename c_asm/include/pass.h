#pragma once


int get_label_address(const char *label);

void first_pass(char* assembly_code);
void second_pass(char* assembly_code, char* output_code);
