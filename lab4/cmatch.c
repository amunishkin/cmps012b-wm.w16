// 
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)
//
// NAME
//    cmatch - print matching lines from files
//
// SYNOPSIS
//    cmatch [-iln] string [filename...]
//
// DESCRIPTION
//    cmatch searches the named input files for lines containing the
//    string. By default the matching lines are printed. If more than
//    one file is specified, lines of output are preceded by the 
//    filename.
//

#define _GNU_SOURCE

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// See man -s 3 strstr (UNIX)
// For finding string match in a larger string.
char *strstr(const char *haystack, const char *needle);
char *strcasestr(const char *haystack, const char *needle);

// Global strings for easy access
char *filename = "";
char *readLine = "";

// Condtion: filecount
int filecount = 0;

// For stdin and stderr
char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

// Condition codes
struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
   bool selected;
};

// Checking the user input for condition code specifiation
void scan_options (int argc, char **argv, struct options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opts->selected = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
      case 'i':
         opts->ignore_case = true;
         opts->selected = true;
         break;
      case 'l':
         opts->filenames_only = true;
         opts->selected = true;
         break;
      case 'n':
         opts->number_lines = true;
         opts->selected = true;
         break;
      default:
         exit_status = EXIT_FAILURE;
         fflush (NULL);
         fprintf (stderr, "%s: -%c: invalid option\n",
               program_name, optopt);
         break;
      }
   }
}

// Extract lines from file or stdin.
// Then print the filename if -l
// or print the line number (if -n) and 
// the whole line where string is matched.
void catbyline (FILE *input, struct options opts, char *string) {
   // For printing line numbers.
   int linecount = 0;   
   char buffer[1024];
   for (;;) {
      ++linecount;
      char *line = fgets (buffer, sizeof buffer, input);
      if (line == NULL) break;
      // -i condition
      if(opts.ignore_case){
         readLine = strcasestr(line, string);
      }else{
         readLine = strstr(line, string);
      }
      // Match found? yes = printline
      if(readLine != NULL){
         // -l condition 
         if(opts.filenames_only){
            printf("%s\n", filename);
            return;
            // End: run only once for file print.
         }else{
            if(filecount >= 2){
               printf("%s:", filename);
            }
            // -n condition
            if(opts.number_lines){
               printf("%d:", linecount);
            }
            printf("%s\n", line);
         }
      }
   }
   linecount = 0;
}

int main (int argc, char **argv) {
   struct options opts;
   program_name = basename (argv[0]);
   scan_options (argc, argv, &opts);
   int start = 1;
   if(opts.selected){
      start++;
   }
   char *string = "";
   string = argv[start];
   filecount = argc - start - 1;
   if(argc == 1){
      printf("Usage: cmatch [-iln] string [filename...]\n");
   }
   if (argc == 2) {
      catbyline (stdin, opts, string);
   }else {
      for (int argi = ++start; argi < argc; ++argi) {
         filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, opts, string);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbyline (input, opts, string);
               fclose (input);
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                     filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
   return exit_status;
}
