// $Id: crpn.c,v 1.4 2013-01-24 18:08:35-08 - - $
//
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)
//
// NAME
//    crpn - implements Reverse Polish notation calculator.
//
// SYNOPSIS
//    crpn
//
// DESCRIPTION
//    Uses ANSI C99 to make use of a stack data structure implemented
//    as an array. Input will be read using scanf and output printed
//    with printf.
//
// NOTES
//    Only numbers and the operators '+', '-', '*', '/', '#', '@', and
//    ';' are valid input.
//

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY (-1)
#define SIZE 16
struct stack {
   int top;
   double numbers[SIZE];
};

/*
  #define DEBUG(FMT,...) { \
           fprintf (stderr, "%s[%d]: %s (" FMT ")\n", \
                    __FILE__, __LINE__, __func__, __VA_ARGS__); \
        }
*/

void err_operator (char *err_oper) {
   //DEBUG ("operator='%s'", err_oper);
   printf("%d : invalid Operator\n", err_oper[0]);  
}

void push (struct stack *stack_ptr, double number) {
   //DEBUG ("stack=%p, top=%d, number=%.15g",
   //       stack_ptr, stack_ptr->top, number);
   if(stack_ptr->top >= SIZE - 1){
      printf("%.2f : stack underflow\n", number);
   }else{
      stack_ptr->numbers[++stack_ptr->top] = number;
   }
}

void do_binop (struct stack *stack_ptr, char operator) {
   //DEBUG ("stack=%p, top=%d, operator='%c'",
   //       stack_ptr, stack_ptr->top, operator);
   if(stack_ptr->top < 1){
      printf("%d : stack underflow\n", operator);
   }else{
      double right = stack_ptr->numbers[stack_ptr->top--];
      double left = stack_ptr->numbers[stack_ptr->top--];
      switch(operator){
         case '+': push(stack_ptr, left + right); break;
         case '-': push(stack_ptr, left - right); break;
         case '*': push(stack_ptr, left * right); break;
         case '/': push(stack_ptr, left / right); break;
      }
   }
}

void do_print (struct stack *stack_ptr) {
   //DEBUG ("stack=%p, top=%d", stack_ptr, stack_ptr->top);
   if(stack_ptr->top == EMPTY){
      printf("stack is empty\n");
   }else{
      for(int pos = 0; pos <= stack_ptr->top; ++pos){
         printf("%.2f\n", stack_ptr->numbers[pos]);
      }
   }
}

void do_clear (struct stack *stack_ptr) {
   //DEBUG ("stack=%p, top=%d", stack_ptr, stack_ptr->top);
   stack_ptr->top = EMPTY;
}

void do_operator (struct stack *stack_ptr, char operator) {
   //DEBUG ("stack=%p, top=%d, operator='%c'",
   //       stack_ptr, stack_ptr->top, operator);
   char operator_array[1];
   switch(operator){
       case '+': do_binop(stack_ptr, '+');      break;
       case '-': do_binop(stack_ptr, '-');      break;
       case '*': do_binop(stack_ptr, '*');      break;
       case '/': do_binop(stack_ptr, '/');      break;
       case ';': do_print(stack_ptr);           break;
       case '@': do_clear(stack_ptr);           break;
       default : operator_array[0] = operator;
                 err_operator(operator_array);  break;
   }
}

int main (int argc, char **argv) {
   if (argc != 1) {
      fprintf (stderr, "Usage: %s\n", basename (argv[0]));
      exit (EXIT_FAILURE);
   }
   struct stack stack;
   stack.top = EMPTY;
   char buffer[1024];
   for (;;) {
      int scanrc = scanf ("%1023s", buffer);
      if (scanrc == EOF) break;
      assert (scanrc == 1);
      if (buffer[0] == '#') {
         scanrc = scanf ("%1023[^\n]", buffer);
         continue;
      }
      char *endptr;
      double number = strtod (buffer, &endptr);
      if (*endptr == '\0') {
         push (&stack, number);
      }else if (buffer[1] != '\0') {
         err_operator (buffer);
      }else {
         do_operator (&stack, buffer[0]);
      }
   }
   return EXIT_SUCCESS;
}

