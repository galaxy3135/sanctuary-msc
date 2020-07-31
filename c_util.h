#pragma once
#include "stdio.h"
#ifndef END_OF_CHAR
#define END_OF_CHAR '\0'
#endif // !END_OF_CHAR
int char_length_of(const char* chars);
int read_text_file(const char* file, char* container);
char* read_text_file(const char* file);



