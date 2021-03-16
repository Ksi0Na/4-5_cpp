// Copyright 2021 Olga Molchanova OlgaMolchun5@gmail.com

#ifndef INCLUDE_NONCOPIEDSTACK_HPP_
#define INCLUDE_NONCOPIEDSTACK_HPP_

#include <iostream>
#include <type_traits>

#include "BaseStack.hpp"

template <typename T>
class NonCopiedStack : public BaseStack<T> {
 public:
  using BS = BaseStack<T>;
  void push(T &&value);
  T pop();
  template <typename... Args>
  void push_emplace(Args &&... value);
};

template <typename T>
void NonCopiedStack<T>::push(T &&value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *newElement = new Element<T>{std::forward<T>(value), BS::head_};
  BS::head_ = newElement;
}

template <typename T>
T NonCopiedStack<T>::pop() {
  if (!BS::head_) {
    throw std::out_of_range("Empty Stack!!!");
  }
  auto *upper = BS::head_;
  BS::head_ = BS::head_->previous;
  T value = std::move(upper->value);
  delete upper;
  return value;
}

template <typename T>
template <typename... Args>
void NonCopiedStack<T>::push_emplace(Args &&... value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *newElement = new Element<T>{{std::forward<Args>(value)...}, BS::head_};
  BS::head_ = newElement;
}
#endif  // INCLUDE_NONCOPIEDSTACK_HPP_
