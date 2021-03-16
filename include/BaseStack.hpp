// Copyright 2021 Olga Molchanova OlgaMolchun5@gmail.com

#ifndef INCLUDE_BASESTACK_HPP_
#define INCLUDE_BASESTACK_HPP_

#include <stdexcept>
#include <utility>

template <class T>
struct Element {
  T value;
  Element<T> *previous = nullptr;
};
template <typename T>
class BaseStack {
 public:
  // Default generation of empty and move constructs
  BaseStack() = default;
  BaseStack(BaseStack &&st) noexcept = default;
  auto operator=(BaseStack &&st) noexcept -> BaseStack & = default;
  // No copy constructor and assignable operator
  BaseStack(const BaseStack &st) = delete;
  auto operator=(const BaseStack &st) -> BaseStack & = delete;
  // Methods
  void push(T &&value);
  const T &head() const;
  // Destructor
  ~BaseStack();

 protected:
  Element<T> *head_ = nullptr;
};

template <typename T>
void BaseStack<T>::push(T &&value) {
  auto *newElement = new Element<T>{std::forward<T>(value), head_};
  head_ = newElement;
}

template <typename T>
const T &BaseStack<T>::head() const {
  if (!head_) {
    throw std::out_of_range("Empty Stack!!!");
  }
  return head_->value;
}

template <typename T>
BaseStack<T>::~BaseStack() {
  while (head_) {
    auto *current = head_;
    head_ = head_->previous;
    delete current;
  }
}

#endif  // INCLUDE_BASESTACK_HPP_
