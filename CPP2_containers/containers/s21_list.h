#ifndef CPP2_S21_CONTAINERS_LIST_H_
#define CPP2_S21_CONTAINERS_LIST_H_

#include <initializer_list>
#include <limits>  // для max_xize()
#include <stdexcept>

namespace s21 {
template <typename T>
class list {
 public:
  // List Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  // List Functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l) noexcept;
  ~list();
  list& operator=(list&& l) noexcept;

 private:
  class Node {
   public:
    value_type value_;
    Node* prev_;
    Node* next_;
    Node(const value_type& value)
        : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  Node* _big_head_;
  size_type size_;

 public:
  // List Element access
  const_reference front();
  const_reference back();

  // List Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // List Modifiers
  void clear();
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void reverse();
  void unique();
  void sort();

  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { ptr_ = nullptr; }
    ListIterator(Node* ptr) : ptr_(ptr){};

    reference operator*() { return this->ptr_->value_; }

    ListIterator& operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }
    ListIterator& operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

   private:
    Node* ptr_;
    friend class list<T>;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const reference operator*() { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, list& other);

  // List Iterators
  iterator begin();
  iterator end();

  // Реализация методов insert_many

  /// @tparam template <typename... Args>  Variadic Templates (шаблоны
  /// переменной арности). Он означет, что 'Args' - это параметры переменной
  /// длины
  /// @tparam ...Args Шаблон с переменных количествомаргументо, когда ... слева
  /// от имени параматра он означает пакет параметров
  /// @param pos позиция перед которой нужно вставить
  /// @param ... оператор распаковки позволяет распаковывать параметры
  /// переменной длины внутри шиблонных функций и классов
  /// @param ...args Хранит в себе аргументы
  /// @return iterator на последний вставленный элемент
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

  // Own functions
 private:
  void set_big_head_();
  void quick_sort(iterator first, iterator last);
  iterator partition(iterator l, iterator h);
  void copy(const list& l);
};

// Базовый конструктор класса list
// set_big_head_ служебная нода, которая соединяет head_ и tail_
template <typename value_type>
list<value_type>::list()
    : head_(nullptr), tail_(nullptr), _big_head_(nullptr), size_(0) {
  _big_head_ = new Node(size_);
  set_big_head_();
}

template <typename value_type>
list<value_type>::list(size_type n)
    : head_(nullptr), tail_(nullptr), _big_head_(nullptr), size_(0) {
  // if (n >= max_size()) {
  //   throw std::out_of_range("Limit of the container is exceeded");
  // }
  _big_head_ = new Node(size_);
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
  set_big_head_();
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), _big_head_(nullptr), size_(0) {
  _big_head_ = new Node(size_);
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename value_type>
list<value_type>::list(const list& l)
    : head_(nullptr), tail_(nullptr), _big_head_(nullptr), size_(0) {
  _big_head_ = new Node(size_);
  copy(l);
}

template <typename value_type>
list<value_type>::list(list&& l) noexcept
    : head_(nullptr), tail_(nullptr), _big_head_(nullptr), size_(0) {
  swap(l);
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  delete _big_head_;
}

template <typename value_type>
typename list<value_type>::list& list<value_type>::operator=(
    list&& l) noexcept {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

// List Element access
// Доступ к первому элементу контейнера.
template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return *begin();
}

// Доступ к последнему элементу контейнера.
template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  return *(--end());
}

// List Capacity
// проверка, пуст ли контейнер
template <typename value_type>
bool list<value_type>::empty() {
  return (size_ == 0);
}
// Возвращает количество элементов
template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return size_;
}
// Возвращает максимально возможное количество элементов
template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(list));
}

// List Modifiers
template <typename value_type>
void list<value_type>::clear() {
  while (!empty()) pop_back();
}

// Добавляет элемент в конец списка
template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  size_++;
  set_big_head_();
}

// Добавляет элемент в начало списка
template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
  }
  size_++;
  set_big_head_();
}

// Удаляет элемент с конца списка
template <typename value_type>
void list<value_type>::pop_back() {
  Node* last_node = tail_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    tail_ = last_node->prev_;
    tail_->next_ = nullptr;
  }
  delete last_node;

  size_--;
  set_big_head_();
}

// Удаляет элемент с начала списка
template <typename value_type>
void list<value_type>::pop_front() {
  Node* first_node = head_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    head_ = first_node->next_;
    head_->prev_ = nullptr;
  }
  delete first_node;
  size_--;
  set_big_head_();
}

// Меняет местами контейнеры
template <typename value_type>
void list<value_type>::swap(list& other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
  std::swap(this->_big_head_, other._big_head_);
}

// Удаляет последовательные повторяющиеся элементы
template <typename value_type>
void list<value_type>::unique() {
  if (!empty() && size_ > 1) {
    iterator begin = this->begin();
    iterator end = this->end();
    iterator next_begin = begin;
    ++next_begin;
    while (begin != end) {
      if (*begin == *next_begin) {
        erase(begin);
        begin = next_begin;
      } else
        ++next_begin;
      ++begin;
    }
  }
}

// Изменяет порядок расположения элементов на противоположный
template <typename value_type>
void list<value_type>::reverse() {
  if (!empty() && size_ > 1) {
    iterator begin = this->begin();
    iterator end = this->end();
    --end;
    while (begin != end && begin.ptr_->prev_ != end.ptr_) {
      std::swap(*begin, *end);
      ++begin;
      --end;
    }
  }
}

// Объединяет два отсортированных списка
// Списки должны быть самостоятельно отсортированны до мерджа
template <typename value_type>
void list<value_type>::merge(list& other) {
  if (!this->empty() && !other.empty()) {
    iterator it_main = this->begin();
    iterator it_other = other.begin();
    while (it_main != this->end()) {
      if (it_other != other.end()) {
        if (it_main.ptr_->value_ >= it_other.ptr_->value_) {
          this->insert(it_main, it_other.ptr_->value_);
          ++it_other;
        } else
          ++it_main;
      } else
        break;
    }
    while (it_other != other.end()) {
      this->insert(it_main, it_other.ptr_->value_);
      ++it_other;
    }

  } else if (this->empty() && !other.empty()) {
    this->copy(other);
  }
  other.clear();
}

// Сортирует список по возрастанию
template <typename value_type>
void list<value_type>::sort() {
  if (size_ > 1) {
    quick_sort(begin(), --end());
  }
}

// Вставляет элементы в конкретный pos и возвращает итератор, который
// указывает на новый элемент
template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node* add_node = new Node(value);
  if (empty()) {
    add_node->next_ = _big_head_;
    add_node->prev_ = _big_head_;
    head_ = add_node;
    tail_ = add_node;
  } else {
    Node* insert_pos = pos.ptr_;
    if (insert_pos == head_) {
      head_ = add_node;
    } else if (insert_pos == _big_head_) {
      tail_ = add_node;
    }
    add_node->next_ = insert_pos;
    add_node->prev_ = insert_pos->prev_;
    insert_pos->prev_->next_ = add_node;
    insert_pos->prev_ = add_node;
  }
  size_++;
  set_big_head_();
  return iterator(add_node);
}

// Стирает элемент в позиции
template <typename value_type>
void list<value_type>::erase(iterator pos) {
  Node* del_pos = pos.ptr_;
  if (!empty() && del_pos != _big_head_) {
    if (del_pos == head_) {
      pop_front();
    } else if (del_pos == tail_) {
      pop_back();
    } else {
      del_pos->prev_->next_ = del_pos->next_;
      del_pos->next_->prev_ = del_pos->prev_;
      delete del_pos;
      size_--;
      set_big_head_();
    }
  }
}

// Переносит элементы из списка other, начиная с pos
template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
    other.clear();
  }
}

// List Iterators
template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return head_;
}
template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return _big_head_;
}

// Реализация методов insert_many

/// @tparam Args&&...args параметры переменной длины
/// @tparam Args это пакет аргументов переменной длины, а Args&& это
/// универсальные ссылки позволяющие принимать lvalue и rvalue
/// @tparam args хранит в себе аргументы
/// @param std::forward<Args>(args)... Это оператор распаковки который
/// распаковывает параметры переменной длины args, сохраняя категорию(lvalue или
/// rvalue) и передает по одному в метод insert
/// @param std::forward<decltype(arg)>(arg) передаёт arg с тем же типом
/// @attention Можно конструкцию auto&& arg : {std::forward<Args>(args)...}
/// заменить на более простую auto& arg : {args...} (и будет просто
/// insert(pos,arg)) в таком случае аргументы могут быть скопированы, даже если
/// они rvalue
template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  for (auto&& arg : {std::forward<Args>(args)...}) {
    insert(pos, std::forward<decltype(arg)>(arg));
  }
  return pos;
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args&&... args) {
  for (auto&& arg : {std::forward<Args>(args)...}) {
    push_back(std::forward<decltype(arg)>(arg));
  }
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args&&... args) {
  for (auto&& arg : {std::forward<Args>(args)...}) {
    push_front(std::forward<decltype(arg)>(arg));
  }
}

// Own functions
template <typename value_type>
void list<value_type>::set_big_head_() {
  if (_big_head_) {
    _big_head_->next_ = head_;
    _big_head_->prev_ = tail_;
    _big_head_->value_ = size();

    if (head_) {
      head_->prev_ = _big_head_;
    }
    if (tail_) {
      tail_->next_ = _big_head_;
    }
  }
}

/// Приватный  рекурсивный метод
/// Часть быстрой сортировки
template <typename value_type>
void list<value_type>::quick_sort(iterator first, iterator last) {
  if (first == last || first == _big_head_ || last == _big_head_ ||
      first == tail_) {
    return;
  }
  iterator privot = partition(first, last);
  quick_sort(first, --privot);
  quick_sort(++privot, last);
}

/// Приватный метод деления массива
/// Часть быстрой сортировки
template <typename value_type>
typename list<value_type>::iterator list<value_type>::partition(iterator l,
                                                                iterator h) {
  value_type pivot = h.ptr_->value_;
  iterator i = l;

  for (iterator j = l; j != h; ++j) {
    if (j.ptr_->value_ <= pivot) {
      std::swap(j.ptr_->value_, i.ptr_->value_);
      ++i;
    }
  }

  std::swap(i.ptr_->value_, h.ptr_->value_);
  return i;
}

template <typename value_type>
void list<value_type>::copy(const list& l) {
  Node* copy = l.head_;
  for (size_type i = 0; i != l.size_; i++) {
    push_back(copy->value_);
    copy = copy->next_;
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_LIST_H_
