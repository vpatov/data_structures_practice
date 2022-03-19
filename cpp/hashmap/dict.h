#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DEFAULT_DICT_SIZE 64
#define DEFAULT_LOAD_FACTOR 0.75

typedef struct ll_node {
  char* key;
  void* val;
  struct ll_node* next;
} ll_node;

typedef struct bucket {
  size_t num_items;
  struct ll_node* head;
} bucket;

typedef struct dictionary {
  struct bucket* buckets;
  size_t capacity;
  size_t used_buckets;
  size_t num_items;
} dictionary;

void initialize_dictionary_default(struct dictionary *dict);

void initialize_dictionary(struct dictionary *dict, uint32_t capacity);

void teardown_dictionary(struct dictionary *dict);

uint32_t hash(char *str);

void add_entry(struct dictionary *dict, char* key, void* val);

void rehash_dictionary(struct dictionary *dict);

void* get_entry(struct dictionary *dict, char* key);
void remove_entry(struct dictionary *dict, char* key);
void iterate_dictionary(struct dictionary* dict, void (*f)(char*, void*));



