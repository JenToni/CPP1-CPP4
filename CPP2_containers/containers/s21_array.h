#ifndef CPP2_S21_CONTAINERS_ARRAY_H_
#define CPP2_S21_CONTAINERS_ARRAY_H_

#include <initializer_list>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  // Array Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  // Array Member functions

  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a) noexcept;
  ~array();
  array<value_type, N>& operator=(array&& a) noexcept;

  // Array Element access

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Array Iterators
  iterator begin();
  iterator end();

  // Array Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Array Modifiers
  void swap(array& other);
  void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type data_[N]{};
};

// Array Element access

template <typename value_type, std::size_t N>
array<value_type, N>::array() {}

template <typename value_type, std::size_t N>
array<value_type, N>::array(std::initializer_list<value_type> const& items) {
  for (size_type i = 0; i < size_; ++i) data_[i] = *(items.begin() + i);
}

template <typename value_type, std::size_t N>
array<value_type, N>::array(const array& a) {
  for (size_type i = 0; i < N; ++i) data_[i] = a.data_[i];
}
template <typename value_type, std::size_t N>
array<value_type, N>::array(array&& a) noexcept {
  swap(a);
}
template <typename value_type, std::size_t N>
array<value_type, N>::~array() {}

template <typename value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::at(
    size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out range");
  }
  return data_[pos];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::array& array<value_type, N>::operator=(
    array&& a) noexcept {
  if (this != &a) {
    swap(a);
  }
  return *this;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::reference array<value_type, N>::operator[](
    size_type pos) {
  return *(data_ + pos);
}
template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::front() {
  return *data_;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::const_reference array<value_type, N>::back() {
  return data_[size_ - 1];
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::data() {
  return data_;
}

// Array Iterators

template <typename value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::begin() {
  return data_;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::iterator array<value_type, N>::end() {
  return data_ + size_;
}

// Array Capacity

template <typename value_type, std::size_t N>
bool array<value_type, N>::empty() {
  return size() == 0;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::size_type array<value_type, N>::size() {
  return size_;
}

template <typename value_type, std::size_t N>
typename array<value_type, N>::size_type array<value_type, N>::max_size() {
  return size();
}

// Array Modifiers

template <typename value_type, std::size_t N>
void array<value_type, N>::swap(array& other) {
  for (size_type i = 0; i != size_; i++) {
    std::swap(this->data_[i], other.data_[i]);
  }
}

template <typename value_type, std::size_t N>
void array<value_type, N>::fill(const_reference value) {
  for (size_type i = 0; i != size_; i++) {
    data_[i] = value;
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_ARRAY_H_