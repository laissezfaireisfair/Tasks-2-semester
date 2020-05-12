#pragma once
#include <stdlib.h>
#include "Errors.h"
#include "String.h"
#include "List.h"

typedef struct _Dictionary {
  List * body;
  unsigned int size;
} Dictionary;

unsigned int hash(String const str);

error init_dictionary(Dictionary *this);

error delete_dictionary(Dictionary *this);

error add_to_dict(Dictionary *this, String const entry);

error is_entry_contained(Dictionary const *this, String const entry, int *out);
