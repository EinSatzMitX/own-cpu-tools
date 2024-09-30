#pragma once

#include "token.h"

char * read_file(const char* name);

char * trim_file(const char* content);

void write_tokens_to_file(const char* filename, Token tokens[], int token_count);
