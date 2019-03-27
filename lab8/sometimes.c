// $Id: sometimes.c,v 1.11 2013-02-26 15:03:21-08 - - $

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
   time_t times[] = {INT_MIN, 0, time (NULL), INT_MAX};
   printf ("sizeof (time_t) = %ld\n", sizeof (time_t));
   for (size_t i = 0; i < sizeof times / sizeof *times; ++i) {
      char *timeformat = "%a %d %b %Y %H:%M:%S %Z";
      time_t when = times[i];
      struct tm *tm = localtime (&when);
      char buffer_local[64];
      strftime (buffer_local, sizeof buffer_local, timeformat, tm);
      char buffer_gmt[64];
      tm = gmtime (&when);
      strftime (buffer_gmt, sizeof buffer_gmt, timeformat, tm);
      printf ("%12ld = %s = %s\n",
              times[i], buffer_gmt, buffer_local);
   }
   return EXIT_SUCCESS;
}

