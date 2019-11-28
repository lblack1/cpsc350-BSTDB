// A BST that contains a key and any data type

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include "TreeNode.h"
#include "IndexOutOfBoundsException.h"
#include "TreeEmptyException.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <typeinfo>

using namespace std;

/* A Binary Search Tree that sorts based on a Comparable class and any data type T.
*/
template <class Comparable, class T>
class BST {

  public:
    TreeNode<Comparable, T>* root;

    /* Default Constructor.
    */
    BST() {
      root = NULL;
    }

    /* Copy Constructor. Recursively copies a tree.
    * @param BST<Comparable, T>* bst: A pointer to the tree to be copied.
    */
    BST(BST<Comparable, T>* bst) {

      if (bst->root != NULL) {
        root = new TreeNode<Comparable, T>(bst->root->key, bst->root->data);
        root->left = copy(bst->root->left);
        root->right = copy(bst->root->right);
      } else {
        root = NULL;
      }

    }

    /* Destructor. Recursively destroys the tree's nodes from the bottom up.
    */
    ~BST() {
      destroy(root);
    }

    /* Indicates if the tree contains a certain key.
    * @param Comparable k: the key to check
    * @return bool: true if tree contains k, false otherwise
    */
    bool contains(Comparable k) {
      TreeNode<Comparable, T>* curr = root;
      while (curr != NULL) {
        if (k == curr->key) {
          return true;
        } else if (k < curr->key) {
          curr = curr->left;
        } else {
          curr = curr->right;
        }
      }
      return false;
    }

    /* Searches the tree for a given key.
    * @param Comparable k: key to search for
    * @return TreeNode<Comparable, T>*: node associated with the Key, or NULL if it doesn't exist.
    */
    TreeNode<Comparable, T>* search(Comparable k) {
      TreeNode<Comparable, T>* curr = root;
      while (curr != NULL) {
        if (k == curr->key) {
          return curr;
        } else if (k < curr->key) {
          curr = curr->left;
        } else {
          curr = curr->right;
        }
      }
      throw IndexOutOfBoundsException();
    }

    /* Returns data at a given key.
    * @param Comparable k: key to search for.
    * @return T: data at given key
    */
    T findData(Comparable k) {
      TreeNode<Comparable, T>* curr = root;
      while (curr != NULL) {
        if (k == curr->key) {
          return curr->data;
        } else if (k < curr->key) {
          curr = curr->left;
        } else {
          curr = curr->right;
        }
      }
      throw IndexOutOfBoundsException();
    }

    /* Inserts data at a given key.
    * @param Comparable k: Key to insert at
    * @param T d: data to insert
    */
    void insert(Comparable k, T d) {
      TreeNode<Comparable, T>* node = new TreeNode<Comparable, T>(k, d);
      if (root == NULL) {
        root = node;
        return;
      } else {
        TreeNode<Comparable, T>* curr = root;
        TreeNode<Comparable, T>* prev = NULL;
        while (curr != NULL) {
          if (k == curr->key) {
            return;
          } else if (k < curr->key) {
            prev = curr;
            curr = curr->left;
          } else {
            prev = curr;
            curr = curr->right;
          }
        }
        if (k < prev->key) {
          prev->left = node;
          return;
        } else {
          prev->right = node;
          return;
        }
      }
    }

    /* Prints a node's data and children in sorted order.
    * @param TreeNode<Comparable, T>* node: node at top of subtree being recursively printed.
    */
    void recPrint(TreeNode<Comparable, T>* node) {
      if (node == NULL) {
        return;
      } else {
        //preorder
        // cout << node->key << endl;
        // recPrint(node->left);
        // recPrint(node->right);

        //inorder
        recPrint(node->left);
        if (is_pointer<T>::value) {
          cout << *node->data << endl;
        } else {
          cout << node->data << endl;
        }
        recPrint(node->right);

        //postorder
        // recPrint(node->left);
        // recPrint(node->right);
        // cout << node->key << endl;
      }
    }

    /* Recursively prints the entire tree.
    */
    void printTree() {
      if (root == NULL) {
        cout << "Tree empty" << endl;
      } else {
        recPrint(root);
      }
    }

    /* Gets the node with highest key.
    * @return TreeNode<Comparable, T>*: node at far right of tree.
    */
    TreeNode<Comparable, T>* getMax(){
      TreeNode<Comparable, T>* curr = root;
      while (curr->right != NULL) {
        curr = curr->right;
      }
      return curr;
    }

    /* Returns value of highest key.
    * @return Comparable: the highest key
    */
    Comparable getMaxKey() {
      if (root == NULL) {
        throw TreeEmptyException();
      }
      TreeNode<Comparable, T>* curr = root;
      while (curr->right != NULL) {
        curr = curr->right;
      }
      return curr->key;
    }

    /* Gets the node with lowest key.
    * @return TreeNode<Comparable, T>*: node at far left of tree.
    */
    TreeNode<Comparable, T>* getMin(){
      TreeNode<Comparable, T>* curr = root;
      while (curr->left != NULL) {
        curr = curr->left;
      }
      return curr;
    }

    /* Returns value of lowest key.
    * @return Comparable: the lowest key
    */
    Comparable getMinKey() {
      if (root == NULL) {
        throw TreeEmptyException();
      }
      TreeNode<Comparable, T>* curr = root;
      while (curr->left != NULL) {
        curr = curr->left;
      }
      return curr->key;
    }

    /* Removes data by given key.
    * @param Comparable k: key to remove.
    * @return bool: true if an item has been removed, false otherwise.
    */
    bool remove(Comparable k) {

      if (root == NULL) {
        return false;
      }

      TreeNode<Comparable, T>* curr = root;
      TreeNode<Comparable, T>* par = root;
      bool isLeft = true;

      while (curr->key != k) {
        par = curr;
        if (k < curr->key) {
          isLeft = true;
          curr = curr->left;
        } else {
          isLeft = false;
          curr = curr->right;
        }
        if (curr == NULL) {
          return false;
        }
      }

      if (curr->left == NULL && curr->right == NULL) { // leaf node, no children
        if (curr == root) {
          root = NULL;
        } else if (isLeft) {
          par->left == NULL;
        } else {
          par->right == NULL;
        }
      } else if (curr->right == NULL) { // must be left child
        if (curr == root) {
          root == curr->left;
        } else if (isLeft){
          par->left = curr->left;
        } else {
          par->right = curr->left;
        }
      } else if (curr->left == NULL) {
        if (curr == root) {
          root == curr->right;
        } else if (isLeft) {
          par->left = curr->right;
        } else {
          par->right = curr->right;
        }
      } else {
        TreeNode<Comparable, T>* succ = getSuccessor(curr);
        if (curr == root) {
          root = succ;
        } else if (isLeft) {
          par->left = succ;
        } else {
          par->right = succ;
        }
        succ->left = curr->left;
        curr->right = NULL;
      }

    }

    /* Finds node to replace a node being deleted, and updates some pointers.
    * @param TreeNode<Comparable, T>* node: node being deleted.
    * @return TreeNode<Comparable, T>*: node to replace node being deleted.
    */
    TreeNode<Comparable, T>* getSuccessor(TreeNode<Comparable, T>* node) { // node is the node to be deleted
      TreeNode<Comparable, T>* curr = node->right;
      TreeNode<Comparable, T>* succPar = node;
      TreeNode<Comparable, T>* succ = node;
      while (curr != NULL) {
        succPar = succ;
        succ = curr;
        curr = curr->left;
      }

      if (succ != node->right) {
        succPar->left = succ->right;
        succ->right = node;
      }
      return succ;
    }

  private:
    void destroy(TreeNode<Comparable, T>* node) {
      if (node != NULL) {
        destroy(node->left);
        destroy(node->right);
        delete node;
      }
    }

    /* Recursively deep copies a subtree.
    * @param TreeNode<Comparable, T>* source: node to deep copy.
    * @return TreeNode<Comparable, T>*: the new node.
    */
    TreeNode<Comparable, T>* copy(TreeNode<Comparable, T>* source) {
      if (source != NULL) {
        TreeNode<Comparable, T>* temp = new TreeNode<Comparable, T>(Comparable(source->key), T(source->data));
        temp->left = copy(source->left);
        temp->right = copy(source->right);
      } else {
        return NULL;
      }
    }

    /* Serializes a BST with Boost.
    */
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & root;
    }

};

#endif
