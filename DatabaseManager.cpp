#include "DatabaseManager.h"
#include "Person.h"
#include "Faculty.h"
#include "Student.h"
#include "DLL.h"
#include "BST.h"
#include "Stack.h"

#include "IndexOutOfBoundsException.h"
#include "ListEmptyException.h"
#include "TreeEmptyException.h"

#include <iostream>
#include <fstream>
#include <time.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;
using namespace boost::archive;

/* Default constructor. Deserializes student and faculty trees, if such files exist.
*/
DatabaseManager::DatabaseManager() {

  ifstream stuIn("studentTable");
  if (!stuIn) {
    studentTree = new BST<unsigned int, Student*>();
  } else {
    text_iarchive iarStu(stuIn);
    iarStu & studentTree;
  }

  ifstream facIn("facultyTable");
  if (!facIn) {
    facultyTree = new BST<unsigned int, Faculty*>();
  } else {
    text_iarchive iarFac(facIn);
    iarFac & facultyTree;
  }

  rollbackStack = new Stack< pair< BST<unsigned int, Student*>*, BST<unsigned int, Faculty*>* >* >(5);
  StackTrees();

}

/* Controls logic for selecting operations to perform on the database.
* @return bool: true if program should continue iterating prompting for options.
*/
bool DatabaseManager::Menu() {

  cout << endl << "What would you like to do? (options marked (c) change the Database and can be rolled back 5 times)" << endl;
  cout << "\t1. Print all student records in order of ascending ID" << endl;
  cout << "\t2. Print all faculty records in order of ascending ID" << endl;
  cout << "\t3. Print a student record by ID number" << endl;
  cout << "\t4. Print a faculty record by ID number" << endl;
  cout << "\t5. Print a student's advisor, given the student's ID" << endl;
  cout << "\t6. Print a faculty's advisees, given the faculty's ID" << endl;
  cout << "\t7. Add a student to database (c)" << endl;
  cout << "\t8. Add a faculty to database (c)" << endl;
  cout << "\t9. Delete a student record by ID (c)" << endl;
  cout << "\t10. Delete a faculty record by ID (c)" << endl;
  cout << "\t11. Set a student's advisor, given both IDs (c)" << endl;
  cout << "\t12. Remove an advisee from a faculty, given both IDs (c)" << endl;
  cout << "\t13. Rollback database" << endl;
  cout << "\t14. Exit" << endl;

  int option;
  string temp;

  while (true) {
    cout << "Enter option number: ";
    getline(cin, temp);

    try {
      option = stoi(temp);
      if (option < 1 || option > 14) {
        throw invalid_argument("Not an option");
      }
      break;
    } catch (invalid_argument &ia) {
      cout << "Not a valid option. Enter a number between 1 and 14." << endl;
    }
  }



  switch (option) {

    case 1:
      PrintStudents();
      break;
    case 2:
      PrintFaculty();
      break;
    case 3:
      cout << "Enter student ID: ";
      while (true) {
        getline(cin, temp);
        try {
          PrintStudent((unsigned int)stoul(temp));
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      break;
    case 4:
      cout << "Enter faculty ID: ";
      while (true) {
        getline(cin, temp);
        try {
          PrintFaculty((unsigned int)stoul(temp));
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      break;
    case 5:
      cout << "Enter student ID: ";
      while (true) {
        getline(cin, temp);
        try {
          PrintAdvisor((unsigned int)stoul(temp));
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      break;
    case 6:
      cout << "Enter faculty ID: ";
      while (true) {
        getline(cin, temp);
        try {
          PrintFaculty((unsigned int)stoul(temp));
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      break;
    case 7:
      AddStudent();
      break;
    case 8:
      AddFaculty();
      break;
    case 9:
      cout << "Enter student ID: ";
      while (true) {
        getline(cin, temp);
        try {
          DeleteStudent((unsigned int)stoul(temp));
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      break;
    case 10:
      cout << "Enter faculty ID: ";
      while (true) {
        getline(cin, temp);
        try {
          DeleteFaculty((unsigned int)stoul(temp));
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      break;
    case 11:
      cout << "Enter student ID: ";
      unsigned int stuID;
      while (true) {
        getline(cin, temp);
        try {
          stuID = (unsigned int)stoul(temp);
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      cout << "Enter faculty ID: ";
      unsigned int facID;
      while (true) {
        getline(cin, temp);
        try {
          facID = (unsigned int)stoul(temp);
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      SetAdvisor(stuID, facID);
      break;
    case 12:
      cout << "Enter faculty ID: ";
      unsigned int facIDTwo;
      while (true) {
        getline(cin, temp);
        try {
          facIDTwo = (unsigned int)stoul(temp);
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      cout << "Enter student ID: ";
      unsigned int stuIDTwo;
      while (true) {
        getline(cin, temp);
        try {
          stuIDTwo = (unsigned int)stoul(temp);
          break;
        } catch (invalid_argument &ia) {
          cout << "Invalid ID. Enter valid ID: ";
        }
      }
      RemoveAdvisee(facIDTwo, stuIDTwo);
      break;
    case 13:
      Rollback();
      break;
    case 14:
      WriteDB();
      return false;
      break;
    default:
      break;

    }

    return true;

}

/* Prints students in ascending order of ID number.
*/
void DatabaseManager::PrintStudents() {
  studentTree->printTree();
}

/* Prints faculty in ascending order of ID number.
*/
void DatabaseManager::PrintFaculty() {
  facultyTree->printTree();
}

/* Prints a student record by ID.
* @param unsigned int i: the ID to print.
* @return bool: true if student ID exists, false otherwise.
*/
bool DatabaseManager::PrintStudent(unsigned int i) {
  try {
    cout << studentTree->findData(i) << endl;
    return true;
  } catch (IndexOutOfBoundsException e) {
    cout << "No student with id " << to_string(i) << " was found." << endl;
    return false;
  }
}

/* Prints a faculty record by ID.
* @param unsigned int i: the ID to print.
* @return bool: true if faculty ID exists, false otherwise.
*/
bool DatabaseManager::PrintFaculty(unsigned int i) {
  try {
    cout << facultyTree->findData(i) << endl;
    return true;
  } catch (IndexOutOfBoundsException e) {
    cout << "No faculty with id " << to_string(i) << " was found." << endl;
    return false;
  }
}

/* Prints the record of the Advisor of a student with a given ID.
* @param unsigned int i: ID of student to print advisor of.
* @return bool: true if Student exists, false otherwise.
*/
bool DatabaseManager::PrintAdvisor(unsigned int i) {
  try {
    cout << facultyTree->findData(studentTree->findData(i)->GetAdvisor()) << endl;
    return true;
  } catch (IndexOutOfBoundsException e) {
    cout << "No student with id " << to_string(i) << " was found." << endl;
    return false;
  }
}

/* Prints the records of the Advisees of a student with a given ID.
* @param unsigned int i: ID of faculty to print advisees of.
* @return bool: true if faculty exists, false otherwise.
*/
bool DatabaseManager::PrintAdvisees(unsigned int i) {
  try {
    DLL<unsigned int>* tempList = facultyTree->findData(i)->GetAdvisees();
    if (tempList->getCount() == 0) {
      cout << "Advisor " << i << " has no advisees." << endl;
    } else {
      for (int i = 0; i < tempList->getCount(); ++i) {
        cout << tempList->valAtIndex(i) << endl;
      }
    }
    return true;
  } catch (IndexOutOfBoundsException e) {
    cout << "No faculty with id " << to_string(i) << " was found." << endl;
    return false;
  }
}

/* Adds a student to the database, with some ansillary faculty adding if desired.
*/
void DatabaseManager::AddStudent() {

  StackTrees();

  string temp;
  unsigned int id;
  while (true) {
    try {
      cout << "Enter student's ID (or type 'r' for random id): ";
      getline(cin, temp);
      if (tolower(temp[0]) == 'r') {
        srand(time(NULL));
        unsigned int rangeMin = studentTree->getMinKey();
        unsigned int rangeMax = studentTree->getMaxKey();
        if (rangeMin == rangeMax) {
          rangeMin = 100000;
          rangeMax = 200000;
        }
        id = rand() % (rangeMax - rangeMin) + rangeMin;
        while (studentTree->contains(id)) {
          id = rand() % (rangeMax - rangeMin) + rangeMin;
        }
        break;
      } else {
        id = (unsigned int)stoul(temp);
        if (studentTree->contains(id)) {
          cout << "There is already a student with the ID " << temp << ". Please enter another ID number." << endl;
        } else if (id == 0) {
          throw invalid_argument("0 is a reserved ID");
        } else {
          break;
        }
      }
    } catch (invalid_argument &ia) {
      cout << "Not a valid ID. Must be a positive integer (or 'r')." << endl;
    } catch (TreeEmptyException e) {
      id = rand() % 100000 + 100000;
      break;
    }
  }

  cout << "Enter student's name: ";
  getline(cin, temp);
  string name = temp;

  cout << "Enter student's level (Freshman, Sophomore, etc.): ";
  getline(cin, temp);
  string level = temp;

  cout << "Enter student's major: ";
  getline(cin, temp);
  string major = temp;

  double gpa;
  while (true) {
    cout << "Enter student's GPA: ";
    getline(cin, temp);
    try {
      gpa = stod(temp);
      break;
    } catch (invalid_argument &ia) {
      cout << "Not a valid GPA. Enter a decimal or integer." << endl;
    }
  }

  unsigned int advisor;
  while (true) {
    cout << "Enter student's advisor's ID (or 'n' for no advisor): ";
    getline(cin, temp);
    if (tolower(temp[0]) == 'n') {
      advisor = 0;
      break;
    } else {
      try {
        advisor = (unsigned int)stoul(temp);
        if (!facultyTree->contains(advisor)) {
          cout << "No faculty with the ID " << advisor << " was found. Would you like to create a faculty member with that ID?" << endl;
          getline(cin, temp);
          if (tolower(temp[0]) == 'y') {
            AddFaculty(advisor, id);
            break;
          } else {
            continue;
          }
        }
        break;
      } catch (invalid_argument &ia) {
        cout << "Not a valid ID. Try again." << endl;
      }
    }
  }

  Student* newStu = new Student(id, name, level, major, gpa, advisor);
  studentTree->insert(id, newStu);

  if (newStu->GetAdvisor() != 0) {
    facultyTree->findData(advisor)->AddAdvisee(id);
  }

}

/* A student adding variant, only used when adding a student within a faculty creation.
* @param unsigned int id: ID of new student.
* @param unsigned int adv: ID of new student's advisor.
*/
void DatabaseManager::AddStudent(unsigned int id, unsigned int adv) {

  string temp;

  cout << "Enter student's name: ";
  getline(cin, temp);
  string name = temp;

  cout << "Enter student's level (Freshman, Sophomore, etc.): ";
  getline(cin, temp);
  string level = temp;

  cout << "Enter student's major: ";
  getline(cin, temp);
  string major = temp;

  double gpa;
  while (true) {
    cout << "Enter student's GPA: ";
    getline(cin, temp);
    try {
      gpa = stod(temp);
      break;
    } catch (invalid_argument &ia) {
      cout << "Not a valid GPA. Enter a decimal or integer." << endl;
    }
  }

  Student* newStu = new Student(id, name, level, major, gpa, adv);
  studentTree->insert(id, newStu);

}

/* Adds a faculty member to database.
*/
void DatabaseManager::AddFaculty() {

  StackTrees();

  string temp;
  unsigned int id;
  while (true) {
    try {
      cout << "Enter faculty's id (or type 'r' for random id): ";
      getline(cin, temp);
      if (tolower(temp[0]) == 'r') {
        srand(time(NULL));
        unsigned int rangeMin = facultyTree->getMinKey();
        unsigned int rangeMax = facultyTree->getMaxKey();
        if (rangeMin == rangeMax) {
          rangeMin = 100000;
          rangeMax = 200000;
        }
        id = rand() % (rangeMax - rangeMin) + rangeMin;
        while (facultyTree->contains(id)) {
          id = rand() % (rangeMax - rangeMin) + rangeMin;
        }
        break;
      } else {
        id = (unsigned int)stoul(temp);
        if (facultyTree->contains(id)) {
          cout << "There is already a faculty with the id " << temp << ". Please enter another id number." << endl;
        } else if (id == 0) {
          throw invalid_argument("0 is a reserved ID");
        } else {
          break;
        }
      }
    } catch (invalid_argument &ia) {
      cout << "Not a valid ID. Must be a positive integer (or 'r')." << endl;
    } catch (TreeEmptyException e) {
      id = rand() % 100000 + 100000;
      break;
    }
  }

  cout << "Enter faculty's name: ";
  getline(cin, temp);
  string name = temp;

  cout << "Enter faculty's level (Lecturer, Associate Professor, etc.): ";
  getline(cin, temp);
  string level = temp;

  cout << "Enter faculty's department: ";
  getline(cin, temp);
  string department = temp;

  DLL<unsigned int>* advisees = new DLL<unsigned int>();
  while (true) {
    cout << "Would you like to add an advisee (will override student's current advisor)?" << endl;
    getline(cin, temp);
    if (tolower(temp[0]) == 'y') {
      try {
        cout << "Enter advisee ID: ";
        getline(cin, temp);
        unsigned int advisee = (unsigned int)stoul(temp);
        if (!studentTree->contains(advisee)) {
          cout << "No student with the ID " << advisee << " was found. Would you like to create a student with that ID?" << endl;
          getline(cin, temp);
          if (tolower(temp[0]) == 'y') {
            AddStudent(advisee, id);
            advisees->insertFront(advisee);
          } else {
            continue;
          }
        } else {
          advisees->insertFront(advisee);
        }
      } catch (invalid_argument &ia) {
        cout << "Not a valid ID. Try again." << endl;
      }
    } else {
      break;
    }
  }

  Faculty* newFac = new Faculty(id, name, level, department, advisees);
  facultyTree->insert(id, newFac);

  for (int i = 0; i < advisees->getCount(); ++i) {
    unsigned int oldFac = studentTree->findData(advisees->valAtIndex(i))->GetAdvisor();
    studentTree->findData(advisees->valAtIndex(i))->SetAdvisor(id);
    if (oldFac != 0 && oldFac != id) {
      facultyTree->findData(oldFac)->RemoveAdvisee(advisees->valAtIndex(i));
    }
  }

}

/* Adds a faculty member given an ID and ID of its advisee.
* @param unsigned int id: new faculty ID.
* @param unsigned int adv: ID of the new faculty's advisee.
*/
void DatabaseManager::AddFaculty(unsigned int id, unsigned int adv) {
  string temp;

  cout << "Enter faculty's name: ";
  getline(cin, temp);
  string name = temp;

  cout << "Enter faculty's level (Lecturer, Associate Professor, etc.): ";
  getline(cin, temp);
  string level = temp;

  cout << "Enter faculty's department: ";
  getline(cin, temp);
  string department = temp;

  DLL<unsigned int>* advisees = new DLL<unsigned int>();

  Faculty* newFac = new Faculty(id, name, level, department, advisees);
  facultyTree->insert(id, newFac);

}

/* Adds a faculty member given an ID and a list of IDs of its advisee.
* @param unsigned int id: new faculty ID.
* @param DLL<unsigned int>* adv: A list of IDs of the new faculty's advisees.
*/
void DatabaseManager::AddFaculty(unsigned int id, DLL<unsigned int>* adv) {
  string temp;

  cout << "Enter faculty's name: ";
  getline(cin, temp);
  string name = temp;

  cout << "Enter faculty's level (Lecturer, Associate Professor, etc.): ";
  getline(cin, temp);
  string level = temp;

  cout << "Enter faculty's department: ";
  getline(cin, temp);
  string department = temp;

  Faculty* newFac = new Faculty(id, name, level, department, adv);
  facultyTree->insert(id, newFac);

  for (int i = 0; i < adv->getCount(); ++i) {
    studentTree->findData(adv->valAtIndex(i))->SetAdvisor(id);
  }

}

/* Deletes a student given the ID.
* @param unsigned int i: student ID to delete
* @return bool: true if Student deletd, false otherwise
*/
bool DatabaseManager::DeleteStudent(unsigned int i) {

  StackTrees();

  if (!studentTree->contains(i)) {
    cout << "No student with ID " << i << " was found." << endl;
    return false;
  }

  unsigned int temp = studentTree->findData(i)->GetAdvisor();
  studentTree->remove(i);
  if (temp != 0) {
    facultyTree->findData(temp)->RemoveAdvisee(i);
  }
  return true;

}

/* Deletes a faculty given the ID. Offers a few advisee reassignment options.
* @param unsigned int i: faculty ID to delete
* @return bool: true if faculty deletd, false otherwise
*/
bool DatabaseManager::DeleteFaculty(unsigned int i) {

  StackTrees();

  if (!facultyTree->contains(i)) {
    cout << "No faculty with ID " << i << " was found." << endl;
    return false;
  }

  Faculty* temp = facultyTree->findData(i);
  if (temp->GetAdvisees()->getCount() > 0) {
    while (true) {
      cout << "Faculty member " << i << " has " << temp->GetAdvisees()->getCount() << " advisees. How would you like to proceed?" << endl;
      cout << "\t1. Reassign all advisees to another advisor together" << endl;
      cout << "\t2. Individually reassign advisees" << endl; // Ew
      cout << "\t3. Set all advisees to 'No Advisor'" << endl;
      cout << "\t4. Cancel faculty deletion";
      cout << "Enter number of option: ";
      string option;
      getline(cin, option);
      if (option[0] == '1') {

        unsigned int advisor;
        while (true) {
          cout << "Enter students' advisor's ID (or 'n' for no advisor): ";
          getline(cin, option);
          if (tolower(option[0]) == 'n') {
            advisor = 0;
            break;
          }
          try {
            advisor = (unsigned int)stoul(option);
            if (!facultyTree->contains(advisor)) {
              cout << "No faculty with the ID " << advisor << " was found. Would you like to create a faculty member with that ID?" << endl;
              getline(cin, option);
              if (tolower(option[0]) == 'y') {
                AddFaculty(advisor, temp->GetAdvisees());
                break;
              } else {
                continue;
              }
            } else {
              Faculty* newAdv = facultyTree->findData(advisor);
              for (int i = 0; i < temp->GetAdvisees()->getCount(); ++i) {
                studentTree->findData(temp->GetAdvisees()->valAtIndex(i))->SetAdvisor(advisor);
                newAdv->AddAdvisee(temp->GetAdvisees()->valAtIndex(i));
              }
              break;
            }
          } catch (invalid_argument &ia) {
            cout << "Not a valid ID. Try again." << endl;
          }
        }
        break;

      } else if (option[0] == '2') {

        DLL<unsigned int>* adviseeList = temp->GetAdvisees();
        for (int i = 0; i < adviseeList->getCount(); ++i) {

          unsigned int advisor;
          while (true) {
            cout << "Enter students' advisor's ID (or 'n' for no advisor): ";
            getline(cin, option);
            if (tolower(option[0]) == 'n') {
              advisor = 0;
              break;
            }
            try {
              advisor = (unsigned int)stoul(option);
              if (!facultyTree->contains(advisor)) {
                cout << "No faculty with the ID " << advisor << " was found. Please try again." << endl;
                continue;
              } else {
                Faculty* newAdv = facultyTree->findData(advisor);
                studentTree->findData(adviseeList->valAtIndex(i))->SetAdvisor(advisor);
                newAdv->AddAdvisee(adviseeList->valAtIndex(i));
                break;
              }
            } catch (invalid_argument &ia) {
              cout << "Not a valid ID. Try again." << endl;
            }
          }

        }
        break;

      } else if (option[0] == '3') {

        for (int i = 0; i < temp->GetAdvisees()->getCount(); ++i) {
          studentTree->findData(temp->GetAdvisees()->valAtIndex(i))->SetAdvisor(0);
        }
        break;

      } else if (option[0] == '4'){

        return false;

      } else {

        cout << "Invalid selection. Please try again." << endl;

      }
    }
  }
  temp = NULL;
  facultyTree->remove(i);
  return true;

}

/* Changes a student's advisor given both IDs.
* @param unsigned int iStu: target student ID
* @param unsigned int iFac: target faculty ID.
* @return bool: true if student and advisor IDs found.
*/
bool DatabaseManager::SetAdvisor(unsigned int iStu, unsigned int iFac) {

  StackTrees();

  bool abort = false;
  if (!studentTree->contains(iStu)) {
    cout << "Error: no student with the ID " << iStu << " was found." << endl;
    abort = true;
  }
  if (!facultyTree->contains(iFac)) {
    cout << "Error: no faculty with the ID " << iFac << " was found." << endl;
    abort = true;
  }
  if (abort) {
    return false;
  }

  Student* tempStu = studentTree->findData(iStu);
  if (tempStu->GetAdvisor() != 0) {
    facultyTree->findData(tempStu->GetAdvisor())->RemoveAdvisee(iStu);
  }
  tempStu->SetAdvisor(iFac);
  facultyTree->findData(iFac)->AddAdvisee(iStu);
  return true;

}

/* Removes an advisee from an advisor's list.
* @param unsigned int iFac: target faculty ID.
* @param unsigned int iStu: target student ID
* @return bool: true if faculty and advisee IDs found.
*/
bool DatabaseManager::RemoveAdvisee(unsigned int iFac, unsigned int iStu) {

  StackTrees();

  if (!facultyTree->contains(iFac)) {
    cout << "No faculty with ID " << iFac << " found." << endl;
    return false;
  }

  Faculty* tempFac = facultyTree->findData(iFac);
  if (!tempFac->GetAdvisees()->deleteFirst(iStu)) {
    cout << "Faculty member " << iFac << " has no advisee " << iStu << "." << endl;
    return false;
  }

  cout << "Student " << iStu << " now has no advisor. Select an option." << endl;
  cout << "\t1. Assign a new advisor" << endl;
  cout << "\t2. Leave student without advisor" << endl;
  cout << "Enter option number: ";
  string temp;
  getline(cin, temp);

  if (temp[0] == '1') {
    while (true) {
      cout << "Enter ID of advisor: ";
      getline(cin, temp);
      unsigned int newFac;
      try {
        newFac = (unsigned int)stoul(temp);
        if (SetAdvisor(iStu, newFac)) {
          return true;
        }
      } catch (invalid_argument &ia) {
        cout << "Not a valid ID. Try again." << endl;
      }
    }
  } else {
    studentTree->findData(iStu)->SetAdvisor(0);
    return true;
  }

}

/* Pushes a copy of database to stack, used for rollback
*/
void DatabaseManager::StackTrees() {

  BST<unsigned int, Student*>* verStuTree = new BST<unsigned int, Student*>(studentTree);
  BST<unsigned int, Faculty*>* verFacTree = new BST<unsigned int, Faculty*>(facultyTree);
  pair <BST<unsigned int, Student*>*, BST<unsigned int, Faculty*>*>* newVer = new pair<BST<unsigned int, Student*>*, BST<unsigned int, Faculty*>*>(verStuTree, verFacTree);
  rollbackStack->push(newVer);

}

/* Restores database to a previous version.
* NOTE: Only restores tree structure, not details of individual students/faculty. If you rollback creating a faculty whom you then set as students' advisor, the old versions of students will need their advisors reset.
*/
void DatabaseManager::Rollback() {

  try {
    pair <BST<unsigned int, Student*>*, BST<unsigned int, Faculty*>* >* lastVer = rollbackStack->pop();
    studentTree = NULL;
    studentTree = lastVer->first;
    facultyTree = NULL;
    facultyTree = lastVer->second;
  } catch (ListEmptyException e) {
    cout << "Rollback stack empty. No further rollback possible." << endl;
  }
}

/* Quits program
*/
void DatabaseManager::Exit() {
  WriteDB();
}

/* Saves database to studentTable and facultyTable
*/
void DatabaseManager::WriteDB() {

  ofstream stuOut("studentTable");
  text_oarchive oarStu(stuOut);
  oarStu & studentTree;
  stuOut.close();

  ofstream facOut("facultyTable");
  text_oarchive oarFac(facOut);
  oarFac & facultyTree;
  facOut.close();

}
