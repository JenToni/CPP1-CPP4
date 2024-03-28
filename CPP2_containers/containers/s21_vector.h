/* Copyright 2023 osgreyro
 *
 * This file contains Original Code created by Petr Velichko aka osgreyro.
 *
 * The Original Code and all software developed in the process of participation
 * on learning by experimental programming educational method. The whole
 * methodology was developed and distributed by autonomous non-profit
 * organization «School 21» (ANO «School 21»).
 *
 * Redistribution and use of this file, its parts, or entire project are
 * permitted by confirmation of its original creator.
 */

/* ========================================================================== */

#ifndef CONTAINERS_SRC_S21_VECTOR_H_
#define CONTAINERS_SRC_S21_VECTOR_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <class T>
class vector {
 public:
  /* ----- TASK TYPES ----- */
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
  vector();
  vector(std::initializer_list<value_type> const& items);
  vector(size_type n);
  vector(const vector& other);
  vector& operator=(vector& other);
  vector(vector&& other) noexcept;
  vector& operator=(vector&& other) noexcept;
  ~vector();

  /* ----- ACCESSORS AND MUTATORS ----- */
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  size_type capacity() const noexcept;
  void reserve(size_type size);
  void shrink_to_fit();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);
  void clear() noexcept;
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  T* data() noexcept;
  const T* data() const noexcept;

  /* ----- ITERATORS ----- */
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  /* ----- BONUS METHODS ----- */
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  /* ----- VARIABLES ----- */
  size_t size_;
  size_t capacity_;
  T* arr_;
};
}  // namespace s21

/* ----- FUNCTIONS ----- */
template <class T>
s21::vector<T>::vector() : size_(0), capacity_(0), arr_(nullptr) {}

template <class T>
s21::vector<T>::vector(std::initializer_list<value_type> const& items) {
  size_t siz = items.size();
  size_ = siz;
  capacity_ = siz;
  arr_ = new T[capacity_];
  for (size_t i = 0; i < siz; i++) arr_[i] = *(items.begin() + i);
}

template <class T>
s21::vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  arr_ = new T[n];
}

template <class T>
s21::vector<T>::vector(const vector& other)  //
    : size_(other.size_), capacity_(other.capacity_) {
  arr_ = new T[size_];
  for (size_t i = 0; i < size(); i++) arr_[i] = other.arr_[i];
}

template <class T>
s21::vector<T>& s21::vector<T>::operator=(vector& other) {
  vector copy(other);
  *this = std::move(copy);
  return *this;
}

template <class T>
s21::vector<T>::vector(vector&& other) noexcept {
  swap(other);
  other.arr_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <class T>
s21::vector<T>& s21::vector<T>::operator=(vector&& other) noexcept {
  swap(other);
  return *this;
}

template <class T>
s21::vector<T>::~vector() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
bool s21::vector<T>::empty() const noexcept {
  return (size_ == 0);
}

template <class T>
size_t s21::vector<T>::size() const noexcept {
  return size_;
}

template <class T>
size_t s21::vector<T>::max_size() const noexcept {
  // return -1 / sizeof(T);
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <class T>
size_t s21::vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
void s21::vector<T>::reserve(size_type size) {
  if (size > max_size()) throw std::length_error("length error");
  if (size > capacity_) {
    value_type* buff = new value_type[size];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size;
  }
}

template <class T>
void s21::vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    value_type* buff = new value_type[size_];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size_;
  }
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    iterator pos, const_reference value) {
  size_type ind = pos - begin();
  if (ind > size_)
    throw std::invalid_argument("Requested position is out of vector range");
  if (size_ == capacity_) reserve(size_ ? size_ * 2 : 1);
  std::copy(begin() + ind, end(), begin() + ind + 1);
  *(arr_ + ind) = std::move(value);
  size_++;
  return begin() + ind;
}

// template <class T>
// typename s21::vector<T>::iterator s21::vector<T>::insert(
//     iterator pos, const_reference value) {
//   size_t dist = pos - begin();
//   if (size_ >= capacity_) {
//     if (size_ == 0) {
//       capacity_ = 1;
//     } else {
//       reserve(size_ * 2);
//     }
//   }
//   value_type* buff = new T[capacity_];
//   size_++;
//   size_t shift = 0;
//   for (size_t i = 0; i < size_; i++) {
//     if (!arr_ || arr_[i] == *pos) {
//       shift = 1;
//       buff[i] = value;
//     } else {
//       buff[i] = arr_[i - shift];
//     }
//   }
//   delete[] arr_;
//   arr_ = buff;
//   iterator iter = &arr_[dist];
//   return iter;
// }

template <class T>
void s21::vector<T>::erase(iterator pos) {
  size_type ind = pos - begin();
  if (ind > size_)
    throw std::invalid_argument("Requested position is out of vector range");
  std::copy(begin() + ind + 1, end(), begin() + ind);
  size_--;
}
// void s21::vector<T>::erase(iterator pos) {
//   const size_t dist = pos - begin();
//   if (size_ != 0) size_--;
//   value_type* buff = new T[capacity_];
//   for (size_t i = 0, j = 0; i <= size_; j++)
//     if (j != dist) buff[i++] = arr_[j];
//   delete[] arr_;
//   arr_ = buff;
// }

template <class T>
void s21::vector<T>::push_back(const_reference value) {
  if (capacity_ > size_) {
    arr_[size_++] = value;
  } else {
    if (size_ == 0) {
      capacity_ = 1;
    } else {
      reserve(size_ * 2);
    }
    value_type* buff = new T[capacity_];
    for (size_t i = 0; i < size_ + 1; i++) {
      if (i == size_) {
        buff[i] = value;
      } else {
        buff[i] = arr_[i];
      }
    }
    delete[] arr_;
    arr_ = buff;
    size_++;
  }
}

template <class T>
void s21::vector<T>::pop_back() {
  arr_[size_ - 1].~T();
  size_--;
}

template <class T>
void s21::vector<T>::swap(vector& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(arr_, other.arr_);
}

template <class T>
void s21::vector<T>::clear() noexcept {
  while (end() != begin()) {
    pop_back();
    size_--;
  }
}

template <class T>
T& s21::vector<T>::at(size_type pos) {
  if (pos > size_) throw std::out_of_range("out of range");
  return arr_[pos];
}

template <class T>
const T& s21::vector<T>::at(size_type pos) const {
  if (pos > size_) throw std::out_of_range("out of range");
  return arr_[pos];
}

template <class T>
T& s21::vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <class T>
const T& s21::vector<T>::operator[](size_type pos) const {
  return arr_[pos];
}

template <class T>
T& s21::vector<T>::front() {
  return arr_[0];
}

template <class T>
const T& s21::vector<T>::front() const {
  return arr_[0];
}

template <class T>
T& s21::vector<T>::back() {
  return arr_[size_ - 1];
}

template <class T>
const T& s21::vector<T>::back() const {
  return arr_[size_ - 1];
}

template <class T>
T* s21::vector<T>::data() noexcept {
  return arr_;
}

template <class T>
const T* s21::vector<T>::data() const noexcept {
  return arr_;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::begin() noexcept {
  return arr_;
}

template <class T>
typename s21::vector<T>::const_iterator s21::vector<T>::begin() const noexcept {
  return arr_;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::end() noexcept {
  return arr_ + size_;
}

template <class T>
typename s21::vector<T>::const_iterator s21::vector<T>::end() const noexcept {
  return arr_ + size_;
}

template <class T>
template <typename... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator ret = nullptr;
  auto dist = pos - begin();
  if (size_ + sizeof...(args) >= capacity_) {
    reserve(2 * (size_ + sizeof...(args)));
  }
  for (auto&& arg : {args...}) {
    ret = insert(begin() + dist, arg);
    dist++;
  }
  return ret;
}

template <class T>
template <typename... Args>
void s21::vector<T>::insert_many_back(Args&&... args) {
  if (size_ + sizeof...(args) >= capacity_) {
    reserve(2 * (size_ + sizeof...(args)));
  }
  for (auto&& arg : {args...}) {
    push_back(arg);
  }
}

// template <class T>
// template <typename... Args>
// typename s21::vector<T>::iterator s21::vector<T>::insert_many(
//     const_iterator pos, Args&&... args) {
//   size_t dist = pos - begin();
//   size_t size_buff = sizeof...(args);
//   value_type res[size_buff] = {args...};
//   if (size_buff + size_ >= capacity_) capacity_ = (size_ + size_buff) * 2;
//   value_type* buff = new T[capacity_];
//   size_ += size_buff;
//   size_t shift = 0;
//   for (size_t i = 0; i < size_; i++) {
//     if (!arr_ || arr_[i] == *pos || (shift > 0 && shift < size_buff)) {
//       buff[i] = res[shift];
//       shift++;
//     } else {
//       buff[i] = arr_[i - shift];
//     }
//   }
//   delete[] arr_;
//   arr_ = buff;
//   iterator iter = &arr_[dist];
//   return iter;
// }

// template <class T>
// template <typename... Args>
// void s21::vector<T>::insert_many_back(Args&&... args) {
//   size_t size_buff = sizeof...(args);
//   value_type res[size_buff] = {args...};
//   if (size_buff + size_ >= capacity_) capacity_ = (size_ + size_buff) * 2;
//   value_type* buff = new T[capacity_];
//   size_ += size_buff;
//   size_t shift = 0;
//   for (size_t i = 0; i < size_; i++) {
//     if (i >= size_ - size_buff) {
//       buff[i] = res[shift];
//       shift++;
//     } else {
//       buff[i] = arr_[i];
//     }
//   }
//   delete[] arr_;
//   arr_ = buff;
// }

#endif  // CONTAINERS_SRC_S21_VECTOR_H_