// $Id: intqueue.java,v 1.5 2013-02-02 11:07:19-08 - - $
// Partner: Alexey Munishkin (amunishk)
// Partner: Diem Phuong Chau (dhchau)

import java.util.Iterator;
import java.util.NoSuchElementException;

class intqueue implements Iterable<Integer> {

   private class node {
      int linenr;
      node link;
   }
   private int count = 0;
   private node front = null;
   private node rear = null;

   // For each word has its own line
   // numbers associated with it.
   public void insert (int number) {
      ++count;
      // Add first element
      if(front == null){
         front = new node();
         rear = new node();
         node tmp = new node();
         front = tmp;
         tmp.linenr = number;
         tmp.link = null;
         rear = tmp;
      }
      // Append the next data
      else{
         node tmp = new node();
         rear.link = tmp;
         rear = tmp;
         tmp.linenr = number;
         tmp.link = null;
      }                                                 
   }

   public boolean empty() {
      return count == 0;
   }

   public int getcount() {
      return count;
   }

   public Iterator<Integer> iterator() {
      return new iterator();
   }

   private class iterator implements Iterator<Integer> {
      node curr = front;

      public boolean hasNext() {
         return curr != null;
      }

      public Integer next() {
         if (curr == null) throw new NoSuchElementException();
         Integer next = curr.linenr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }

}

