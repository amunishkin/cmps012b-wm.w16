// $Id: lsort.c,v 1.5 2013-02-19 19:40:41-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>

// Used for function exit status.
#define FAILURE 1;
#define SUCCESS 0;

// Create new data structure.
typedef struct node node;
typedef char *cstring;

struct node{
   cstring line;
   node *link;
};

node *head = NULL;
node *curr = NULL;
node *prev = NULL;
bool failure = false;

void push(cstring buffer){
   if(head == NULL){
      head = malloc(sizeof (struct node));
      assert (head != NULL);
      head->line = strdup (buffer);
      assert (head->line != NULL);
      head->link = NULL;
   }else{
      // Find intersection point
      for(curr = head; curr != NULL;){
         if(strcmp(curr->line, buffer) >= 0){
            break;
         }
         prev = curr;
         curr = curr->link;
      }
      // Create the new placeholder
      node *tmp = malloc(sizeof (struct node));
      assert (tmp != NULL);
      tmp->line = strdup (buffer);
      assert (tmp->line != NULL);
      tmp->link = curr;
      if(prev == NULL){
         head = tmp;
      }else{
         prev->link = tmp;
      }
   }
}

int error_check(void){
   if(failure != 0){
      return FAILURE;
   }else{
      return SUCCESS;
   }
}

int main(int argc, char **argv){
   char *progname = argv[0];
   char buffer[72];
   int opt = getopt(argc, argv, "-d");
   // Pushing numbers onto a list.
   int linenr;
   for(linenr = 1; ; ++linenr){
      cstring gotline = fgets(buffer, sizeof(buffer), stdin);
      if(gotline == NULL){
         break;
      }
      else{
         push(buffer);
      }
      cstring nlpos = strchr (buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }else {
         fprintf (stderr, "%s: %d: unterminated line: %s\n",
               progname, linenr, buffer);
         failure = true;
      }
   }
   if(opt == 'd'){
      // Print out in debug format
      printf("&head = [%p]\n", &head);
      printf("head = [%p]\n", head);
      for(node *pointer = head; pointer != NULL;
            pointer = pointer->link){
         printf("[%p] -> struct node {item= [%s], link= [%p]}\n",
               pointer, pointer->line, pointer->link);
      }
      printf("NULL = [%p]\n", NULL);
   }else{
      // Print out sorted numbers.
      for(node *pointer = head; pointer != NULL;
            pointer = pointer->link){
         cstring line = pointer->line;
         printf("%s\n", line);
      }
   }
   // Free all nodes in list
   while(head != NULL){
      node *old = head;
      cstring old_string = head->line;
      head = head->link;
      free(old);
      free(old_string);
   }
   // Exit status
   return error_check();
}
