#ifndef CPP2_S21_CONTAINERS_STACK_H_
#define CPP2_S21_CONTAINERS_STACK_H_

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = list<T>>
class stack {
 public:
  // Stack Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Stack Member functions
  stack() : container_(){};
  stack(std::initializer_list<value_type> const &items) : container_(items){};
  stack(const stack &s) : container_(s.container_) {}
  stack(stack &&s) : container_(std::move(s.container_)) {}
  ~stack(){};
  stack &operator=(stack &&s) {
    this->container_ = std::move(s.container_);
    return *this;
  }

  // Stack Element access
  const_reference top() { return container_.back(); }

  // Stack Capacity
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }

  // Stack Modifiers
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  void swap(stack &other) { container_.swap(other.container_); }

  // Реализация методов insert_many
  template <typename... Args>
  void insert_many_front(Args &&... args) {
    for (auto &&arg : {std::forward<Args>(args)...}) {
      container_.push_back(std::forward<decltype(arg)>(arg));
    }
  }

 private:
  Container container_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_STACK_H_