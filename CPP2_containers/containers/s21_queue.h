#ifndef CPP2_S21_CONTAINERS_QUEUE_H_
#define CPP2_S21_CONTAINERS_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = list<T>>
class queue {
 public:
  // Queue Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // Stack Member functions
  queue() : container_() {}
  queue(std::initializer_list<value_type> const &items) : container_(items) {}
  queue(const queue &s) : container_(s.container_) {}
  queue(queue &&s) : container_(std::move(s.container_)) {}
  ~queue(){};
  queue &operator=(queue &&s) {
    this->container_ = std::move(s.container_);
    return *this;
  }

  // Stack Element access

  const_reference front() { return container_.front(); }
  const_reference back() { return container_.back(); }

  // Stack Capacity
  bool empty() { return container_.empty(); }
  size_type size() { return container_.size(); }

  // Stack Modifiers
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_front(); }
  void swap(queue &other) { container_.swap(other.container_); }

  // Реализация методов insert_many
  template <typename... Args>
  void insert_many_back(Args &&... args) {
    for (auto &&arg : {std::forward<Args>(args)...}) {
      container_.push_back(std::forward<decltype(arg)>(arg));
    }
  }

 private:
  Container container_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_QUEUE_H_