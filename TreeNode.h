#ifndef TREENODE
#define TREENODE

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/* Template class for a Binary Search Tree Node, with a comparable class as a key and any data type T.
*/
template <class Comparable, class T>
class TreeNode
{

  public:
    Comparable key;
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode() {
      left = NULL;
      right = NULL;
    }

    TreeNode(Comparable k, T d) {
      key = k;
      data = d;
      left = NULL;
      right = NULL;
    }

    ~TreeNode() {
      left = NULL;
      right = NULL;
    }

  private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & key;
      ar & data;
      ar & left;
      ar & right;
    }

};

#endif
