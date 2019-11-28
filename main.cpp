#include "Person.h"
#include "Faculty.h"
#include "Student.h"
#include "DLL.h"
#include "BST.h"
#include "DatabaseManager.h"
#include <iostream>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
using namespace boost;

/* Runs database manager until told to quit.
*/
int main (int argc, char** argv) {

  DatabaseManager* db = new DatabaseManager();

  cout << endl << "\t\tLLOYD'S STUDENT/FACULTY DATABASE" << endl << endl;
  while (db->Menu()) {
    continue;
  }

}
