// $Id: bigint.c,v 1.9 2013-03-03 17:16:25-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"

static char *bigint_tag = "struct bigint";

struct bigint {
   char *tag;
   bool is_negative;
   size_t length;
   size_t digits;
   char *buffer;
};

static void trim_zeros (bigint *bigint) {
   while (bigint->digits > 0) {
      size_t digitpos = bigint->digits - 1;
      if (bigint->buffer[digitpos] != 0) break;
      --bigint->digits;
   }
}

static bigint *do_add (bigint *left, bigint *right) {
   bigint *result = new_bigint(left->digits+1);
   int carry = 0;
   for(unsigned int i = 0; i < right->digits; i++){
      int sum = left->buffer[i] + right->buffer[i] + carry;
      result->buffer[i] = sum % 10;
      carry = sum / 10;
      if(i == right->digits-1){
         for(unsigned int j = right->digits; j < left->digits; j++){
            result->buffer[j] = left->buffer[j] + carry;
            carry = result->buffer[j] / 10;
            result->buffer[j] %= 10;
            if(j == left->digits-1){
               result->buffer[j+1] = carry;
            }
         }
      }
   }
   result->is_negative = left->is_negative;
   trim_zeros(result);
   return result;
}

static bigint *do_sub (bigint *left, bigint *right) {
   bigint *result = new_bigint(left->digits);
   int borrow = 0;
   for(unsigned int i = 0; i < right->digits; i++){
      int diff = left->buffer[i] - right->buffer[i] - borrow;
      if(diff < 0) diff += 20;
      result->buffer[i] = diff % 10;
      borrow = diff / 10;
      if(i == right->digits-1){
         for(unsigned int j = right->digits; j < left->digits; j++){
            diff = left->buffer[j] - borrow;
            if(diff < 0) diff += 20;
            result->buffer[j] = diff % 10;
            borrow = diff / 10;
         }
      }
   }
   result->is_negative = left->is_negative;
   trim_zeros(result);
   return result;
}

bigint *new_bigint (size_t length) {
   bigint *bigint = malloc (sizeof (struct bigint));
   assert (bigint != NULL);
   bigint->tag = bigint_tag;
   bigint->is_negative = false;
   bigint->length = length;
   bigint->digits = length;
   bigint->buffer = calloc (length, sizeof (char));
   assert (bigint->buffer != NULL);
   return bigint;
}

bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   assert (length > 0);
   bigint *bigint = new_bigint (length);
   if (*string == '_') {
      bigint->is_negative = true;
      ++string;
      --length;
   }
   int index = 0;
   while (length-- > 0) {
      char digit = string[length] - '0';
      assert (0 <= digit && digit <= 9);
      bigint->buffer[index++] = digit;
   }
   trim_zeros (bigint);
   return bigint;
}

void free_bigint (bigint *bigint) {
   assert (is_bigint (bigint));
   free (bigint->buffer);
   memset (bigint, 0, sizeof (bigint));
   free (bigint);
}

void print_bigint (bigint *bigint, FILE *file) {
   assert (is_bigint (bigint));
   int index = bigint->digits;
   if((bigint->is_negative && index == 1 && 
       bigint->buffer[index-1] == 0) || index == 0){
      fprintf(file, "0");
   }else{
      if(bigint->is_negative){
         fprintf(file, "-");
      } 
      while(index > 0){
         fprintf(file, "%d", bigint->buffer[--index]);
      }
   }
   fprintf(file, "\n");
}

bigint *add_bigint (bigint *left, bigint *right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint *result = NULL;
   // pos + pos
   if(!left->is_negative && !right->is_negative){
      result = do_add(left, right);
   }
   // pos + neg
   // neg + pos
   else if((left->is_negative && !right->is_negative) ||
           (!left->is_negative && right->is_negative)){
      if(is_bigger(left, right)){
         result = do_sub(left, right);
      }else{
         result = do_sub(right, left);
      }
   }
   // neg + neg
   else{
      result = do_add(left, right);
   }
   if(is_zero(result)) result->digits = 1;
   return result;
}

bigint *sub_bigint (bigint *left, bigint *right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint *result = NULL;
   // pos - pos
   if(!left->is_negative && !right->is_negative){
      if(is_bigger(left, right)){
         result = do_sub(left, right);
      }else{
         right->is_negative = true;
         result = do_sub(right, left);
      }
   }
   // pos - neg
   // neg - pos
   else if((left->is_negative && !right->is_negative) ||
           (!left->is_negative && right->is_negative)){
      if(is_bigger(left, right)){
         result = do_add(left, right);
      }else{
         if(!left->is_negative) right->is_negative = true;
                          else right->is_negative = false;
         result = do_add(right, left);
      }
   }
   // neg - neg
   else{
      if(is_bigger(left, right)){
         result = do_sub(left, right);
      }else{
         right->is_negative = false;
         result = do_sub(right, left);
      }
   }
   if(is_zero(result)) result->digits = 1;
   return result;
}

bigint *mul_bigint (bigint *left, bigint *right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint *result = new_bigint(left->digits + right->digits + 1);
   for(unsigned int i = 0; i < result->length; i++){
      result->buffer[i] = 0;
   }
   int carry = 0;
   for(unsigned int i = 0; i < right->digits; i++){
      for(unsigned int j = 0; j < left->digits; j++){
         int sum = (right->buffer[i] * left->buffer[j]) + carry;
         result->buffer[i+j] += sum;
         carry = result->buffer[i+j] / 10;
         result->buffer[i+j] %= 10;
         if(j == left->digits-1){
            result->buffer[i+j+1] = carry;
            carry = 0;
         }
      }     
   }
   trim_zeros(result);
   if(is_zero(result)) result->digits = 1;
   return result;
}

bool is_zero(bigint *bigint){
   for(unsigned int i = 0; i < bigint->digits; i++){
      int digit = bigint->buffer[i];
      if(bigint->buffer[i] != 0){
         assert(0 < digit && digit <= 9);
         return false;
      }
   }
   return true; 
}
bool is_bigger(bigint *left, bigint *right){
   if(left->digits > right->digits) return true;
   if(left->digits == right->digits){
      if(left->buffer[left->digits-1] >=
                  right->buffer[right->digits-1])
         return true;
   }
   return false;
}

bool is_bigint (bigint *bigint) {
   return bigint->tag == bigint_tag;
}
