#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include "Node.h"
#include "ListEmptyException.h"
#include "IndexOutOfBoundsException.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/* A generic doubly linked list.
*/
template <class T>
class DLL
{

  private:
    Node<T>* front;
    Node<T>* rear;
    int count;

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & front;
      ar & rear;
      ar & count;
    }

  public:

    /* Default Constructor. Creates an empty list.
    */
    DLL() {
      front = NULL;
      rear = NULL;
      count = 0;
    }

    /* Destructor. Iterates through list, deleting all nodes.
    */
    ~DLL() {
      if (front == NULL) {
        return;
      } else {
        Node<T>* curr = front;
        while (curr->next != NULL) {
          curr = curr->next;
          Node<T>* prev = curr->prev;
          prev->next = NULL;
          prev->prev = NULL;
          curr->prev = NULL;
          delete prev;
        }
        delete curr;
      }
    }


    /* Inserts data to the front of the list.
    * @param T d: the data to be inserted of template type.
    */
    void insertFront(T d) {
      Node<T>* node = new Node<T>(d);
      if (front == NULL) {
        rear = node;
      } else {
        node->next = front;
        front->prev = node;
      }
      front = node;
      count++;
    }

    /* Inserts data to the rear of the list.
    * @param T d: the data to be inserted of template type.
    */
    void insertRear(T d) {
      Node<T>* node = new Node<T>(d);
      if (rear == NULL) {
        front = node;
      } else {
        node->prev = rear;
        rear->next = node;
      }
      rear = node;
      count++;
    }

    /* Inserts a new node into the list at a specified index, throwing exceptions for out of bounds indeces as necessary.
    * @param int idx: the index at which to insert the data. -1 treated as the end of the list, -2 as second from the end, etc.
    * @param T d: the data to be inserted.
    */
    void insertAt(int idx, T d) {
      if (idx == 0) {
        insertFront(d);
      } else if (idx == count || idx == -1) {
        insertRear(d);
      } else {
        Node<T>* node = new Node<T>(d);
        Node<T>* temp = findAtIndex(idx);
        node->next = temp;
        node->prev = temp->prev;
        temp->prev->next = node;
        temp->prev = node;
        count++;
      }
    }

    /* Removes and returns the data at the beginning of the list.
    * @return T: data in the node at the beginning of the list.
    */
    T removeFront() {
      if (isEmpty()) {
        throw ListEmptyException();
      } else {
        T d = front->data;
        Node<T>* ft = front;
        if (front->next == NULL) {
          rear = NULL;
        } else {
          front->next->prev = NULL;
        }
        front = front->next;
        ft->next = NULL;
        delete ft;
        count--;
        return d;
      }
    }

    /* Removes and returns the data at the end of the list.
    * @return T: data in the node at the end of the list.
    */
    T removeRear(){
      if (isEmpty()) {
        throw ListEmptyException();
      } else {
        T d = rear->data;
        Node<T>* rr = rear;
        if (rear->prev == NULL) {
          front = NULL;
        } else {
          rear->prev->next = NULL;
        }
        rear = rear->prev;
        rr->prev = NULL;
        delete rr;
        count--;
        return d;
      }
    }

    /* Removes and returns the data at the specified index.
    * @param int idx: the index at which to insert the data. -1 treated as the end of the list, -2 as second from the end, etc.
    * @return T: data in the node at the end of the list.
    */
    T removeAt(int idx) {
      if (isEmpty()) {
        throw ListEmptyException("List Empty");
      } else if (idx == 0) {
        return removeFront();
      } else if (idx == count || idx == -1) {
        return removeRear();
      } else {
        Node<T>* temp = findAtIndex(idx);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->next = NULL;
        temp->prev = NULL;
        T d = temp->data;
        delete temp;
        count--;
        return d;
      }
    }

    /* Deletes the first instance of argument data in the list.
    * @param T d: the data that, if matched, will be deleted.
    * @return bool: true if matching value found and deleted, false otherwise.
    */
    bool deleteFirst(T d) {
      if (isEmpty()) {
        return false;
      } else {
        Node<T>* curr = findFirst(d);
        if (curr == NULL) {
          return false;
        } else if (curr->next == NULL) { //last element
          removeRear();
          return true;
        } else if (curr->prev == NULL) { // first element
          removeFront();
          return true;
        } else {
          curr->prev->next = curr->next;
          curr->next->prev = curr->prev;
          curr->next = NULL;
          curr->prev = NULL;
          delete curr;
          count--;
          return true;
        }
      }
    }

    /* Deletes the last instance of argument data in the list.
    * @param T d: the data that, if matched, will be deleted.
    * @return bool: true if matching value found and deleted, false otherwise.
    */
    bool deleteLast(T d) {
      if (isEmpty()) {
        return false;
      } else {
        Node<T>* curr = findLast(d);
        if (curr == NULL) {
          return false;
        } else if (curr->next == NULL) { //last element
          removeRear();
          return true;
        } else if (curr->prev == NULL) { // first element
          removeFront();
          return true;
        } else {
          curr->prev->next = curr->next;
          curr->next->prev = curr->prev;
          curr->next = NULL;
          curr->prev = NULL;
          delete curr;
          count--;
          return true;
        }
      }
    }

    /* Searches list for data matching argument.
    * @param T d: data to be searched for.
    * @return bool: true if matching data found, false otherwise.
    */
    bool contains(T d) {
      if (isEmpty()) {
        return false;
      } else {
        Node<T>* curr = front;
        while (curr != NULL) {
          if (curr->data == d) {
            return true;
          }
          curr = curr->next;
        }
        return false;
      }
    }

    /* Finds the node at the specified index.
    * @param int idx: the index at which to insert the data. -1 treated as the end of the list, -2 as second from the end, etc.
    * @return Node<T>*: a pointer to the node located at the specified index, or NULL if list is empty.
    */
    Node<T>* findAtIndex(int idx) {
      if (isEmpty()) {
        return NULL;
      } else if (idx < 0) {
        idx = count+idx;
        if (idx < 0) {
          throw IndexOutOfBoundsException("Index out of bounds");
        }
      } else if (idx >= count) {
        throw IndexOutOfBoundsException("Index out of bounds");
      }
      Node<T>* curr = front;
      for (int i = 0; i < idx; ++i) {
        curr = curr->next;
        if (curr == NULL) {
          return NULL;
        }
      }
      return curr;
    }

    /* Finds the data at the specified index.
    * @param int idx: the index at which to insert the data. -1 treated as the end of the list, -2 as second from the end, etc.
    * @return T: data located at the specified index, or NULL if list is empty.
    */
    T valAtIndex(int idx) {
      if (isEmpty()) {
        throw ListEmptyException("List Empty");
      } else if (idx < 0) {
        idx = count+idx;
        if (idx < 0) {
          throw IndexOutOfBoundsException("Index out of bounds");
        }
      } else if (idx >= count) {
        throw IndexOutOfBoundsException("Index out of bounds");
      }
      Node<T>* curr = front;
      for (int i = 0; i < idx; ++i) {
        curr = curr->next;
      }
      return curr->data;
    }

    /* Finds the first node matching the argument data.
    * @param T d: data to be searched for.
    * @return Node<T>*: a pointer to the first node matching argument data, or NULL if no such node exists.
    */
    Node<T>* findFirst(T d) {
      if (isEmpty()) {
        return NULL;
      } else {
        Node<T>* curr = front;
        while (curr->data != d) {
          curr = curr->next;
          if (curr == NULL) {
            return NULL;
          }
        }
        return curr;
      }
    }

    /* Searches List for first data matching argument and returns its index.
    * @param T d: data to be searched for.
    * @return int: the index of the first matching data value, or -1 if no such node exists.
    */
    int findFirstIndex(T d) {
      if (isEmpty()) {
        return -1;
      } else {
        Node<T>* curr = front;
        int idx = 0;
        while (curr->data != d) {
          curr = curr->next;
          ++idx;
          if (curr = NULL) {
            return -1;
          }
        }
        return idx;
      }
    }

    /* Finds the last node matching the argument data.
    * @param T d: data to be searched for.
    * @return Node<T>*: a pointer to the last node matching argument data, or NULL if no such node exists.
    */
    Node<T>* findLast(T d) {
      if (isEmpty()) {
        return NULL;
      } else {
        Node<T>* curr = rear;
        while (curr->data != d) {
          curr = curr->prev;
          if (curr == NULL) {
            return NULL;
          }
        }
        return curr;
      }
    }

    /* Searches List for last data matching argument and returns its index.
    * @param T d: data to be searched for.
    * @return int: the index of the last matching data value, or -1 if no such node exists.
    */
    int findLastIndex(T d) {
      if (isEmpty()) {
        return -1;
      } else {
        Node<T>* curr = rear;
        int idx = count-1;
        while (curr->data != d) {
          curr = curr->prev;
          --idx;
          if (curr = NULL) {
            return -1;
          }
        }
        return idx;
      }
    }


    /* Shows data at front.
    @return T: data at front of list.
    */
    T peekFront() {
      return front->data;
    }
    /* Shows data at rear.
    * @return T: data at end of list.
    */
    T peekRear() {
      return rear->data;
    }

    /* Returns count.
    * @return int: the number of elements in the list.
    */
    int getCount() {
      return count;
    }
    /* Returns whether or not the list is empty.
    * @return bool: true if list has no elements, false otherwise.
    */
    bool isEmpty() {
      return (count == 0);
    }
    /* Iterates through list and prints each element to cout (one element per line).
    */
    void printList() {
      Node<T>* curr = front;
      while (curr != NULL) {
        cout << curr->data << endl;
        curr = curr->next;
      }
    }

};

#endif
