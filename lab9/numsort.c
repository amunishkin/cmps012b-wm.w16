// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <stdio.h>
#include <stdlib.h>

#include "inssort.h"

int main(void){
   double array[1000];
   int size = 0;
   for(; size < 1000; size++){
      double num;
      int status = scanf("%lg", &num);
      if(status != 1) break;
      array[size] = num;
   }
   const size_t array_size = size;
   inssort(array, array_size, sizeof *array, doublecmp);
   for(int i = 0; i < size; i++){
      printf("%20.15g\n", array[i]);
   }
   return EXIT_SUCCESS;
}
