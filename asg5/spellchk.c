// $Id: spellchk.c,v 1.4 2013-03-14 19:34:01-07 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>

#include "debugf.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
#define DEFAULT_DICTNAME "/usr/share/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2

#define EXIT_FAILURE_WD  1
#define EXIT_FAILURE_RUN 2

int again = 0;

void print_error (char *object, char *message) {
   fflush (NULL);
   fprintf (stderr, "%s: %s: %s\n", Exec_Name, object, message);
   fflush (NULL);
   Exit_Status = EXIT_FAILURE_RUN;
}

FILE *open_infile (char *filename) {
   FILE *file = fopen (filename, "rb");
   if (file == NULL) print_error (filename, strerror (errno));
   DEBUGF ('m', "filename = \"%s\", file = %p\n", filename, file);
   return file;
}

void spellcheck (char *filename, hashset *hashset) {
   yylineno = 1;
   DEBUGF ('m', "filename = \"%s\", hashset = %p\n",
         filename, hashset);
   for (;;) {
      int token = yylex ();
      if (token == 0) break;
      DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
      // Look up word in dictionary
      
         if(!has_hashset(hashset, yytext)){
            char text[strlen(yytext)];
            for(unsigned int i = 0; i < strlen(yytext); i++){
               if(i == strlen(yytext)) text[i] = '\0';
               text[i] = tolower(yytext[i]);
            }
            if(!has_hashset(hashset, text)){
               printf("-: %d: %s\n", yylineno, yytext);
               Exit_Status = EXIT_FAILURE_WD;
            }
         }
      
   }
}

void load_dictionary (char *dictionary_name, hashset *hashset) {
   if (dictionary_name == NULL) return;
   DEBUGF ('m', "dictionary_name = \"%s\", hashset = %p\n",
         dictionary_name, hashset);
   FILE *dict = open_infile(dictionary_name);
   if(dict == NULL){
      print_error(dictionary_name, strerror(errno));
      return;
   }
   for(;;){
      char buff[64];
      char *status = fgets(buff, 64, dict);
      if(status == NULL) break;
      // Remove '\n'
      for(int i = 0; i < 64; i++){
         if(buff[i] == '\n'){
            buff[i - 1] = '\0';
            break;
         }
      }
      char *word = strdup(buff);
      assert(word != NULL);
      put_hashset(hashset, word);
   }
   fclose(dict);
}

int main (int argc, char **argv) {
   Exec_Name = basename (argv[0]);
   char *default_dictionary = DEFAULT_DICTNAME;
   char *user_dictionary = NULL;
   hashset *hashset = new_hashset ();
   yy_flex_debug = false;
   bool print_hash = false;

   // Scan the arguments and set flags.
   opterr = false;
   for (;;) {
      int option = getopt (argc, argv, "nxyd:@:");
      if (option == EOF) break;
      switch (option) {
      char optopt_string[16]; // used in default:
      case 'd': user_dictionary = optarg;
      break;
      case 'n': default_dictionary = NULL;
      break;
      case 'x': print_hash = true;
           again++;
      break;
      case 'y': yy_flex_debug = true;
      break;
      case '@': set_debugflags (optarg);
      if (strpbrk (optarg, "@y")) yy_flex_debug = true;
      break;
      default : sprintf (optopt_string, "-%c", optopt);
      print_error (optopt_string, "invalid option");
      break;
      }
   }

   // Load the dictionaries into the hash table.
   load_dictionary (default_dictionary, hashset);
   load_dictionary (user_dictionary, hashset);

   // Debugging about hash table.
   if(print_hash) print_hashfn(hashset);
   if(again >= 2) print_hashfn_full(hashset);
   print_debugf_words(hashset); 

   if(!again){
   // Read and do spell checking on each of the files.
      if (optind >= argc) {
         yyin = stdin;
         spellcheck (STDIN_NAME, hashset);
      }else {
         for (int fileix = optind; fileix < argc; ++fileix) {
            DEBUGF ('m', "argv[%d] = \"%s\"\n", fileix, argv[fileix]);
            char *filename = argv[fileix];
            if (strcmp (filename, STDIN_NAME) == 0) {
               yyin = stdin;
               spellcheck (STDIN_NAME, hashset);
            }else {
               yyin = open_infile (filename);
               if (yyin == NULL) continue;
               spellcheck (filename, hashset);
               fclose (yyin);
            }
         }
      }
   }
   free_hashset (hashset);
   yycleanup ();
   return Exit_Status;
}

