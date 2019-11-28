#ifndef TREE_EMPTY_EXCEPTION
#define TREE_EMPTY_EXCEPTION

#include <iostream>

using namespace std;

/* Exception thrown when trying to search or remove from an empty tree.
*/
class TreeEmptyException {
  public:
    TreeEmptyException();
    TreeEmptyException(string msg);
    string getMessage();
  private:
    string message;
};

#endif
