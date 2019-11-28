#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION
#define INDEX_OUT_OF_BOUNDS_EXCEPTION

#include <iostream>

using namespace std;

/* Exception class for indicating an attempt to access an index beyond bounds of a linked list.
*/
class IndexOutOfBoundsException {
  public:
    IndexOutOfBoundsException();
    IndexOutOfBoundsException(string msg);
    string getMessage();
  private:
    string message;
};

#endif
