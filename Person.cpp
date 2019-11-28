#include "Person.h"
#include <iostream>

using namespace std;

/* Default constructor
*/
Person::Person() {
  id = 0;
  name = "";
  level = "";
}

/* Overloaded constructor
* @param unsigned int i: ID
* @param n: name
* @param l: level
*/
Person::Person(unsigned int i, string n, string l) {
  id = i;
  name = n;
  level = l;
}

/* Accessor - ID
*/
unsigned int Person::GetID() {
  return id;
}

/* Mutator - ID
*/
void Person::SetID(unsigned int i) {
  id = i;
}

/* Accessor - Name
*/
string Person::GetName() {
  return name;
}

/* Mutator - ID
*/
void Person::SetName(string n) {
  name = n;
}

/* Accessor - Level
*/
string Person::GetLevel() {
  return level;
}

/* Mutator - ID
*/
void Person::SetLevel(string l) {
  level = l;
}

/* Converts Person to string.
*/
string Person::ToString() {
  string temp = "";
  temp += name + "\n";
  temp += "ID: " + to_string(id) + "\n";
  temp += "Level: " + level + "\n";
  return temp;
}

/* Compares two Person objects based on ID
*/
bool Person::operator < (Person p) {
  return (id < p.id);
}

/* Compares two Person objects based on ID
*/
bool Person::operator > (Person p) {
  return (id > p.id);
}

/* Compares two Person objects based on ID
*/
bool Person::operator == (Person p) {
  return (id == p.id);
}
