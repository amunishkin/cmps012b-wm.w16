// $Id: futuretimes.c,v 1.16 2013-02-26 19:04:24-08 - - $

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const time_t localtime_segfault = (time_t)INT_MAX * 365 * 24 * 60 * 60;

int main (void) {
   printf ("sizeof (time_t)    = %20ld\n", sizeof (time_t));
   printf ("INT_MAX            = %20d\n", INT_MAX);
   printf ("LONG_MAX           = %20ld\n", LONG_MAX);
   printf ("localtime_segfault = %20ld\n", localtime_segfault);
   for (time_t when = 1; when > 0; when = when * 2 + 1) {
      if (when > localtime_segfault) break;
      char *timeformat = "%11Y %b %d %a %H:%M:%S %Z";
      char buffer[256];
      struct tm *tm = localtime (&when);
      strftime (buffer, sizeof buffer, timeformat, tm);
      printf ("%18ld = %s\n", when, buffer);
   }
   return EXIT_SUCCESS;
}

