#ifndef LIST_EMPTY_EXCEPTION
#define LIST_EMPTY_EXCEPTION

#include <iostream>

using namespace std;

/* Exception thrown when trying to search or remove from an empty list.
*/
class ListEmptyException {
  public:
    ListEmptyException();
    ListEmptyException(string msg);
    string getMessage();
  private:
    string message;
};

#endif
