//
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)
//
// NAME
//    wordct - count lines, words, characters in files
//
// SYNOPSIS
//    wordct [-lwc] [filename...]
//
// DESCRIPTION
//    The wordct utility reads one or more input files, and by default,
//    writes out the number of lines, words, and bytes contained in the
//    input files to stdout. If more than one input file is specified,
//    the total count for all of the files is also written. If more
//    than one input file is specified, the total count for all of the
//    files is also written to stdout.
//
// NOTES
//    This program assumes text files.
//

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class wordct {
   static final String STDIN_NAME = "-";
   private static String[] words;
   private static int fileCount;
   private static counts dataOnFile = new counts();
   private static counts total = new counts();

   // Inner convenience class for counting entities.
   static class counts {
      int linecount;
      int wordcount;
      int charcount;
   }

   static class options {
      boolean optsChanged = false;
      boolean countlines = true;
      boolean countwords = true;
      boolean countchars = true;
   }

   //
   // NAME
   //    countfile (Scanner)
   //
   // DESCRIPTION
   //    Uses nextLine to read lines from an open Scanner.
   //    Counts chars/words/lines in file.
   //
   static void countfile (String filename, Scanner scan){
      if (scan != null) {
         while (scan.hasNextLine()) {
            String line = scan.nextLine();
            ++dataOnFile.linecount;
            dataOnFile.wordcount += countWordsInLine(line);
            dataOnFile.charcount += countCharsInLine(words);
            // Contiditional Statement if no file(s).
            if(filename.equals(STDIN_NAME)){
               out.print("Continue (Y/N): ");
               if(scan.next().equalsIgnoreCase("N")){
                 break;
               }
               scan.nextLine();
            }
         }      
      }
   }

   //
   // NAME
   //    countWordsInLine
   //
   // DESCRIPTION
   //    Counts the total amount of word in a line.
   //
   static int countWordsInLine(String line){
      int totalWords = 0;
      //Cut up the words and put them in a data structure
      words = line.split("\\s+");
      if(words[0].equals(null)){
         // No words
      }else if(words[0].equals("")){
         totalWords = words.length - 1;
      }else{
         totalWords = words.length;
      }
      return totalWords;
   }

   //
   // NAME
   //    countCharsInLine
   //
   // DESCRIPTION
   //    Counts the total amount of chars in a line:
   //    only the words not white space.
   //
   static int countCharsInLine(String[] currentWords){
      int totalChars = 0;
      for(int i = 0; i < currentWords.length; i++){
         totalChars += currentWords[i].length();
      }
      return totalChars;
   }

   //
   // NAME
   //    findMaxWidth
   // 
   // DESCRIPTION
   //     Finds the largest int from linecount, wordcount,
   //     and charcount.
   //     Returns the largest width from the digit amount
   //     from the largest number.
   //
   public static int findMaxWidth(counts count){
      int max = count.linecount;
      String digitAmount = "";
      if(max < count.wordcount){
         max = count.wordcount;
      }
      if(max < count.charcount){
         max = count.charcount;
      }
      // Find the needed digits to place the largest number
      // in. Max is now the amount needed for largest width.
      digitAmount = "" + max;
      max = digitAmount.length();
      return max;
   }

   //
   // NAME
   //    printFileInfo
   // 
   // DESCRIPTION
   //    Prints the information in the file or stdin (if no file
   //    specified): line count, word count, and or char count (also
   //    known as byte if using ASCII characters) to the stdout.
   //
   public static void printFileInfo(String filename, options opts){
      // For formatting based on variable width.
      int width = findMaxWidth(dataOnFile);
      // Prints the specificed data.
      if(filename.charAt(0) != '-'){
         out.printf("%s :%n", filename);
      }
      if(opts.countlines){
         out.printf("%" + width + "d Lines%n",
                    dataOnFile.linecount);
      }
      if(opts.countwords){
         out.printf("%" + width + "d Words%n",
                    dataOnFile.wordcount);
      }
      if(opts.countchars){
         out.printf("%" + width + "d Characters%n",
                    dataOnFile.charcount);
      }
   }
   
   //
   // NAME
   //    printTotal
   //
   // DESCRIPTION
   //    Prints the total lines, words, and or characters from all
   //    files. This method runs if there where 2 or more files
   //    specified to be read by wordct.
   //
   public static void printTotal(){
      int width = findMaxWidth(total);
      out.println("::::: TOTAL COUNTS :::::"); 
      out.printf("%" + width + "d total Files%n", fileCount);
      out.printf("%" + width + "d total Lines%n", total.linecount);
      out.printf("%" + width + "d total Words%n", total.wordcount);
      out.printf("%" + width + "d total Characters%n", total.charcount);
   }
   
   //
   // NAME
   //    addToTotal
   //
   // DESCRIPTION
   //    Accumalates the total line, word, and character count
   //    from all files read to be later printed by printTotal
   //    method.
   //
   public static void addToTotal(counts count){
      total.linecount += count.linecount;
      total.wordcount += count.wordcount;
      total.charcount += count.charcount;
   } 
 
   //
   // NAME
   //    main
   //
   // DESCRIPTION
   //    Main function of the class.  Causes a service function to
   //    emit the contents of standard input, if no args, and to
   //    emit each file in turn, if args.
   //
   public static void main (String[] args) {
      options opts = new options();
      String choice = "";
      // Default: only wordct was typed.
      if (args.length < 1) {
         countfile (STDIN_NAME, new Scanner (System.in));
         printFileInfo(STDIN_NAME, opts);
      }else {
         // Option(s) specified.
         if(args[0].charAt(0) == '-'){
            opts.optsChanged = true;
            String option = args[0] + " ";
            if(option.length() == 3){
               choice = option.substring(0,2);
            }
            else if(option.length() == 4){
               choice = option.substring(0,3);
            }
         }
         // Set Choice.
         if(choice.equals("-l")){
            opts.countwords = false;
            opts.countchars = false;
         }
         else if(choice.equals("-w")){
            opts.countlines = false;
            opts.countchars = false;
         }
         else if(choice.equals("-c")){
            opts.countlines = false;
            opts.countwords = false;
         }
         else if(choice.equals("-lw") ||
                  (choice.equals("-wl"))){
            opts.countchars = false;
         }
         else if(choice.equals("-lc") ||
                  (choice.equals("-cl"))){
            opts.countwords = false;
         }
         else if(choice.equals("-wc") ||
                  (choice.equals("-cw"))){
            opts.countlines = false;
         }
         // Check options to see if need to skip first
         // entry at args[0]. Skip if only filename and
         // options specified.
         int itor;
         if(opts.optsChanged && (args.length > 1)){
            itor = 1;
         }else{
            itor = 0;
         }
         // Process filenames.
         for(; itor < args.length; ++itor){
            String filename = args[itor];
            // Default: stdin is read, if no files specified.
            if(filename.charAt(0) == '-') {
               countfile (STDIN_NAME, new Scanner (System.in));
            // File is specified.
            }else {
               try {                  
                  Scanner scan = new Scanner (new File (filename));
        
                  // Work only on files.
                  if(args[itor].charAt(0) != '-'){                    
                     countfile (filename, scan);
                     addToTotal(dataOnFile);
                     fileCount++;
                  }
                  scan.close();                  
               }catch (IOException error) {
                  misclib.warn (error.getMessage());
                  countfile (filename, null);
               }
            }
            // Information is printed with options if specified.
            printFileInfo(filename, opts);
         }
         // Prints total info if two or more files specifed.
         if(fileCount >= 2){
            printTotal();
         }
      }
      exit (misclib.exit_status);
   }
}
