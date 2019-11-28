#include "Person.h"
#include "Faculty.h"
#include "DLL.h"
#include <iostream>

using namespace std;

/* Default constructor.
*/
Faculty::Faculty() : Person() {
  department = "";
  advisees = new DLL<unsigned int>();
}

/* Overloaded constructor.
* @param i: ID of new faculty.
* @param n: name
* @param l: Level
* @param d: department
* @param DLL<unsigned int>* a: list of advisees
*/
Faculty::Faculty(unsigned int i, string n, string l, string d, DLL<unsigned int>* a) : Person(i, n, l) {
  department = d;
  advisees = a;
}

/* Destructor.
*/
Faculty::~Faculty() {
  advisees = NULL;
}

/* Accessor - Department
*/
string Faculty::GetDepartment() {
  return department;
}

/* Mutator - department
*/
void Faculty::SetDepartment(string d) {
  department = d;
}

/* Accessor - Advisees
*/
DLL<unsigned int>* Faculty::GetAdvisees() {
  return advisees;
}

/* Mutator - advisees
*/
void Faculty::SetAdvisees(DLL<unsigned int>* a) {
  advisees = a;
}

/* Adds an advisee to advisee list.
*/
void Faculty::AddAdvisee(unsigned int i) {
  advisees->insertFront(i);
}

/* Removes an advisee from advisee list.
*/
void Faculty::RemoveAdvisee(unsigned int i) {
  advisees->deleteFirst(i);
}

/* Converts faculty to string.
*/
string Faculty::ToString() {
  string temp = Person::ToString();
  temp += "Department: " + department + "\n";
  temp += "Advisee IDs: \n";
  for (int i = 0; i < advisees->getCount(); ++i) {
    temp += "\t" + to_string(i+1) + ". " + to_string(advisees->valAtIndex(i)) + "\n";
  }
  return temp;
}

/* Overrides << operator.
*/
ostream& operator <<(ostream& os, const Faculty& f) {
  os << f.name << endl << "ID: " << to_string(f.id) << endl << "Level: " << f.level << endl << "Department: " << f.department << endl;
  if (f.advisees->getCount() == 0) {
    os << "No advisees." << endl;
  } else {
    os << "Advisees: " << endl;
    for (int i = 0; i < f.advisees->getCount(); ++i) {
      os << '\t' << to_string(i+1) << ". " << to_string(f.advisees->valAtIndex(i)) << endl;
    }
  }
  return os;
}
