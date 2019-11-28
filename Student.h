#ifndef STUDENT
#define STUDENT

#include "Person.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/* Class for storing student records.
*/
class Student : public Person
{

  public:

    Student();
    Student(unsigned int id, string name, string level, string major, double gpa, unsigned int advisor);

    string GetMajor();
    void SetMajor(string m);
    double GetGPA();
    void SetGPA(double g);
    unsigned int GetAdvisor();
    void SetAdvisor(unsigned int a);

    virtual string ToString();

    friend ostream& operator <<(ostream& os, const Student& s);

  private:
    string major;
    double gpa;
    unsigned int advisor;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & boost::serialization::base_object<Person>(*this);
      ar & major;
      ar & gpa;
      ar & advisor;
    }

};

#endif
