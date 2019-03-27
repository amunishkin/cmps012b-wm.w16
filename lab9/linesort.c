// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "inssort.h"

int main(void){
   char *array[1000];
   int size = 0;
   for(; size < 1000; size++){
      char buffer[1000];
      char *status = fgets(buffer, 1000, stdin);
      if(status == NULL) break;
      array[size] = strdup(buffer);
      assert(array[size] != NULL);
      for(int i = 0; i < 1000; i++){
         if(array[size][i] == '\n'){
            array[size][i] = '\0';
            break;
         }
      }
   }
   size_t array_size = size;
   inssort(array, array_size, sizeof array[0], strstrcmp);
   for(int i = 0; i < size; i++){
      printf("%s\n", array[i]);
      free(array[i]);
   }
   return EXIT_SUCCESS;
}
