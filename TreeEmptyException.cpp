#include "TreeEmptyException.h"

using namespace std;

/* Default Constructor. Sets message to "Tree empty."
*/
TreeEmptyException::TreeEmptyException() {
  message = "Tree empty.";
}

/* Overloaded constructor. Sets message to argument.
* @param string msg: Error message.
*/
TreeEmptyException::TreeEmptyException(string msg) {
  message = msg;
}

/* Retrieves error message.
* @return string: Error message.
*/
string TreeEmptyException::getMessage() {
  return message;
}
