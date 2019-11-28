# cpsc350-BSTDB
A binary search tree-based database.

Lloyd Black
2295968
CPSC350, Section 2
Rene German

A program that operates a database of Students and Faculty.

1. Source Files - main.cpp, BST.h, DatabaseManager.h, DatabaseManager.cpp, DLL.h, Faculty.h, Faculty.cpp, FileNotFoundException.h, FileNotFoundException.cpp, IndexOutOfBoundsException.h, IndexOutOfBoundsException.cpp, ListEmptyException.h, ListEmptyException.cpp, Node.h, Person.h, Person.cpp, Stack.h, Student.h, Student.cpp, TreeEmptyException.h, TreeEmptyException.cpp, TreeNode.h

2. Issues - Rollback only restores tree structure, not details of individual students/faculty. For instance, if you rollback creating a faculty whom you then set as students' advisor, the old versions of students will need their advisors reset.

3. Resources - cplusplus.com/reference, stackoverflow, tutorialspoint, and Data Structures and Algorithms in C (by Goodrich, Tamassia, and Mount).

4. Description of Program - Prompts user on one of 14 database management options such as adding and deleting student and faculty records, printing records, and modifying records. When altering interrelationships of students and faculty, updates all corresponding records as necessary. When told to exit, writes database to a couple files, which it then reads back in upon next running.

5. After compiling - ./YOURFILEOUT.out

6. NOTE: Requires the Boost library in the same directory, with boost_serialization binaries built. Failure to add files will result in failure to compile.
