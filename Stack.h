#ifndef STACK_H
#define STACK_H

#include "DLL.h"
#include <cstdlib>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
using namespace boost::serialization;

/* Template stack class, doubly linked list based. Serializeable.
*/
template <class T>
class Stack
{

  public:

    Stack<T>() {
      size = 128;
      list = new DLL<T>;
    }
    Stack<T>(int s) {
      size = s;
      list = new DLL<T>;
    }

    void push(T d) {
      if (list->getCount() == size) {
        list->removeFront();
        list->insertRear(d);
      } else {
        list->insertRear(d);
        size++;
      }
    }
    T pop() {
      if (list->isEmpty()) {
        throw ListEmptyException();
      } else {
        return list->removeRear();
        size--;
      }
    }
    T peek() {
      if (list->isEmpty()) {
        throw ListEmptyException();
      } else {
        return list->peekRear();
      }
    }
    int getSize() {
      return size;
    }

  private:
    int size;
    DLL<T>* list;

    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & size;
      ar & list;
    }

};

#endif
