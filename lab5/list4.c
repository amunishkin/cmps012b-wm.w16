// $Id: list4.c,v 1.25 2013-02-12 17:56:17-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   char *word;
   node *link;
};

int main (int argc, char **argv) {
   node *head = NULL;
   for (int argi = 0; argi < argc; ++argi) {
      node *node = malloc (sizeof (struct node));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }
   for (node *curr = head; curr != NULL; curr = curr->link) {
      printf ("%p->node {word=%p->[%s], link=%p}\n",
              curr, curr->word, curr->word, curr->link);
   }
   while(head != NULL){
      node *tmp = head;
      head = head->link;
      free(tmp);
   }
   return EXIT_SUCCESS;
}
