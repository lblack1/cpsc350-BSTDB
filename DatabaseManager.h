#ifndef DATABASE_MANAGER
#define DATABASE_MANAGER

#include "BST.h"
#include "DLL.h"
#include "Stack.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;
using namespace boost;

/* A class that manages a database of Students and Faculty members.
*/
class DatabaseManager
{

  public:
    DatabaseManager();

    bool Menu();

  private:
    void PrintStudents();
    void PrintFaculty();
    bool PrintStudent(unsigned int i);
    bool PrintFaculty(unsigned int i);
    bool PrintAdvisor(unsigned int i);
    bool PrintAdvisees(unsigned int i);
    void AddStudent();
    bool DeleteStudent(unsigned int i);
    void AddFaculty();
    bool DeleteFaculty(unsigned int i);
    bool SetAdvisor(unsigned int iStu, unsigned int iFac);
    bool RemoveAdvisee(unsigned int iFac, unsigned int iStu);
    void Rollback();
    void Exit();

    void WriteDB();

    void StackTrees();

    void AddStudent(unsigned int id, unsigned int adv);
    void AddFaculty(unsigned int id, unsigned int adv);
    void AddFaculty(unsigned int id, DLL<unsigned int>* adv);

    BST<unsigned int, Student*>* studentTree;
    BST<unsigned int, Faculty*>* facultyTree;

    Stack< pair<BST <unsigned int, Student*>*, BST <unsigned int, Faculty*>* >* >* rollbackStack;


};

#endif
