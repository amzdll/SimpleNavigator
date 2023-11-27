#ifndef CONTAINERS_CPP_S21_QUEUE_S21_QUEUE_H_
#define CONTAINERS_CPP_S21_QUEUE_S21_QUEUE_H_

#include <iostream>

#include "./list.h"

namespace s21 {
template <class T>
class queue {
 public:
  // Members type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Constructors
  queue();
  queue(size_type n);
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();

  // Overload operators
  queue operator=(queue &&q);

  // Element access
  const_reference front() const;
  const_reference back() const;

  // Capacity
  bool empty() const;
  size_type size() const;

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue &other);

 private:
  s21::list<T> list;
};
}  // namespace s21

// Constructors
template <class T>
s21::queue<T>::queue() : list() {}

template <class T>
s21::queue<T>::queue(size_type n) : list(n) {}

template <class T>
s21::queue<T>::queue(std::initializer_list<value_type> const &items)
    : list(items) {}

template <class T>
s21::queue<T>::queue(const queue &q) : list(q.list) {}

template <class T>
s21::queue<T>::queue(queue &&q) : list(std::move(q.list)) {}

template <class T>
s21::queue<T>::~queue() {}

// Overload operators
template <class T>
s21::queue<T> s21::queue<T>::operator=(queue &&q) {
  list.clear();
  list.MoveList(q.list);
  return *this;
}

// Element access
template <class T>
typename s21::queue<T>::const_reference s21::queue<T>::front() const {
  return list.front();
}

template <class T>
typename s21::queue<T>::const_reference s21::queue<T>::back() const {
  return list.back();
}

// Capacity
template <class T>
bool s21::queue<T>::empty() const {
  return list.empty();
}

template <class T>
typename s21::queue<T>::size_type s21::queue<T>::size() const {
  return list.size();
}

// Modifiers
template <class T>
void s21::queue<T>::push(const_reference value) {
  list.push_back(value);
}

template <class T>
void s21::queue<T>::pop() {
  list.pop_front();
}

template <class T>
void s21::queue<T>::swap(queue &other) {
  list.swap(other.list);
}

#endif  // CONTAINERS_CPP_S21_QUEUE_S21_QUEUE_H_
