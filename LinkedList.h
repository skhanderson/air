#pragma once

#include <functional>
#include <exception>
#include <unistd.h>

using namespace std;

template<class T> class LinkedList;
template<class T> class LinkedListIterator;

template<class T>
class LinkedListNode {
  friend LinkedList<T>;
  friend LinkedListIterator<T>;
 private:
  T v;
  LinkedListNode<T> *nx;
 LinkedListNode(T value, LinkedListNode<T>* nxt) : v(value), nx(nxt) {}
};

class LinkedListError: public runtime_error {
 public:
 LinkedListError(): runtime_error("Linked List Error") {}
};

template<class T>
class LinkedListIterator {
  friend LinkedList<T>;
 private:
  LinkedListNode<T> **ref;
  LinkedListIterator<T> (LinkedListNode<T> **r): ref(r) { }
  static LinkedListIterator<T> end(const LinkedList<T> &list) {
    return LinkedListIterator<T>(list.endptr);
  }
  LinkedListIterator<T>(LinkedList<T> &list) {
    ref = &list.list;
  }
 public:
  LinkedListIterator<T>() {
    ref = nullptr;
  }
  LinkedListIterator<T>(const LinkedListIterator<T> &it) {
    ref = it.ref;
  }
  T& operator*() {
    if (ref == nullptr || *ref == nullptr) {
      throw LinkedListError();
    }
    return (*ref)->v;
  }
  bool operator==(LinkedListIterator<T> other) {
    return ref == other.ref;
  }
  bool operator!=(LinkedListIterator<T> other) {
    return ref != other.ref;
  }
  LinkedListIterator<T> &operator++() {
    if (ref == nullptr || *ref == nullptr) {
      throw LinkedListError();
    }
    ref = &((*ref)->nx);
    return *this;
  }
  LinkedListIterator<T> operator++(int) {
    if (ref == nullptr || *ref == nullptr) {
      throw LinkedListError();
    }
    LinkedListIterator ret = *this;
    ref = &((*ref)->nx);
    return ret;
  }
};

template<class T>
class LinkedList {
  friend LinkedListIterator<T>;
private:
  LinkedListNode<T> *list;
  LinkedListNode<T> **endptr;
  void free_storage() {
    LinkedListNode<T> *nx = list;
    list = nullptr;
    endptr = &list;
    while (nx != nullptr) {
      LinkedListNode<T> *tmp = nx->nx;
      delete nx;
      nx = tmp;
    }
  }
  void do_copy(const LinkedList<T> &copy) {
    list = nullptr;
    endptr = &list;
    for (LinkedListNode<T> *p = copy.list; p != nullptr; p = p->nx) {
      push_front(p->v);
    }
    reverse_iterative();
  }    
 public:
  typedef LinkedListIterator<T> iterator;
  LinkedList<T>() {
    list = nullptr;
    endptr = &list;
  }
  LinkedListIterator<T> begin() {
    return LinkedListIterator<T>(*this);
  }
  LinkedListIterator<T> end() {
    return LinkedListIterator<T>::end(*this);
  }
  ~LinkedList<T>() {
    free_storage();
  }
  LinkedList(const LinkedList<T> &copy) {
    do_copy(copy);
  }
  LinkedList &operator=(const LinkedList<T> &copy) {
    free_storage();
    do_copy(copy);
  }
  void push_front(T v) {
    LinkedListNode<T> *tmp = new LinkedListNode<T>(v, list);
    list = tmp;
    if (endptr == &list) {
      endptr = &tmp->nx;
    }
  }
  void push_back(T v) {
    LinkedListNode<T> *tmp = new LinkedListNode<T>(v, nullptr);
    *endptr = tmp;
    endptr = &tmp->nx;
  }
  void insert(size_t position, T v) {
    LinkedListNode<T> *p = &list;
    for (size_t i = 0; *p != nullptr && i < position; i++) {
      p = &(*p)->nx;
    }
    LinkedListNode<T> *tmp = new LinkedListNode<T>(v, *p);
    if (p == endptr) {
      endptr = &tmp->nx;
    }
    *p = tmp;
  }
  void reverse_iterative() {
    if (list == nullptr) {
      return;
    }
    LinkedListNode<T> *res = list;
    list = nullptr;
    endptr = &res->nx;
    while (res != nullptr) {
      LinkedListNode<T> *tmp = res->nx;
      res->nx = list;
      list = res;
      res = tmp;
    }
  }
  // This is tail recursive, so the compiler can convert to iteration.
  LinkedListNode<T> *reverse_recursive_aux(LinkedListNode<T> *l,
					   LinkedListNode<T> *res) {
    if (l == nullptr) {
      return res;
    }
    LinkedListNode<T> *tmp = l->nx;
    l->nx = res;
    return reverse_recursive_aux(tmp, l);
  }
  void reverse_recursive() {
    if (list == nullptr) {
      return;
    }
    endptr = &list->nx;
    list = reverse_recursive_aux(list, nullptr);
  }
};
