// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int exit_status = EXIT_SUCCESS;
char *execname = NULL;

void print_std_time(struct tm *time){
   char *timeformat = "%b %e  %Y";
   char buffer_local[64];
   strftime(buffer_local, sizeof(buffer_local), timeformat, time);
   printf("%s ", buffer_local);
   return;
}

void print_180_time(struct tm *time){
   char *timeformat = "%b %e %R";
   char buffer_local[64];
   strftime(buffer_local, sizeof(buffer_local), timeformat, time);
   printf("%s ", buffer_local);
   return;
}

void print_file_time(time_t time_file){
   time_t now = time(NULL);
   const time_t TIME_180 = 180 * 24 * 60 * 60;
   struct tm *local_time = localtime(&time_file);
   time_file -= now;
   if((-1 * TIME_180) > time_file || time_file > TIME_180){
      print_std_time(local_time);
   }else{
      print_180_time(local_time);
   }
   return;
}

void print_file_info(char *file){
   // symlink?
   char linkname[PATH_MAX + 1];
   ssize_t retval = readlink(file, linkname, sizeof(linkname));
   struct stat *info = malloc(sizeof(struct stat));
   assert(info != NULL);
   int status = lstat(file, info);
   if(status != 0){
      fprintf(stderr, "%s: %s: %s\n",
              execname, file, strerror(errno));
      exit_status = EXIT_FAILURE;
   }else{
      printf("%06o %9d ", info->st_mode, (unsigned int) info->st_size);
      print_file_time(info->st_mtime);
   }
   // it is a symlink
   if(retval >= 0){
      linkname[retval < PATH_MAX + 1 ? retval : PATH_MAX] = '\0';
      printf("%s -> %s\n", file, linkname);
   }
   // it is not a symlink
   else{
      printf("%s\n", file);
   }
   free(info);
   return;
}

int main(int argc, char **argv){
   execname = basename(argv[0]);
   if(argc == 1){
      // read in current dir (.)
      print_file_info(".");
   }else{
      for(int i = 1; i < argc; i++){
         // read in each file: argv[i]
         print_file_info(argv[i]);
      }
   }         
   return exit_status;
}
