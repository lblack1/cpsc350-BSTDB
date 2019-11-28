#ifndef PERSON
#define PERSON

#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/* Base class for faculty and student records.
*/
class Person
{

  public:

    Person();
    Person(unsigned int i, string n, string l);

    unsigned int GetID();
    void SetID(unsigned int i);
    string GetName();
    void SetName(string n);
    string GetLevel();
    void SetLevel(string l);

    virtual string ToString();

    bool operator < (Person p);
    bool operator > (Person p);
    bool operator == (Person p);

  protected:
    unsigned int id;
    string name;
    string level;

  private:

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & id;
      ar & name;
      ar & level;
    }

};

#endif
