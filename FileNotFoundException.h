#ifndef FILE_NOT_FOUND_EXCEPTION
#define FILE_NOT_FOUND_EXCEPTION

#include <iostream>

using namespace std;

class FileNotFoundException {
  public:
    FileNotFoundException();
    FileNotFoundException(string msg);
    string getMessage();
  private:
    string message;
};

#endif
