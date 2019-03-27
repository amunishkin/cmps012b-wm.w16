// $Id: jrpn.java,v 1.1 2013-01-24 15:40:00-08 amunishk - $

import java.util.Scanner;
import static java.lang.System.*;

class jrpn {
   static final int EMPTY = -1;
   static final int SIZE = 16;
   static class stack_t {
      int top = EMPTY;
      double[] numbers = new double[SIZE];
   }

   static void err_operator (String operator) {
      out.println (operator + ": invalid operator");
   }

   static void push (stack_t stack, double number) {
      if (stack.top >= SIZE - 1) {
         out.println (number + ": stack overflow");
      }else {
         stack.numbers[++stack.top] = number;
      }
   }

   static void do_binop (stack_t stack, char operator) {
      if (stack.top < 1) {
         out.println (operator + ": stack underflow");
      }else {
         double right = stack.numbers[stack.top--];
         double left = stack.numbers[stack.top--];
         switch (operator) {
            case '+': push (stack, left + right); break;
            case '-': push (stack, left - right); break;
            case '*': push (stack, left * right); break;
            case '/': push (stack, left / right); break;
         }
      }
   }

   static void do_print (stack_t stack) {
      if (stack.top == EMPTY) {
         out.printf ("stack is empty%n");
      }else {
         for (int pos = 0; pos <= stack.top; ++pos) {
            out.println (stack.numbers[pos]);
         }
      }
   }

   static void do_clear (stack_t stack) {
      stack.top = EMPTY;
   }


   static void do_operator (stack_t stack, String operator) {
      switch (operator.charAt(0)) {
         case '+': do_binop (stack, '+');   break;
         case '-': do_binop (stack, '-');   break;
         case '*': do_binop (stack, '*');   break;
         case '/': do_binop (stack, '/');   break;
         case ';': do_print (stack);        break;
         case '@': do_clear (stack);        break;
         default : err_operator (operator); break;
      }
   }

   public static void main (String[] args) {
      Scanner stdin = new Scanner (in);
      stack_t stack = new stack_t();
      for (;;) {
         if (stdin.hasNextDouble()) {
            double number = stdin.nextDouble();
            push (stack, number);
         }else if (stdin.hasNext()) {
            String operator = stdin.next();
            if (operator.startsWith("#")) {
               stdin.nextLine();
            }else if (operator.length() != 1) {
               err_operator (operator);
            }else {
               do_operator (stack, operator);
            }
         }else {
            break;
         }
      }
   }
}
