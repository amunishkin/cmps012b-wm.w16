// $Id: strhash.c,v 1.1 2013-03-05 19:08:50-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "strhash.h"

hashcode_t strhash (char *string) {
   assert (string != NULL);
   hashcode_t hashcode = 0;
   for (int index = 0; string[index] != '\0'; ++index) {
      hashcode = hashcode * 31 + (unsigned char) string[index];
   }
   return hashcode;
}

