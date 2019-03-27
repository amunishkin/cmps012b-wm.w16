//
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)
// 
// # $Id: exit255.java,v 1.1 2013-01-22 19:46:46-08 amunishk - $

import java.lang.System.*;

class exit255{

   private static final int EXIT_FAILURE = 255;
   private static final String message = "EXIT 255";
//
// NAME
//    main
//
// DESCRIPTION
//    Prints out "EXIT 1" to the standard error and exit with
//    a exit status of 1.
//
   public static void main(String[] args){
      System.err.printf("%s", message);
      System.exit(EXIT_FAILURE);
   }
}
