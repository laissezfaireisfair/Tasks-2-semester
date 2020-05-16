#include <stdlib.h>
#include "Constants.h"

Constants get_constants() {
  Constants constants;
  constants.MAX_VERTEX      = 5000;
  constants.MAX_EDGES = (constants.MAX_VERTEX * (constants.MAX_VERTEX - 1)) / 2;
  constants.MAX_INT         = 2147483647;
  constants.INPUT_FILENAME  = "input.txt";
  constants.OUTPUT_FILENAME = "output.txt";
  constants.ERROR_FILENAME  = "error.txt";
  return constants;
}
