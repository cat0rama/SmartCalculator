#ifndef PARSER_H
#define PARSER_H

#include "defines.h"

enum eError parse_string(const char* string);

double get_number(const char** string);

#endif
