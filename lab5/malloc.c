// $Id: malloc.c,v 1.1 2013-02-12 15:33:48-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   int value;
   node *link;
};

int main (int argc, char **argv) {
   node *ptr = malloc (sizeof (struct node));
   ptr = malloc (sizeof (node));
   ptr->value = 6;
   ptr->link = NULL;
   printf ("%p-> {%d, %p}\n", ptr, ptr->value, ptr->link);
   free (ptr);
   return EXIT_SUCCESS;
}
