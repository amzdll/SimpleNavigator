#ifndef CONTAINERS_CPP_S21_STACK_S21_STACK_H_
#define CONTAINERS_CPP_S21_STACK_S21_STACK_H_

#include <iostream>

#include "./s21_list.hpp"

namespace s21 {
template <class T>
class stack {
 public:
  // Members type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Constructors
  stack();
  stack(size_type n);
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();

  // Overload operators
  stack operator=(stack &&s);

  // Element access
  const_reference top() const;

  // Capacity
  bool empty() const;
  size_type size() const;

  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

 private:
  s21::list<T> list;
};
}  // namespace s21

// Constructors
template <class T>
s21::stack<T>::stack() : list() {}

template <class T>
s21::stack<T>::stack(size_type n) : list(n) {}

template <class T>
s21::stack<T>::stack(std::initializer_list<value_type> const &items)
    : list(items) {}

template <class T>
s21::stack<T>::stack(const stack &s) : list(s.list) {}

template <class T>
s21::stack<T>::stack(stack &&s) : list(std::move(s.list)) {}

template <class T>
s21::stack<T>::~stack() {}

// Overload operators
template <class T>
s21::stack<T> s21::stack<T>::operator=(stack &&s) {
  list.clear();
  list.MoveList(s.list);
  return *this;
}

// Element access
template <class T>
typename s21::stack<T>::const_reference s21::stack<T>::top() const {
  return list.back();
}

// Capacity
template <class T>
bool s21::stack<T>::empty() const {
  return list.empty();
}

template <class T>
typename s21::stack<T>::size_type s21::stack<T>::size() const {
  return list.size();
}

// Modifiers
template <class T>
void s21::stack<T>::push(const_reference value) {
  list.push_back(value);
}

template <class T>
void s21::stack<T>::pop() {
  list.pop_back();
}

template <class T>
void s21::stack<T>::swap(stack &other) {
  list.swap(other.list);
}

#endif  // CONTAINERS_CPP_S21_STACK_S21_STACK_H_
