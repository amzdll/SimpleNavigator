#include "s21_stack.h"

// Constructors
namespace s21 {
template <class T>
stack<T>::stack() : list<T>() {}

template <class T>
stack<T>::stack(size_type n) : list<T>(n) {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : list<T>(items) {}

template <class T>
stack<T>::stack(const stack &s) : list<T>(s) {}

template <class T>
stack<T>::stack(stack &&s) : list<T>(std::move(s)) {}

template <class T>
stack<T>::~stack() = default;

// Overload operators
template <class T>
stack<T> stack<T>::operator=(stack &&s) {
  list<T>::clear();
  list<T>::MoveList(s);
  return *this;
}

// Element access
template <class T>
typename stack<T>::const_reference stack<T>::top() const {
  return list<T>::back();
}

// Modifiers
template <class T>
void stack<T>::push(const_reference value) {
  list<T>::push_back(value);
}

template <class T>
void stack<T>::pop() {
  list<T>::pop_back();
}
}  // namespace s21