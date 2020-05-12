#include "Dictionary.h"

unsigned int count_hash(String const str) {
  unsigned int sumASII = 0;
  for (unsigned int i = 0; i < str.length; ++i)
    sumASII += str.body[i];
  return sumASII / str.length;
}

error init_dictionary(Dictionary *this) {
  if (this == NULL)
    return NULL_POINTER;
  this->size = 128; // Range of hash is [0, 127]
  this->body = (List*)malloc(sizeof(List) * this->size);
  if (this->body == NULL)
    return RUNTIME_ERROR;
  for (unsigned int i = 0; i < this->size; ++i)
    this->body[i] = make_list();
  return OK;
}

void delete_dictionary(Dictionary *this) {
  for (unsigned int i = 0; i < this->size; ++i)
    delete_list(&this->body[i]);
  free(this->body);
}

error add_to_dict(Dictionary *this, String const entry) {
  if (this == NULL)
    return NULL_POINTER;
  if (entry.length == 0)
    return INVALID_ARGUMENT;

  unsigned int const hash = count_hash(entry);
  if (hash > 127)
    return INVALID_ARGUMENT;

  push_front(&this->body[hash], entry);
  return OK;
}

error is_entry_contained(Dictionary const *this, String const entry, int *out) {
  if (this == NULL || out == NULL)
    return NULL_POINTER;
  if (entry.length == 0)
    return INVALID_ARGUMENT;

  unsigned int const hash = count_hash(entry);
  if (hash > 127)
    return INVALID_ARGUMENT;

  for (ListElem *i = this->body[hash].head; i != NULL; i = i->next) {
    int areEqual;
    error const cmpStatus = compare_string(&entry, &i->value, &areEqual);
    if (cmpStatus != OK)
      return cmpStatus;
    if (areEqual) {
      *out = 1;
      return OK;
    }
  }

  *out = 0;
  return OK;
}
