#include "IndexOutOfBoundsException.h"

using namespace std;

/* Default Constructor. Sets message to "Index out of bounds."
*/
IndexOutOfBoundsException::IndexOutOfBoundsException() {
  message = "Index out of bounds.";
}

/* Overloaded constructor. Sets message to argument.
* @param string msg: Error message.
*/
IndexOutOfBoundsException::IndexOutOfBoundsException(string msg) {
  message = msg;
}

/* Retrieves error message.
* @return string: Error message.
*/
string IndexOutOfBoundsException::getMessage() {
  return message;
}
