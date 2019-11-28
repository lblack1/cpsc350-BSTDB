#include "ListEmptyException.h"

using namespace std;

/* Default Constructor. Sets message to "List empty."
*/
ListEmptyException::ListEmptyException() {
  message = "List empty.";
}

/* Overloaded constructor. Sets message to argument.
* @param string msg: Error message.
*/
ListEmptyException::ListEmptyException(string msg) {
  message = msg;
}

/* Retrieves error message.
* @return string: Error message.
*/
string ListEmptyException::getMessage() {
  return message;
}
