#pragma once
#include <stdlib.h>

typedef struct _Constants {
  unsigned int MAX_VERTEX;
  unsigned int MAX_EDGES;
  unsigned int MAX_INT;
  char const  *INPUT_FILENAME;
  char const  *OUTPUT_FILENAME;
  char const  *ERROR_FILENAME;
} Constants;

Constants get_constants();
