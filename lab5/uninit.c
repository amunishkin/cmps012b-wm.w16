// $Id: uninit.c,v 1.1 2013-02-12 15:24:47-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int foo;
   printf ("%d\n", foo);
   int *pointer;
   printf ("%d\n", *pointer);
}
