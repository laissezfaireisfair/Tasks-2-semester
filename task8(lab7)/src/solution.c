#include <stdlib.h>
#include <stdio.h>
#include "Errors.h"
#include "String.h"
#include "Dictionary.h"

int main() {
  char const * const inputFilename  = "in.txt";
  char const * const outputFilename = "out.txt";
  char const * const errorFilename  = "err.txt"; // Case when out.txt not available
  unsigned int const maxStrLen = 255;

  Dictionary dictionary;
  init_dictionary(&dictionary);
  FILE fin = fopen(inputFilename, "r");
  if (fin == NULL) {
    print_error(outputFilename, RUNTIME_ERROR);
    delete_dictionary(&dictionary);
    return 1;
  }

  String target = make_str();
  error const readTargetStatus = ask_string(fin, &target, maxStrLen);
  if (readTargetStatus != OK) {
    print_error(outputFilename, readTargetStatus);
    delete_dictionary(&dictionary);
    fclose(fin);
    return 2;
  }

  String str = make_str();
  int fileEnd = 0;
  while (!fileEnd){
    error const readStatus = ask_string(fin, &str, maxStrLen);
    if (readStatus != OK) {
      print_error(outputFilename, readTargetStatus);
      delete_dictionary(&dictionary);
      deinit_str(&target);
      fclose(fin);
      return 3;
    }
    if (str.length == 0)
      fileEnd = 1;
    else {
      error const addStatus = add_to_dict(&dictionary, str);
      if (addStatus != OK) {
        print_error(outputFilename, addStatus);
        delete_dictionary(&dictionary);
        deinit_str(&target);
        deinit_str(&str);
        fclose(fin);
        return 4;
      }
    }
  }

  fclose(fin);
  deinit_str(&target);
  deinit_str(&str);

  int isInDictionary;
  error checkStatus = is_entry_contained(&dictionary, target, &isInDictionary);
  delete_dictionary(&dictionary);
  if (checkStatus != OK) {
    print_error(outputFilename, checkStatus);
    return 5;
  }

  FILE *fout = fopen(outputFilename, "w");
  if (fout == NULL) {
    print_error(errorFilename, RUNTIME_ERROR);
    return 6;
  }

  if (isInDictionary)
    fprintf(fout, "YES\n");
  else
    fprintf(fout, "NO\n");

  fclose(fout);
  return 0;
}
