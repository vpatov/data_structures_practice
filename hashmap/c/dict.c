#include "dict.h"


void initialize_dictionary_default(struct dictionary *dict){
  initialize_dictionary(dict, DEFAULT_DICT_SIZE);
}

void initialize_dictionary(struct dictionary *dict, uint32_t capacity){
  dict->capacity = capacity;
  dict->used_buckets = 0;
  dict->buckets = calloc(sizeof(struct bucket), dict->capacity);
  dict->num_items = 0;
}

void rehash_dictionary(struct dictionary *dict){
  uint32_t current_capacity, new_capacity;
  struct bucket *bin, *current_buckets;
  struct ll_node *node;

  current_capacity = dict->capacity;
  current_buckets = dict->buckets;
  new_capacity = dict->capacity * 3.5;

  initialize_dictionary(dict, new_capacity);

  for (uint32_t i = 0; i < current_capacity; i++){
    bin = current_buckets + i;
    node = bin->head;
    while (node != NULL){
      add_entry(dict,node->key,node->val);
      node = node->next;
    }
  }
  free(current_buckets);
}


// void teardown_dictionary(struct dictionary *dict){

// }

// Taken from https://stackoverflow.com/a/7666577
uint32_t hash(char *str){
    uint32_t hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


void add_entry(struct dictionary *dict, char* key, void* val){
  uint32_t hash_val = hash(key);
  size_t bucket_index = hash_val % dict->capacity;
  struct bucket* bin = dict->buckets + bucket_index;
  struct ll_node *node = bin->head;
  struct ll_node *tail = bin->head;

  // look through nodes and find existing key
  if (bin->num_items){
    while (node != NULL){
      if (strcmp(key,node->key) == 0){
        node->val = val;
        return;
      }
      tail = node;
      node = node->next;
    }
  }

  struct ll_node *new_node = calloc(sizeof(struct ll_node), 1);
  new_node->key = key;
  new_node->val = val;
  new_node->next = NULL;
  bin->num_items++;
  dict->num_items++;

  if (tail != NULL){
    tail->next = new_node;
  }
  else {
    bin->head = new_node;
    dict->used_buckets++;
  }

  if ((double)dict->num_items / dict->capacity > DEFAULT_LOAD_FACTOR){
    rehash_dictionary(dict);
  }

}



void* get_entry(struct dictionary *dict, char* key){
  uint32_t hash_val = hash(key);
  size_t bucket_index = hash_val % dict->capacity;
  struct bucket *bin = dict->buckets + bucket_index;
  struct ll_node *node = bin->head;

  if (bin->num_items){
    while (node != NULL){
      if (strcmp(key,node->key) == 0){
        return node->val;
      }
      node = node->next;
    }
  }
  return NULL;
}

void remove_entry(struct dictionary *dict, char* key){
  uint32_t hash_val = hash(key);
  size_t bucket_index = hash_val % dict->capacity;
  struct bucket *bin = dict->buckets + bucket_index;
  struct ll_node *node = bin->head;
  struct ll_node *prev = NULL;

  if (bin->num_items){
    while (node != NULL){
      if (strcmp(key,node->key) == 0){
        if (prev != NULL) {
          free(prev->next);
          prev->next = node->next;
        }
        else {
          free(bin->head);
          bin->head = node->next;  
        }
        bin->num_items--;
        dict->num_items--;
        if (bin->head == NULL){
          dict->used_buckets--;
        }
        return;
      }
      prev = node;
      node = node->next;
    }
  }
}

void iterate_dictionary(struct dictionary* dict, void (*f)(char*, void*)) {
  struct bucket *bin;
  struct ll_node *node;

  for (uint32_t i = 0; i < dict->capacity; i++){
    bin = dict->buckets + i;
    node = bin->head;
    while (node != NULL){
      f(node->key, node->val);
      node = node->next;
    }
  }
}

void print_key_val(char* key, void* val){
  printf("%s: %s\n", key, ((char*) val));
}

void generate_random_string(char *dest, int length){
  char *ptr = dest;
  for (; ptr < (dest + length - 1); ptr++){
    *ptr = (rand() % 26) + 'a';
  }
  *ptr = '\0';
}

void test_dict(struct dictionary *dict){
  int TEST_SIZE = 1000;
  int KEY_LEN = 10;
  int VAL_LEN = 20;
  char *key, *val;
  char *keys = calloc(TEST_SIZE, sizeof(char) * KEY_LEN);
  char *vals = calloc(TEST_SIZE, sizeof(char) * VAL_LEN);

  // generate random data and insert into dict
  for (int i = 0; i < TEST_SIZE; i++){
    key = keys + (i*KEY_LEN);
    val = vals + (i*VAL_LEN);
    generate_random_string(key, KEY_LEN);
    generate_random_string(val, VAL_LEN);
    add_entry(dict, key, val);
  }

  // get each entry, assert equality
  // remove each entry
  for (int i = TEST_SIZE - 1; i >= 0; i--){
    key = keys + (i*KEY_LEN);
    val = vals + (i*VAL_LEN);
    char* retval = get_entry(dict, key);
    if (strcmp(val, retval) != 0){
      printf("strcmp unequal for %s.\n\tExpected: %s\n\tActual:   %s\n", key,  val, retval);
    }
    remove_entry(dict, key);
  }
  free(keys);
  free(vals);
}



int main () {
  struct dictionary dict;
  srand(1);
  initialize_dictionary(&dict, DEFAULT_DICT_SIZE);
  for (long i = 0; i < 10000; i++){
    test_dict(&dict);
  }
}

