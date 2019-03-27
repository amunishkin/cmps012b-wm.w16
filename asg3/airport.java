// $Id: airport.java,v 1.1 2013-02-14 19:29:35-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class airport {
   private static final String STDIN_FILENAME = "-";

   public static treemap load_database (String database_name) {
      treemap tree = new treemap ();
      try {
         Scanner database = new Scanner (new File (database_name));
         for (int linenr = 1; database.hasNextLine(); ++linenr) {
            String line = database.nextLine();
            if (line.matches ("^\\s*(#.*)?$")) continue;
            String[] keyvalue = line.split (":");
            if (keyvalue.length != 2) {
               misc.warn (database_name, linenr, "invalid line");
               continue;
            }
            tree.put (keyvalue[0], keyvalue[1]);
         }
         database.close();
      }catch (IOException error) {
         misc.warn (error.getMessage());
         exit(misc.exit_status);
      }
      return tree;
   } 

   public static void main (String[] args) {
      treemap tree = new treemap();
      boolean debug = false;
      if(args.length == 0){
         misc.warn("Usage: airport [-d] database");
         exit(misc.exit_status);
      }
      else if(args.length == 1){
         tree = load_database (args[0]);
      }
      else{
         debug = true;
         tree = load_database (args[1]);
      }
      if(debug){
         tree.debug_tree ();
      }else{
         Scanner stdin = new Scanner (in);
         while (stdin.hasNextLine()) {
            String airport = stdin.nextLine().toUpperCase().trim();
            String airport_name = tree.get (airport);
            if (airport_name == null) {
               misc.warn("no such airport", airport);
            }else {
               out.printf ("%s = %s%n", airport, airport_name);
            }
         }
      }
      exit (misc.exit_status);
   }

}
