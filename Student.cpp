#include "Person.h"
#include "Student.h"
#include <iostream>

using namespace std;

/* Default constructor
*/
Student::Student() : Person() {
  major = "";
  gpa = -1;
  advisor = 0;
}

/* Overloaded constructor
* @param i: ID
* @param n: name
* @param l: level
* @param m: major
* @param g: GPA
* @param a: advisor
*/
Student::Student(unsigned int i, string n, string l, string m, double g, unsigned int a) : Person(i, n, l) {
  major = m;
  gpa = g;
  advisor = a;
}

/* Accessor - major
*/
string Student::GetMajor() {
  return major;
}

/* Mutator - major
*/
void Student::SetMajor(string m) {
  major = m;
}

/* Accessor - GPA
*/
double Student::GetGPA() {
  return gpa;
}

/* Mutator - GPA
*/
void Student::SetGPA(double g) {
  gpa = g;
}

/* Accessor - advisor
*/
unsigned int Student::GetAdvisor() {
  return advisor;
}

/* Mutator - advisor
*/
void Student::SetAdvisor(unsigned int a) {
  advisor = a;
}

/* Converts student record to string.
*/
string Student::ToString() {
  string temp = Person::ToString();
  temp += "Major: " + major + "\n";
  temp += "GPA: " + to_string(gpa) + "\n";
  temp += "Advisor ID: " + to_string(advisor) + "\n";
  return temp;
}

/* Overrides << operator
*/
ostream& operator <<(ostream& os, const Student& s) {
  os << s.name << endl << "ID: " << to_string(s.id) << endl << "Level: " << s.level << endl << "Major: " << s.major << endl << "GPA: " << to_string(s.gpa) << endl << "Advisor: ";
  if (s.advisor == 0) {
    os << "No advisor" << endl;
  } else {
    os << to_string(s.advisor) << endl;
  }
  return os;
}
