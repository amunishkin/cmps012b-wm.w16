// $Id: nsort.c,v 1.3 2013-02-19 19:38:07-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

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

struct node{
   double num;
   node *link;
};

node *head = NULL;
node *curr = NULL;
node *prev = NULL;
bool failure = false;

void push(double num){
   if(head == NULL){
      head = malloc(sizeof (struct node));
      assert (head != NULL);
      head->num = num;
      head->link = NULL;
   }else{
      // Find intersection point
      int cmp = 1;
      for(curr = head; curr != NULL;){
         if((cmp = curr->num) >= num){
            break;
         }
         prev = curr;
         curr = curr->link;
      }
      // Create the new placeholder
      node *tmp = malloc(sizeof (struct node));
      assert (tmp != NULL);
      tmp->num = num;
      // Make sure there isn't a mixup
      if(curr->link == head){
         tmp->link = NULL;
      }else{
         tmp->link = curr;
      }
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
   char err_buffer [256];
   char err_buf_fmt[16];
   sprintf (err_buf_fmt, "%%%lds", sizeof err_buffer - 1);
   int opt = getopt(argc, argv, "-d");
   // Pushing numbers onto a list.
   for(;;){
      double num;
      int scanvalue = scanf("%lg", &num);
      if(scanvalue == EOF){
         printf("%s: EOF\n", progname);
         break;
      }
      else if(scanvalue == 1){
         push(num);
      }
      else{
         scanvalue = scanf(err_buf_fmt, err_buffer);
         assert (scanvalue == 1);
         printf("%s: bad number\n", progname);
         failure = true;
      }
   }
   if(opt == 'd'){
      // Print out in debug format
      printf("&head = [%p]\n", &head);
      printf("head = [%p]\n", head);
      for(node *pointer = head; pointer != NULL;
            pointer = pointer->link){
         printf("[%p] -> struct node {item= [%.15g], link= [%p]}\n",
               pointer, pointer->num, pointer->link);
      }
      printf("NULL = [%p]\n", NULL);
   }else{
      // Print out sorted numbers.
      for(node *pointer = head; pointer != NULL;
            pointer = pointer->link){
         double num = pointer->num;
         printf("%24.15g\n", num);
      }
   }
   // Free all nodes in list
   while(head != NULL){
      node *old = head;
      head = head->link;
      free(old);
   }
   // Exit status
   return error_check(); 
}
