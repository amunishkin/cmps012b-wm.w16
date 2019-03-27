//
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)
// 
// # $Id: exit1.java,v 1.1 2013-01-22 19:45:56-08 amunishk - $

import java.lang.System.*;

class exit1{

   private static final int EXIT_FAILURE = 1;
   private static final String message = "EXIT 1";
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
