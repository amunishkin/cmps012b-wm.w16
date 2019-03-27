// $Id: listmap.java,v 1.7 2013-02-02 11:07:19-08 - - $
// Partner: Alexey Munishkin (amunishk)
// Partner: Diem Phuong Chau (dhchau)

import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import static java.lang.System.*;

class listmap implements Iterable<Entry<String,intqueue>> {

   private class node implements Entry<String,intqueue> {
      String key;
      intqueue queue = new intqueue();
      node link;
      public String getKey() {
         return key;
      }
      public intqueue getValue() {
         return queue;
      }
      public intqueue setValue (intqueue queue) {
         throw new UnsupportedOperationException();
      }
   }
   private node head = null;

   public listmap() {
      // Not needed, since head defaults to null anyway.
   }

   public void insert (String key, int linenr) {
      // Add first element
      if(head == null){
         head = new node();
         node tmp = new node();
         head = tmp;
         tmp.key = key;
         tmp.queue.insert(linenr);
         tmp.link = null;
      }
      // Order the next elements
      else{
         node curr = head;
         node prev = null;
         int cmp = 1;
         // Phase 1 - find the insertion points. -- O(n)
         while(curr != null){
            cmp = curr.key.compareTo(key);
            if(cmp >= 0) break;
            prev = curr;
            curr = curr.link;
         }
         // Phase 2 - insert if not already there. -- O(1)
         if(cmp != 0){
            node tmp = new node();
            tmp.key = key;
            tmp.queue.insert(linenr);
            tmp.link = curr;
            if(prev == null) head = tmp;
            else prev.link = tmp;
         }else{
            curr.queue.insert(linenr);
         }
      }
   }

   public Iterator<Entry<String,intqueue>> iterator() {
      return new iterator();
   }
   private class iterator implements Iterator<Entry<String,intqueue>> {
      node curr = head;

      public boolean hasNext() {
         return curr != null;
      }

      public Entry<String,intqueue> next() {
         if (curr == null) throw new NoSuchElementException();
         node next = curr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }

   }

}
