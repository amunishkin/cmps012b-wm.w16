// $Id: jxref.java,v 1.13 2013-02-02 11:44:27-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)
//
// NAME
//    jxref - cross refercing and word count utility
//
// SYNOPSIS
//    jxref [filename...]
// 
// DESCRIPTION
//    Each file is read in sequence and words are extracted
//    from the file. At the end of each file, a table is 
//    printed, sorted in lexicographic order with each word
//    followed by the number of times it occurs and a list 
//    of the numbers of the lines where it occurs. Cross
//    reference output is written to stdout (System.out)
//    and error messages are written to stderr (System.err)
//
// OPTIONS
//    None.
// 
// OPERANDS
//    Operands consist of the names of files to be read in
//    sequence. If no filenames are specified, stdin is 
//    read. Tf filenames are specified, each file is read
//    in turn. If a filename is specified as a single minus
//    sign (-) stdin is read at that point. In order to 
//    read a file whose name really is a minus sign, it 
//    should be specified on the command line as "./-".
//

import java.io.*;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import static java.lang.System.*;

class jxref {
   private static final String STDIN_FILENAME = "-";
   private static final String REGEX = "\\w+([-'.:/]\\w+)*";
   private static final Pattern PATTERN = Pattern.compile (REGEX);

   // Processing of file
   private static void xref_file (String filename, Scanner file) {
      listmap map = new listmap();
      // Read each line
      for (int linenr = 1; file.hasNextLine(); ++linenr) {
         String line = file.nextLine();
         Matcher match = PATTERN.matcher (line);
         // If word is matched in structure
         // just add the line number.
         while (match.find()) {
            String word = match.group();
            map.insert(word, linenr);
         }
      }
      // Print title in a table format.
      out.println("::::::::::::::::::::::::::::::::");
      out.println(filename);
      out.println("::::::::::::::::::::::::::::::::");
      // Print words in lexographic order with line numbers.
      for (Entry<String, intqueue> entry: map) {
         out.printf("%s [%d] ", entry.getKey(),
                                entry.getValue().getcount());
         for(Integer val: entry.getValue()){
            out.printf("%d ", val);
         }
         out.println(); 
      }
   }

   // For each filename, open the file, cross reference it, and print.
   private static void xref_filename (String filename) {
      if (filename.equals (STDIN_FILENAME)) {
         // Read stdin and print it
         xref_file (filename, new Scanner (System.in));
      }else {
         try {
            Scanner file = new Scanner (new File (filename));
            // Read and print data on file
            xref_file (filename, file);
            file.close();
            // Errors condition
         }catch (IOException error) {
            misc.warn (error.getMessage());
         }
      }
   }

   // Main function scans arguments to cross reference files.
   public static void main (String[] args) {
      if (args.length == 0) {
         xref_filename (STDIN_FILENAME);
      }else {
         for (String filename: args) {
            xref_filename (filename);
         }
      }
      exit (misc.exit_status);
   }

}

