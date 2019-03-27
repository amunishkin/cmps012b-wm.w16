// $Id: debugf.c,v 1.2 2013-02-28 14:13:14-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugf.h"

static char *debugflags = "";
static bool alldebugflags = false;
char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

void __stubprintf (char *filename, int line, const char *func,
                   char *format, ...) {
   va_list args;
   fflush (NULL);
   assert (program_name != NULL);
   fprintf (stdout, "%s: STUB: %s[%d] %s:\n",
            program_name, filename, line, func);
   va_start (args, format);
   vfprintf (stdout, format, args);
   va_end (args);
   fflush (NULL);
}

void set_debugflags (char *flags) {
   debugflags = flags;
   if (strchr (debugflags, '@') != NULL) alldebugflags = true;
   DEBUGF ('a', "Debugflags = \"%s\"\n", debugflags);
}

void __debugprintf (char flag, char *file, int line, const char *func,
                    char *format, ...) {
   va_list args;
   if (alldebugflags || strchr (debugflags, flag) != NULL) {
      fflush (NULL);
      assert (program_name != NULL);
      fprintf (stderr, "%s: DEBUGF(%c): %s[%d]: %s()\n",
               program_name, flag, file, line, func);
      va_start (args, format);
      vfprintf (stderr, format, args);
      va_end (args);
      fflush (NULL);
   }
}

