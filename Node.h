#ifndef NODE
#define NODE

#include <cstdlib>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/* A generic node for a doubly linked list.
*/
template <class T>
class Node
{
  public:
    T data;
    Node* next;
    Node* prev;

    Node() {
      // data left uninitialized
      next = NULL;
      prev = NULL;
    }
    Node(T d) {
      data = d;
      next = NULL;
      prev = NULL;
    }

  private:
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned version) {
      ar & data;
      ar & next;
      ar & prev;
    }

};

#endif
