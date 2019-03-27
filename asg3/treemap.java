// $Id: treemap.java,v 1.2 2013-02-14 19:32:45-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

import static java.lang.System.*;

class treemap {

   class tree {
      String key;
      String value;
      tree left;
      tree right;
   }
   
   tree root = null;
   private boolean replace = false;
   private boolean gone_left = false;

   // Binary search
   // Retrieve data from tree
   public String get (String key) {
      String value = null;
      tree tmp = binarysearch(root, key, false);
      if(tmp != null){
         value = tmp.value;
      }
      return value;
   }

   // Binary search algorithm.
   tree binarysearch(tree root, String key, boolean put) {
      tree curr = root;
      tree prev = null;
      while (curr != null) {
         int cmp = curr.key.compareTo (key);
         if (cmp == 0){
            replace = true;
            return curr;
         }
         if (cmp < 0){
            gone_left = false;
            prev = curr;
            curr = curr.right;
         }else{
            gone_left = true;
            prev = curr;
            curr = curr.left;
         }
      }
      replace = false;
      if(put && (root != null)){
         return prev;
      }else{
         return curr;
      }
   }

   // Put data in the tree
   public String put (String key, String value) {
      tree node = binarysearch(root, key, true);
      String val = null;
      // Found key
      if(node != null && replace){
         val = node.key;
         node.key = key;
      }
      // Not found key
      // Create new leaf node
      else{
         if(root == null){
            root = new tree();
            root.key = key;
            root.value = value;
            root.left = null;
            root.right = null;
         }else{
            tree tmp = new tree();
            tmp.key = key;
            tmp.value = value;
            tmp.left = null;
            tmp.right = null;
            if(gone_left){
               node.left = tmp;
            }else{
               node.right = tmp;
            }
         }
      }
      return val;
   }

   // Inorder transfersal function
   // Prints contents of each node in tree
   // (depth, key, value, left child and right child)
   public void depth_inorder (tree node, int depth) {
      int level = depth;
      if (node.left != null) depth_inorder (node.left, ++level);
      out.printf ("Depth[%d] Key[%s] Value[%s] " +
            "Left Child[%s] Right Child[%s]%n",
            depth, node.key, node.value,
            node.left, node.right);
      if (node.right != null) depth_inorder (node.right, ++level);
      out.printf ("Depth[%d] Key[%s] Value[%s] " +
            "Left Child[%s] Right Child[%s]%n",
            depth, node.key, node.value,
            node.left, node.right);
   }

   // Modified toString to print tree nodes
   public String toString(){
      return "%3d \"%s\" \"%s\" %s %s%n";
   }

   public void debug_tree () {
      debug_tree_recur (root, 0);
   }

   private void debug_tree_recur (tree node, int depth) {
      depth_inorder(node, depth);
   }

}
