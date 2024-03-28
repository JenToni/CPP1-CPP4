/* Copyright 2023 sigridva
 *
 * This file contains Original Code created by Ilya Perederin aka sigridva.
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

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "s21_binarytree.h"
// #include "s21_vector.h"

namespace s21 {
template <class Key, class Value>
class map {
  typedef Key key_type;
  typedef Value mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef std::pair<const key_type*, mapped_type*> reference;              // &
  typedef const std::pair<const key_type*, mapped_type*> const_reference;  // &
  typedef std::size_t size_type;

 private:
  int count = 0;

 public:
  BinaryTree<Key, Value>* GetTree() { return tr; };

  class MapIterator {
    friend class BinaryTree<Key, Value>;

   public:
    MapIterator(){};
    MapIterator(const value_type& value, BinaryTree<Key, Value>* tree);

    MapIterator(MapIterator& other);
    MapIterator(MapIterator&& other);
    MapIterator operator=(MapIterator&& other);
    MapIterator operator=(MapIterator& other);
    bool operator!=(MapIterator& other);
    bool operator!=(MapIterator&& other);
    value_type operator*();
    MapIterator operator++() {
      if ((tr->MoveIterator(tr->GetNodeViaKey(*first))) == tr->GetNIL()) {
        second = nullptr;
        first = nullptr;
      } else {
        second = &((tr->MoveIterator(tr->GetNodeViaKey(*first)))->val);
        first = &((tr->MoveIterator(tr->GetNodeViaKey(*first)))->key);
      }
      return *this;
    };
    MapIterator operator--();

    BinaryTree<Key, Value>* GetTree() { return tr; };
    BinaryTree<Key, Value> SetTree(BinaryTree<Key, Value>* other) {
      tr = other;
    };

    Key* first = nullptr;
    Value* second = nullptr;

    ~MapIterator();
    BinaryTree<Key, Value>* tr;
  };

  class MapConstIterator : MapIterator {
   public:
    MapConstIterator() : MapIterator(){};
    MapConstIterator(MapIterator it);
    MapConstIterator(const value_type& value, BinaryTree<Key, Value>* tree)
        : MapIterator(value, tree){};
    MapConstIterator(MapConstIterator& other) : MapIterator(other){};
    MapConstIterator(MapConstIterator&& other) : MapIterator(other){};
    MapConstIterator operator=(MapConstIterator&& other);
    MapConstIterator operator=(MapConstIterator& other);
    bool operator!=(MapConstIterator& other);
    bool operator!=(MapConstIterator&& other);
    const value_type operator*();
    MapConstIterator operator++();
    MapConstIterator operator--();

    const Key* first;
    const Value* second;

    ~MapConstIterator();

    BinaryTree<Key, Value>* tr;
  };

  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  map operator=(map&& m);
  map operator=(map& m);
  ~map();

  bool empty();

  typedef MapIterator iterator;

  iterator begin() const;
  iterator end() const;

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const Value& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const Value& obj);

  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  void clear();

  bool contains(const Key& key);

  Value& at(const Key& key);
  Value& operator[](const Key& key);

  size_type size();
  size_type max_size();

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 protected:
  BinaryTree<Key, Value>* tr = nullptr;
};

// @brief default constructor, creates empty map
template <class Key, class Value>
map<Key, Value>::map() {
  count = 0;
  tr = new BinaryTree<Key, Value>();
};

// @brief initializer list constructor, creates the map initizialized using
// std::initializer_list
template <class Key, class Value>
map<Key, Value>::map(std::initializer_list<value_type> const& items) {
  //   if (tr != nullptr) {
  //     delete tr;
  //   }
  tr = new BinaryTree<Key, Value>();
  count = 0;

  for (auto element : items) {
    insert(element);
  }
}

// @brief copy constructor
template <class Key, class Value>
map<Key, Value>::map(const map& m) {
  //   if (tr != nullptr) {
  //     delete tr;
  //   }
  tr = new BinaryTree<Key, Value>();

  map<Key, Value>::MapIterator endIt = m.end();

  for (map<Key, Value>::MapIterator it = m.begin(); it != endIt; ++it) {
    tr->Insert(tr->CreateNode(*(it.first), *(it.second)));
  }
}

// @brief move constructor
template <class Key, class Value>
map<Key, Value>::map(map&& m) {
  if (tr != m.tr) {
    // if (tr != nullptr) {
    delete tr;
    // }
    tr = m.tr;
    count = m.count;
    m.tr = nullptr;
    m.count = 0;
  }
}

// @brief destructor
template <class Key, class Value>
map<Key, Value>::~map() {
  if (tr != nullptr) {
    delete tr;
  }
};

// @brief assignment operator overload for moving object
template <class Key, class Value>
map<Key, Value> map<Key, Value>::operator=(map&& m) {
  if (tr != m.tr) {
    // if (tr != nullptr) {
    delete tr;
    // }
    tr = m.tr;
    count = m.count;
    m.tr = nullptr;
    m.count = 0;
  }
  return *this;
}

// @brief assignment operator overload for copying object
template <class Key, class Value>
map<Key, Value> map<Key, Value>::operator=(map& m) {
  //   if (tr != nullptr) {
  //     delete tr;
  //   }
  tr = new BinaryTree<Key, Value>();

  map<Key, Value>::MapIterator endIt = m.end();

  for (map<Key, Value>::MapIterator it = m.begin(); it != endIt; ++it) {
    tr->Insert(tr->CreateNode(*(it.first), *(it.second)));
  }
  return *this;
}

//@brief access specified element with bounds checking
template <class Key, class Value>
Value& map<Key, Value>::at(const Key& key) {
  return tr->GetValue(key);
}

//@brief access or insert specified element
template <class Key, class Value>
Value& map<Key, Value>::operator[](const Key& key) {
  return tr->GetValue(key);
}

// @brief returns an iterator to the beginning
template <class Key, class Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() const {
  map<Key, Value>::iterator it;
  it.first = &((tr->RecursiveMinimum())->key);
  it.second = &((tr->RecursiveMinimum())->val);
  it.tr = tr;
  return it;
}

// @brief returns an iterator to the end
template <class Key, class Value>
typename map<Key, Value>::iterator map<Key, Value>::end() const {
  map<Key, Value>::iterator it;
  it.first = nullptr;
  it.second = nullptr;
  it.tr = tr;

  return it;
}

//@brief checks whether the container is empty
template <class Key, class Value>
bool map<Key, Value>::empty() {
  return (count == 0);
}

//@brief returns the number of elements
template <class Key, class Value>
typename map<Key, Value>::size_type map<Key, Value>::size() {
  return ((size_type)count);
};

//@brief returns the number of elements
template <class Key, class Value>
typename map<Key, Value>::size_type map<Key, Value>::max_size() {
  return (size_type)(std::numeric_limits<size_type>::max() /
                     sizeof(tr->NodeSize()));
}

//@brief clears the contents
template <class Key, class Value>
void map<Key, Value>::clear() {
  delete tr;  // calls destructor, all memory freed
  tr = nullptr;
  count = 0;
}

// @brief inserts node and returns iterator to where the element is in the
// container and bool denoting whether the insertion took place
template <class Key, class Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const value_type& value) {
  bool insert_status;
  insert_status =
      tr->Insert(tr->CreateNode(std::get<0>(value), std::get<1>(value)));

  MapIterator it;
  if (insert_status) {
    it = MapIterator(value, tr);
    count++;
  }
  return std::pair<iterator, bool>(it, insert_status);
}

//@brief inserts value by key and returns iterator to where the element is in
// the container and bool denoting whether the insertion took place
template <class Key, class Value>
std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(
    const Key& key, const Value& obj) {
  bool insert_status;
  insert_status = tr->InsertValueViaKey(key, obj, 0);

  MapIterator it;
  if (insert_status) {
    it = MapIterator(std::pair<Key, Value>(key, obj), tr);
  }
  return std::pair<iterator, bool>(it, insert_status);
}

//@brief inserts an element or assigns to the current element if the key already
// exists
template <class Key, class Value>
std::pair<typename map<Key, Value>::iterator, bool>
map<Key, Value>::insert_or_assign(const Key& key, const Value& obj) {
  bool insert_status;
  MapIterator it;
  insert_status = tr->InsertValueViaKey(key, obj, 1);

  if (insert_status) {
    it = MapIterator(std::pair<Key, Value>(key, obj), tr);
    count++;
  }

  return std::pair<iterator, bool>(it, insert_status);
}

// @brief erases element at pos
template <class Key, class Value>
void map<Key, Value>::erase(iterator pos) {
  if (pos.first == nullptr) {
    return;
  }
  tr->DeleteNode(*(pos.first));
  count--;
}

//@brief swaps the contents
template <class Key, class Value>
void map<Key, Value>::swap(map<Key, Value>& other) {
  map<Key, Value> copy(*this);
  (*this) = std::move(other);
  other = std::move(copy);
}

//@brief splices nodes from another container
template <class Key, class Value>
void map<Key, Value>::merge(map& other) {
  tr->merge(other.tr);
}

//@brief checks if there is an element with key equivalent to key in the
// container
template <class Key, class Value>
bool map<Key, Value>::contains(const Key& key) {
  bool res(true);

  try {
    tr->GetValue(key);
  } catch (std::out_of_range const& err) {
    res = false;
  }

  return res;
};

// @brief Bonus Psrt
// inserts new elements into the container
template <class Key, class Value>
template <typename... Args>
typename std::vector<std::pair<typename map<Key, Value>::iterator, bool>>
map<Key, Value>::insert_many(Args&&... args) {
  std::vector<std::pair<typename map<Key, Value>::iterator, bool>> res;

  for (auto&& arg : {std::forward<Args>(args)...}) {
    res.push_back(insert(std::forward<decltype(arg)>(arg)));
  }
  return res;
}

template <class Key, class Value>
typename map<Key, Value>::value_type map<Key, Value>::iterator::operator*() {
  return std::pair<Key, Value>(*first, *second);
}

template <class Key, class Value>
inline map<Key, Value>::MapIterator::MapIterator(const value_type& value,
                                                 BinaryTree<Key, Value>* tree) {
  tr = tree;
  first = &((tr->GetNodeViaKey(std::get<0>(value)))->key);
  second = &((tr->GetNodeViaKey(std::get<0>(value)))->val);
}

template <class Key, class Value>
map<Key, Value>::MapIterator::MapIterator(MapIterator& other)
    : first(other.first), second(other.second) {}

template <class Key, class Value>
map<Key, Value>::MapIterator::MapIterator(MapIterator&& other)
    : first(other.first), second(other.second) {
  other.first = nullptr;
  other.second = nullptr;
}

template <class Key, class Value>
bool map<Key, Value>::MapIterator::operator!=(MapIterator& other) {
  return (first != other.first);
}

template <class Key, class Value>
inline bool map<Key, Value>::MapIterator::operator!=(MapIterator&& other) {
  return (first != other.first);
}

template <class Key, class Value>
typename map<Key, Value>::MapIterator
map<Key, Value>::MapIterator::operator--() {
  if (second == nullptr) {
    second = &(tr->RecursiveMaximum()->val);
    first = &(tr->RecursiveMaximum()->key);
  } else {
    second = &((tr->MoveBackwardIterator(tr->GetNodeViaKey(*first)))->val);
    first = &((tr->MoveBackwardIterator(tr->GetNodeViaKey(*first)))->key);
  }
  return *this;
}

template <class Key, class Value>
typename map<Key, Value>::iterator map<Key, Value>::iterator::operator=(
    map<Key, Value>::iterator&& other) {
  if (this != &other) {
    first = other.first;
    second = other.second;
    other.first = nullptr;
    other.second = nullptr;
  }

  return *this;
}

template <class Key, class Value>
map<Key, Value>::MapIterator::~MapIterator() {
  first = nullptr;
  second = nullptr;
}

template <class Key, class Value>
inline map<Key, Value>::MapConstIterator::MapConstIterator(MapIterator it) {
  first = it.first;
  second = it.second;
  tr = it.tr;
}

template <class Key, class Value>
const typename map<Key, Value>::value_type
map<Key, Value>::MapConstIterator::operator*() {
  return std::pair<Key, Value>(*first, *second);
};

template <class Key, class Value>
typename map<Key, Value>::MapConstIterator
map<Key, Value>::MapConstIterator::operator=(MapConstIterator&& other) {
  first = other.first;
  second = other.second;
  tr = other.tr;
  other.first = nullptr;
  other.second = nullptr;
  other.tr = nullptr;
}

template <class Key, class Value>
typename map<Key, Value>::MapConstIterator
map<Key, Value>::MapConstIterator::operator=(MapConstIterator& other) {
  first = other.first;
  second = other.second;
  tr = other.tr;
}

template <class Key, class Value>
bool map<Key, Value>::MapConstIterator::operator!=(MapConstIterator&& other) {
  return first != other.first;
}

template <class Key, class Value>
typename map<Key, Value>::MapConstIterator
map<Key, Value>::MapConstIterator::operator++() {
  if ((tr->MoveIterator(tr->GetNodeViaKey(*first))) == tr->GetNIL()) {
    second = nullptr;
    first = nullptr;
  } else {
    second = &((tr->MoveIterator(tr->GetNodeViaKey(*first)))->val);
    first = &((tr->MoveIterator(tr->GetNodeViaKey(*first)))->key);
  }
  return *this;
}

template <class Key, class Value>
typename map<Key, Value>::MapConstIterator
map<Key, Value>::MapConstIterator::operator--() {
  if (second == nullptr) {
    second = &((tr->MoveBackwardIterator(tr->RecursiveMaximum()))->val);
    first = &((tr->MoveBackwardIterator(tr->RecursiveMaximum()))->key);
  } else {
    second = &((tr->MoveBackwardIterator(tr->GetNodeViaKey(*first)))->val);
    first = &((tr->MoveBackwardIterator(tr->GetNodeViaKey(*first)))->key);
  }
  return *this;
}

template <class Key, class Value>
bool map<Key, Value>::MapConstIterator::operator!=(MapConstIterator& other) {
  return (first != other.first);
}

template <class Key, class Value>
inline map<Key, Value>::MapConstIterator::~MapConstIterator() {}

};  // namespace s21

#endif
