// $Id: stack.c,v 1.6 2013-03-03 17:16:25-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "bigint.h"

typedef struct stack_node stack_node;

static char *stack_tag = "struct stack";
static char *stack_node_tag = "struct stack_node";

struct stack {
   char *tag;
   size_t length;
   stack_node *top;
};

struct stack_node {
   char *tag;
   stack_item item;
   stack_node *link;
};

stack *new_stack (void) {
   stack *stack = malloc (sizeof (struct stack));
   assert (stack != NULL);
   stack->tag = stack_tag;
   stack->length = 0;
   stack->top = NULL;
   return stack;
}

void free_stack (stack *stack) {
   assert (is_stack (stack));
   while(stack->top != NULL){
      stack_node *old = stack->top;
      stack->top = stack->top->link;
      old->tag = NULL;
      free_bigint(old->item);
      free(old);
      stack->length--;
   }
   assert (is_empty_stack (stack));
   memset (stack, 0, sizeof stack);
   free (stack);
}

void push_stack (stack *stack, stack_item item) {
   assert (is_stack (stack));
   stack_node *tmp = malloc(sizeof(struct stack_node));
   assert(tmp != NULL);
   tmp->tag = stack_node_tag;
   if(stack->top == NULL){
      stack->top = tmp;
      stack->top->item = item;
      stack->top->link = NULL;
   }else{
      tmp->link = stack->top;
      stack->top = tmp;
      tmp->item = item;
   }
   stack->length++;
}

stack_item pop_stack (stack *stack) {
   assert (is_stack (stack));
   assert (! is_empty_stack (stack));
   stack_item item = stack->top->item;
   stack_node *old = stack->top;
   old->tag = NULL;
   stack->top = stack->top->link;
   free(old);
   stack->length--;
   return item;
}

stack_item peek_stack (stack *stack, int index) {
   assert (is_stack (stack));
   assert (index >= 0);
   assert (index < length_stack (stack));
   stack_node *curr = stack->top;
   for(int i = 0; i < index; i++) curr = curr->link;
   return curr->item;
}

bool is_empty_stack (stack *stack) {
   assert (is_stack (stack));
   return length_stack (stack) == 0;
}

int length_stack (stack *stack) {
   assert (is_stack (stack));
   return stack->length;
}

bool is_stack (stack *stack) {
   return stack != NULL && stack->tag == stack_tag;
}

