#ifndef FACULTY
#define FACULTY

#include "Person.h"
#include "DLL.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/* A class for storing faculty records.
*/
class Faculty : public Person
{

  public:
    Faculty();
    Faculty(unsigned int i, string n, string l, string d, DLL<unsigned int>* a);
    ~Faculty();

    string GetDepartment();
    void SetDepartment(string d);
    DLL<unsigned int>* GetAdvisees();
    void SetAdvisees(DLL<unsigned int>* a);
    void AddAdvisee(unsigned int i);
    void RemoveAdvisee(unsigned int i);

    virtual string ToString();

    friend ostream& operator <<(ostream& os, const Faculty& f);

  private:
    string department;
    DLL<unsigned int>* advisees;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & boost::serialization::base_object<Person>(*this);
      ar & department;
      ar & advisees;
    }

};

#endif
