#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));

  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(Pair *));

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // //hash the key, get index back
  // unsigned int index = hash(key, ht->capacity);
  // //create a (Pair *) from the key and value
  // Pair *pair = create_pair(key, value);
  // //see if there is already (Pair *)at the given index
  //   if (ht->storage != NULL)
  //   {
  //     Pair *stored_pair = ht->storage[index];
  //     //if there is, overwrite it and free the memory of the overwritten (Pair *)
  //     printf("Overwriting key/value pair '%s:%s with %s:%s\n", stored_pair->key, stored_pair->value, key, value);
  //     destroy_pair(stored_pair);
  //   }    
  //   //else, put the (Pair *) ther
  //   ht->storage[index] = pair;
    
  int hashIndex = hash(key, ht->capacity);

  if (ht->storage[hashIndex] == NULL)
  {
    ht->storage[hashIndex] = create_pair(key, value);
    // printf("key:%s value:%s\n", key, value); //sanity check
  }
  else
  {
    fprintf(stderr, "OverwritingIndexWarning: Index %d is already in use and will be overwritten\n", hashIndex);
    ht->storage[hashIndex] = create_pair(key, value);
    // printf("key:%s value:%s\n", key, value); //sanity check - to see if it works uncomment second hash_table_insert() in main() at the bottom
  }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // //has the given key, get an index back
  // unsigned int index = hash(key, ht->capacity);

  // //check if storage holds a pair at the given index
  // if (ht->storage[index] != NULL)
  //   //free the Pair*
  //   destroy_pair(ht->storage[index]);
  //   //NULL it out
  //   ht->storage[index] = NULL;
  
  // //else, there is nothing there, so nothing more to do

  int hashIndex = hash(key, ht->capacity);

  if (ht->storage[hashIndex] != NULL)
  {
    destroy_pair(ht->storage[hashIndex]);
    ht->storage[hashIndex] = NULL;
  }
  
  printf("RemovalWarning: Key at index %d has already been removed\n", hashIndex);
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  // //hash the key, get an index back
  //   unsigned int index = hash(key, ht->capacity);

  // //check to see if storage[index] holds a Pair*
  // if (ht->storage[index] != NULL)
  //   //if it does, return the value associated with the key
  //   {
  //     return ht-> storage[index]->value;
  //   }
  // //else return NULL
  // return NULL;

  int hashIndex = hash(key, ht->capacity);

  if (ht->storage[hashIndex] != NULL)
  {
    return ht->storage[hashIndex]->value;
  }

  printf("NULLWarning: There is not value stored at index %d\n", hashIndex);
  return NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  //Loop through every index of storage
  for (int i = 0; i < ht->capacity; i++)
  {
    //if the index holds a Pair*
    if (ht->storage[i] != NULL)
    {
      //free it
      destroy_pair(ht->storage[i]);
    }
  }
  //Free storage
  free(ht->storage);
  //Free struct
  free(ht);
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");
  
  // hash_table_insert(ht, "line", "Here tomorrow...\n"); //sanity check to see if overwriting works

  printf("%s", hash_table_retrieve(ht, "line")); //should return: Here today...

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif