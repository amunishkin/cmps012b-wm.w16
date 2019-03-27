// $Id: hashset.c,v 1.3 2013-03-14 19:25:38-07 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

bool new_item = true;

struct hashset {
   size_t length;
   int load;
   char **array;
};

hashset *new_hashset (void) {
   hashset *new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   assert (new->array != NULL);
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void double_hash(hashset *hashset){
   size_t size = (2 * hashset->length) + 1;
   //printf("%d\n", (int)size);
   char **new_array = calloc(size + 1, sizeof(char*));
   assert(new_array != NULL);
   for (size_t index = 0; index < size + 1; ++index) {
      new_array[index] = NULL;
   }
   size_t old_length = hashset->length;
   char **old_array = hashset->array;
   hashset->length = size;
   hashset->array = new_array;
   
   new_item = false;
   for(unsigned int i = 0; i < old_length; i++){
      if(old_array[i] != NULL){
         put_hashset(hashset, old_array[i]);
      }
   }
   new_item = true;
   free(old_array);
   DEBUGF('h', "double hash (%p), length (%d)\n",
                hashset->array, hashset->length);
}

void free_hashset (hashset *hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   for(unsigned int i = 0; i < hashset->length; i++){
      if(hashset->array[i] != NULL){
         free(hashset->array[i]);
      }
   }
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void print_debugf_words(hashset *hashset){
   for(unsigned int i = 0; i < hashset->length; i++){
      if(hashset->array[i] != NULL)
         DEBUGF('h', "word (%s)\n", hashset->array[i]);
   }
}

void print_hashfn(hashset *hashset){
   DEBUGF('h', "print hash (%p)\n", hashset);
   int words = 0;
   int size = 1000;
   int count_cluster = 0;
   int cluster_data[size];
   bool exit_loop = false;
   for(int i = 0; i < size; i++){
      cluster_data[i] = 0;
   }
   bool cluster = true;
   for(unsigned int i = 0; i < hashset->length; i++){
      if(i == hashset->length - 1){
         i = 0;
         exit_loop = true;
      }
      if(hashset->array[i] != NULL){
         words++;
         if(exit_loop) break;
         DEBUGF('h', "item (%s)\n", hashset->array[i]);
         if(cluster){
            count_cluster++;
         }else{
            count_cluster = 1;
            cluster = true;
         }
      }else{
         cluster = false;
         if(count_cluster > 0){
            cluster_data[count_cluster]++;
         }
         count_cluster = 0;
      }
   }
   printf("%20d words in the hash set\n", words);
   printf("%20d length of the hash array\n", (int) hashset->length);
   for(int i = 0; i < size; i++){
      if(cluster_data[i] != 0){
         printf("%20d clusters of size %d\n", cluster_data[i], i);
      }
   }
}

void print_hashfn_full(hashset *hashset){
   for(unsigned int i = 0; i < hashset->length; i++){
      if(hashset->array[i] != NULL){
         char *item = hashset->array[i];
         hashcode_t hash_item = strhash(item);
         printf("array[%10d] = %12u \"%s\"\n", i, hash_item, item);
      }
   }
}

void put_hashset (hashset *hashset, char *item) {
   DEBUGF('a', "put hash (%p), item (%s), load (%d)\n",
                           hashset, item, hashset->load);
   if(new_item) hashset->load++;
   if((unsigned) hashset->load * 4 > hashset->length){
      double_hash(hashset);
   } 
   hashcode_t hash_item = strhash(item);
   int starting_index = hash_item % hashset->length;
   int i = starting_index;
   for(;;){
      i++;
      if(hashset->array[i] == NULL){
         hashset->array[i] = item;
         DEBUGF('h', "put item (%s)\n", hashset->array[i]);
         break;
      }
      if(strcmp(hashset->array[i], item) == 0){
         free(item);
         break;
      }
      
      if((unsigned) i == hashset->length-1) i = 0;
      if(i == starting_index) break;
   }
}

bool has_hashset (hashset *hashset, char *item) {
   DEBUGF('h', "has hash (%p), item (%s)\n", hashset, item);
   hashcode_t hash_item = strhash(item);
   int starting_index = hash_item % hashset->length;
   int i = starting_index;
   while(hashset->array[i] != NULL){
      if(strcmp(hashset->array[i], item) == 0) return true;
      i++;
      if((unsigned) i == hashset->length-1) i = 0;
      if(i == starting_index) break;
   }
   return false;
}

