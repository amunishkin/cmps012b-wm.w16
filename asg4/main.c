// $Id: main.c,v 1.6 2013-03-03 17:16:25-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bigint.h"
#include "debugf.h"
#include "stack.h"
#include "token.h"

char *execname = NULL;
bool options = false;

bool not_enough (stack *stack, int enough) {
   DEBUGF ('m', "stack=%p, enough=%d\n", stack, enough);
   if (length_stack (stack) >= enough) return false;
   fprintf (stderr, "%s: stack empty\n", execname);
   return true;
}

void do_push (stack *stack, char *yytext) {
   DEBUGF ('m', "stack=%p, yytext=%p=\"%s\"\n", stack, yytext, yytext);
   bigint *bigint = new_string_bigint (yytext);
   push_stack (stack, bigint);
}

void do_binop (stack *stack, bigint_binop binop) {
   DEBUGF ('m', "stack=%p, binop=%p\n", stack, binop);
   if (not_enough (stack, 2)) return;
   bigint *right = pop_stack (stack);
   bigint *left = pop_stack (stack);
   bigint *answer = binop (left, right);
   push_stack (stack, answer);
   free_bigint (left);
   free_bigint (right);
}

void do_clear (stack *stack) {
   DEBUGF ('m', "stack=%p\n", stack);
   while (! is_empty_stack (stack)) {
      bigint *bigint = pop_stack (stack);
      free_bigint (bigint);
   }
}

void do_print (stack *stack) {
   DEBUGF ('m', "stack=%p\n", stack);
   if (not_enough (stack, 1)) return;
   print_bigint (peek_stack (stack, 0), stdout);
}

void do_print_all (stack *stack) {
   DEBUGF ('m', "stack=%p\n", stack);
   int length = length_stack (stack);
   for (int index = 0; index < length; ++index) {
      print_bigint (peek_stack (stack, index), stdout);
   }
}

void unimplemented (int oper) {
   printf ("%s: ", execname);
   if (isgraph (oper)) printf ("'%c' (0%o)", oper, oper);
                  else printf ("0%o", oper);
   printf (" unimplemented\n");
}

void scan_options (int argc, char **argv) {
   opterr = false;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@': set_debugflags (optarg);
                   break;
         default : fprintf (stderr, "%s: -%c: invalid option\n",
                           execname, optopt);
                   break;
      }
      options = true;
   }
}

void do_scan(token *scanner, stack *stack){
   for(;;){
      int token = scan_token(scanner);
      if(token == EOF) break;
      switch(token){
         case NUMBER: do_push(stack, peek_token(scanner)); break;
         case '+': do_binop(stack, add_bigint); break;
         case '-': do_binop(stack, sub_bigint); break;
         case '*': do_binop(stack, mul_bigint); break;
         case 'c': do_clear(stack); break;
         case 'f': do_print_all(stack); break;
         case 'p': do_print(stack); break;
         default: unimplemented(token); break;
      }
   }
}

void err_file(char *input){
   fflush(NULL);
   fprintf(stderr, "%s: %s: invalid file", execname, input);
   fflush(NULL);
   exit_status = EXIT_FAILURE;
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   execname = program_name;
   scan_options (argc, argv);
   stack *stack = new_stack ();
   int index = 1;
   if(options){
      index = 2;
   }
   token *scanner = NULL;
   if((argc == index) || (argc == index && options)){
      scanner = new_token(stdin);
      do_scan(scanner, stack);
   }else{
      for(; index < argc; index++){
         FILE *input = fopen(argv[index], "r");
         if(input == NULL){
            err_file(argv[index]);
            break;
         }
         scanner = new_token(input);
         do_scan(scanner, stack);
      }
   }
   free_stack(stack);
   free_token(scanner);
   return exit_status;
}
