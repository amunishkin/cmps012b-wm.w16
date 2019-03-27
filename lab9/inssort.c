// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "inssort.h"

int doublecmp(const void *this, const void *that){
   double *thisdouble = (double*) this;
   double *thatdouble = (double*) that;
   return *thisdouble < *thatdouble ? -1 : *thisdouble > *thatdouble
                                    ? +1 : 0;
}

int strstrcmp(const void *this, const void *that){
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp(*thisstr, *thatstr);
}

void inssort(void *base, size_t nelem, size_t size,
             int (*compar) (const void *, const void *)){
   char *addre_base;
   addre_base = (char*) base;
   char *copy = malloc(size);
   assert(copy != NULL);
   for(unsigned int sorted = 1; sorted < nelem; ++sorted){
      char *slot_ptr = addre_base + (sorted * size);
      copy = memcpy(copy, slot_ptr, size);
      for(; slot_ptr > addre_base;){
         int cmp = (*compar) (copy, slot_ptr - size);
         if(cmp > 0) break;
         slot_ptr = memcpy(slot_ptr, slot_ptr - size, size);
         slot_ptr = slot_ptr - size;
      }
      slot_ptr = memcpy(slot_ptr, copy, size);
   }
   free(copy);
}
