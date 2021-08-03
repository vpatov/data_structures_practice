// #define DEFAULT_DICT_SIZE 64
// #define DEFAULT_LOAD_FACTOR 0.75

// typedef struct ll_node {
//   char* key;
//   void* val;
//   struct ll_node* next;
// } ll_node;

// typedef struct bucket {
//   size_t num_items;
//   struct ll_node* head;
// } bucket;

// typedef struct dictionary {
//   struct bucket* buckets;
//   size_t capacity;
//   size_t used_buckets;
//   size_t num_items;
// } dictionary;