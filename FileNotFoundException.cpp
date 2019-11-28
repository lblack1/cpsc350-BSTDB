#include "FileNotFoundException.h"

using namespace std;

/* Default Constructor. Sets message to "File path not found."
*/
FileNotFoundException::FileNotFoundException() {
  message = "File path not Found";
}

/* Overloaded constructor. Sets message to argument.
* @param string msg: Error message.
*/
FileNotFoundException::FileNotFoundException(string msg) {
  message = msg;
}

/* Retrieves error message.
* @return string: Error message.
*/
string FileNotFoundException::getMessage() {
  return message;
}
