// $Id: hello.java,v 1.6 2013-01-11 10:09:08-08 - - $
//
// Author: Alexey Munishkin username: amunishk
//
// NAME
// hello - a verbose version of the classical 'Hello World' program.
//
// SYNOPSIS
// hello
//
// DESCRIPTION
// Prints the message 'Hello World' to stdout, and otherwise
// introduces itself and its environment.
//
import java.util.ArrayList;
import static java.lang.System.*;

class hello {

   static void printfprop (String format, String... props) {
      ArrayList<Object> propvals = new ArrayList<Object>();
      for (String prop : props) propvals.add (getProperty (prop));
      out.printf (format, propvals.toArray());
   }

   public static void main (String[] args) {
      double freemem = Runtime.getRuntime().freeMemory();
      long now = currentTimeMillis();
      out.print ("Hello, World!\n");
      printfprop ("Class path is%n%s%n", "java.class.path");
      printfprop ("Operating system is %s-bit %s-endian %s %s %s%n",
                  "sun.arch.data.model", "sun.cpu.endian",
                  "os.arch", "os.name", "os.version");
      printfprop ("Runtime is %s (%s)%n",
                  "java.runtime.name", "java.runtime.version");
      printfprop ("Virtual machine is %s (%s)%n",
                  "java.vm.name", "java.vm.version");
      printfprop ("Home is %s (%s)%n", "java.home", "java.version");
      out.printf ("There are %.0f bytes = %.2f Kbytes = %.4f Mbytes"
                  +" of free memory%n",
                  freemem, freemem / (1<<10), freemem / (1<<20));
      out.printf ("Time is now %.3f seconds = %tc%n", now / 1e3, now);
   }

}
