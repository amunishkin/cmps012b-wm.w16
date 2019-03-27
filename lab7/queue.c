// $Id: queue.c,v 1.42 2013-02-28 18:37:25-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

static char *queue_tag = "struct queue";
static char *queue_node_tag = "struct queue_node";

typedef struct queue_node queue_node;

struct queue_node {
   char *tag;
   queue_item_t item;
   queue_node *link;
};

struct queue {
   char *tag;
   queue_node *front;
   queue_node *rear;
};

queue *new_queue (void) {
   queue *tmp = malloc(sizeof(queue));
   assert(tmp != NULL);
   tmp->tag = queue_tag;
   tmp->front = NULL;
   tmp->rear = NULL;
   return tmp;
}

void free_queue (queue *this) {
   assert (is_queue (this));
   assert (isempty_queue (this));
   while(this->rear != NULL){
      queue_node *old = this->rear;
      this->rear = this->rear->link;
      free(old->item);
      free(old);
   }
   memset (this, 0, sizeof (queue));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
   assert (is_queue (this));
   queue_node *tmp = malloc(sizeof(struct queue_node));
   tmp->tag = queue_node_tag;
   tmp->item = item;
   tmp->link = NULL;
   if(this->front == NULL){
      this->front = tmp;
      this->rear = tmp;
   }else{
      tmp->link = this->front;
      this->front = tmp;
   }
}

queue_item_t remove_queue (queue *this) {
   assert (is_queue (this));
   assert (! isempty_queue (this));
   queue_node *prev = this->front;
   for(queue_node *curr = prev; curr->link->tag != NULL;){
      prev = curr;
      curr = curr->link;
      if(curr->link == NULL) break;
   }   
   this->rear->tag = NULL;
   queue_item_t _item = this->rear->item;
   if(this->front == this->rear){
      this->front = NULL;
   }else{
      this->rear = prev;
   }
   return _item;
}

bool isempty_queue (queue *this) {
   assert (is_queue (this));
   return this->front == NULL;
}

bool is_queue (queue *this) {
   return this != NULL && this->tag == queue_tag;
}

