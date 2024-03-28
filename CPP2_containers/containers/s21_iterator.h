#ifndef CONTAINERS_SRC_CONTAINERS_S21_ITERATOR_H_
#define CONTAINERS_SRC_CONTAINERS_S21_ITERATOR_H_

/* ----- NAMESPACES AND CLASSES ----- */
namespace s21 {
template <typename T, typename Container>
class ra_iterator {
 public:
  /* ----- CONSTANTS ----- */
  constexpr ra_iterator() noexcept : ptr_(nullptr){};
  explicit ra_iterator(T* data) noexcept : ptr_(data){};

  /* ----- TYPES ----- */
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = int32_t;
  using pointer = T*;
  using reference = T&;

  /* ----- OPERATOR OVERLOADS ----- */
  T* base() const noexcept { return ptr_; }
  T& operator*() const noexcept { return *ptr_; }
  T* operator->() const noexcept { return ptr_; }
  bool operator==(const ra_iterator& other) const noexcept {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const ra_iterator& other) const noexcept {
    return ptr_ != other.ptr_;
  }
  bool operator>(const ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) > 0;
  }
  bool operator<(const ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) < 0;
  }
  bool operator>=(const ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) >= 0;
  }
  bool operator<=(const ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) <= 0;
  }
  ra_iterator operator+(difference_type delta) const noexcept {
    return ra_iterator(ptr_ + delta);
  }
  ra_iterator operator-(difference_type delta) const noexcept {
    return ra_iterator(ptr_ - delta);
  }
  difference_type operator-(const ra_iterator& other) const noexcept {
    return ptr_ - other.ptr_;
  }
  ra_iterator operator++(int) noexcept { return ra_iterator(ptr_++); }
  ra_iterator operator--(int) noexcept { return ra_iterator(ptr_--); }
  ra_iterator& operator++() noexcept {
    ++ptr_;
    return *this;
  }
  ra_iterator& operator--() noexcept {
    --ptr_;
    return *this;
  }
  operator ra_iterator<const T, Container>() const noexcept {
    return ra_iterator<const T, Container>(const_cast<const T*>(ptr_));
  }

 protected:
  /* ----- VARIABLES ----- */
  T* ptr_;
};

template <typename T, typename Container>
class reverse_ra_iterator {
 public:
  /* ----- CONSTANTS ----- */
  constexpr reverse_ra_iterator() noexcept : ptr_(nullptr){};
  explicit reverse_ra_iterator(T* data) noexcept : ptr_(data){};

  /* ----- TYPES ----- */
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = int32_t;
  using pointer = T*;
  using reference = T&;

  /* ----- OPERATOR OVERLOADS ----- */
  T* base() const noexcept { return ptr_; }
  T& operator*() const noexcept { return *ptr_; }
  T* operator->() const noexcept { return *ptr_; }
  bool operator==(const reverse_ra_iterator& other) const noexcept {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const reverse_ra_iterator& other) const noexcept {
    return ptr_ != other.ptr_;
  }
  bool operator>(const reverse_ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) < 0;
  }
  bool operator<(const reverse_ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) > 0;
  }
  bool operator>=(const reverse_ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) <= 0;
  }
  bool operator<=(const reverse_ra_iterator& other) const noexcept {
    return (ptr_ - other.ptr_) >= 0;
  }
  reverse_ra_iterator operator+(difference_type delta) const noexcept {
    return reverse_ra_iterator(ptr_ - delta);
  }
  reverse_ra_iterator operator-(difference_type delta) const noexcept {
    return reverse_ra_iterator(ptr_ + delta);
  }
  difference_type operator-(const reverse_ra_iterator& other) const noexcept {
    return other.ptr_ - ptr_;
  }
  reverse_ra_iterator operator++(int) noexcept {
    return reverse_ra_iterator(ptr_--);
  }
  reverse_ra_iterator operator--(int) noexcept {
    return reverse_ra_iterator(ptr_++);
  }
  reverse_ra_iterator& operator++() noexcept {
    --ptr_;
    return *this;
  }
  reverse_ra_iterator& operator--() noexcept {
    ++ptr_;
    return *this;
  }
  operator reverse_ra_iterator<const T, Container>() const noexcept {
    return reverse_ra_iterator<const T, Container>(const_cast<const T*>(ptr_));
  }

 protected:
  /* ----- VARIABLES ----- */
  T* ptr_;
};
}  // namespace s21

#endif  // CONTAINERS_SRC_CONTAINERS_S21_ITERATOR_H_
