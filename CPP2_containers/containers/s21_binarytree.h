#ifndef S21_BINARY_TREE
#define S21_BINARY_TREE

template <class Key, class Value>
class BinaryTree {
  typedef Key key_type;
  typedef Value mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef std::pair<const key_type *, mapped_type *> reference;
  typedef const std::pair<const key_type *, mapped_type *> const_reference;
  typedef size_t size_type;

 protected:
  struct Node {
    key_type key;
    mapped_type val;
    int color;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
  };

 private:
  int count;
  Node *NIL = nullptr;
  Node *root = nullptr;
  Node *CreateNIL();
  void PrintTree(Node *nd);

 public:
  class Iterator {
    friend class BinaryTree;

   public:
    Iterator();
    Iterator(Node *nd);
    Iterator(Node *nd, BinaryTree<Key, Value> *tree);
    Iterator(const Iterator &);
    Iterator(Iterator &&);

    ~Iterator() = default;
    Iterator operator=(Iterator &&other);
    bool operator!=(Iterator &other);
    bool operator!=(Iterator &&other);
    Iterator(const value_type &value);

    mapped_type operator*();
    Iterator operator++();
    Iterator operator--();

    key_type *first;
    mapped_type *second;

   protected:
    Node *current;
    BinaryTree *tr;
  };

  class ConstIterator : Iterator {
    ConstIterator();
    ConstIterator(Node *nd);
    ConstIterator(Node *nd, BinaryTree<Key, Value> *tree);
    ConstIterator(const ConstIterator &);
    ConstIterator(ConstIterator &&);
    ConstIterator operator=(ConstIterator &&other);
    bool operator!=(ConstIterator &other);
    ConstIterator(const value_type &value);
  };

  BinaryTree();
  void free();

  bool empty();
  void merge(BinaryTree *other);

  Iterator begin();
  Iterator end();
  Iterator *insert_iterator(const value_type &value);

  void RotateLeft(Node *nd);
  void RotateRight(Node *nd);

  bool Insert(Node *nd);
  bool InsertValueViaKey(key_type K, mapped_type V, int assign);

  void DeleteSubTree(Node *nd);

  void InsertCheck(Node *nd);
  Value &GetValue(const Key &key);
  Node *GetNode(const Key &key);
  Node *CreateNode(Key K, Value V);
  Node *GetNIL() { return NIL; }

  size_t NodeSize();
  Node *GetNodeViaKey(const Key &key);

  Node *MinimumTree(Node *nd);
  Node *MaximumTree(Node *nd);
  void RBDeleteFixup(Node *nd);
  void RBTransplant(Node *nd1, Node *nd2);
  void DeleteNode(Key pos);
  Node *MoveIterator(Node *nd);
  Node *MoveBackwardIterator(Node *nd);

  Node *RecursiveMinimum();
  Node *RecursiveMaximum();
  Node *GetMinimumNode(Node *nd);
  Node *GetMaximumNode(Node *nd);
  ~BinaryTree();
};

template <class Key, class Value>
BinaryTree<Key, Value>::BinaryTree() {
  NIL = CreateNIL();
  root = NIL;
  root->parent = root->left = root->right = NIL;
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::empty() {
  return (root == NIL);
}

template <class Key, class Value>
void BinaryTree<Key, Value>::merge(BinaryTree *other) {
  Iterator last = (*other).end();
  Iterator lastCopy = last;
  if ((--lastCopy).first == nullptr) {
    return;
  }
  for (Iterator start = (*other).begin(); start != last; ++start) {
    Insert(CreateNode(*(start.first), *(start.second)));
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::DeleteSubTree(Node *nd) {
  if (nd == NIL || nd == root) {
    return;
  }
  DeleteSubTree(nd->left);
  DeleteSubTree(nd->right);

  if (nd) {
    delete nd;
    count--;
    nd = nullptr;
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::free() {
  if (root != NIL) {
    DeleteSubTree(root->right);
    DeleteSubTree(root->left);
  }
}

template <class Key, class Value>
BinaryTree<Key, Value>::~BinaryTree() {
  free();
  if (root != NIL) {
    delete root;
    delete NIL;
  } else {
    delete NIL;
  }
}

template <class Key, class Value>
Value &BinaryTree<Key, Value>::GetValue(const Key &key) {
  Node *nd = root;

  if (key == nd->key) {
    return nd->val;
  }

  while (nd != NIL) {
    if (key > nd->key) {
      nd = nd->right;
    } else if (key < nd->key) {
      nd = nd->left;
    } else {
      return nd->val;
    }
  }

  throw std::out_of_range(
      "No element with this key found.");  // TODO check whether throw is needed
};

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::GetNodeViaKey(
    const Key &key) {
  Node *nd = root;

  if (key == nd->key) {
    return nd;
  }

  while (nd != NIL) {
    if (key > nd->key) {
      nd = nd->right;
    } else if (key < nd->key) {
      nd = nd->left;
    } else {
      return nd;
    }
  }

  return NIL;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *
BinaryTree<Key, Value>::MoveBackwardIterator(Node *nd) {
  if (nd->left != NIL) {
    return MaximumTree(nd->left);
  }

  Node *parent = nd->parent;
  while (parent != NIL && nd == parent->left) {
    nd = parent;
    parent = parent->parent;
  }

  return parent;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::RBDeleteFixup(Node *nd) {
  Node *temp;

  while (nd != root && nd->color == 1) {
    if (nd == nd->parent->left) {
      temp = nd->parent->right;
      if (temp->color == 0) {
        temp->color = 1;
        nd->parent->color = 0;
        RotateLeft(nd->parent);
        temp = nd->parent->right;
      }
      if (temp->left->color == 1 && temp->right->color == 1) {
        temp->color = 0;
        nd = nd->parent;
      } else if (temp->right->color == 1) {
        temp->left->color = 1;  // n?
        temp->color = 0;
        RotateRight(temp);
        temp = nd->parent->right;
      }
      temp->color = nd->parent->color;
      nd->parent->color = 1;
      temp->right->color = 1;
      RotateLeft(nd->parent);
      nd = root;
    } else {
      temp = nd->parent->left;
      if (temp->color == 0) {
        temp->color = 1;
        nd->parent->color = 0;
        RotateRight(nd->parent);
        temp = nd->parent->left;
      }
      if (temp->right->color == 1 && temp->left->color == 1) {
        temp->color = 0;
        nd = nd->parent;
      } else if (temp->left->color == 1) {
        temp->right->color = 1;  // n?
        temp->color = 0;
        RotateLeft(temp);
        temp = nd->parent->left;
      }
      temp->color = nd->parent->color;
      nd->parent->color = 1;
      temp->left->color = 1;
      RotateRight(nd->parent);
      nd = root;
    }
  }

  nd->color = 1;
}

template <class Key, class Value>
size_t BinaryTree<Key, Value>::NodeSize() {
  return sizeof(Node);
}

template <class Key, class Value>
void BinaryTree<Key, Value>::RBTransplant(Node *nd1, Node *nd2) {
  if (nd1->parent == NIL) {
    root = nd1;
  } else if (nd1 == nd1->parent->left) {
    nd1->parent->left = nd2;
  } else {
    nd1->parent->right = nd2;
  }
  nd2->parent = nd1->parent;
};

template <class Key, class Value>
void BinaryTree<Key, Value>::RotateLeft(Node *nd) {
  if (nd->right != NIL) {
    Node *pivot = nd->right;
    nd->right = pivot->left;

    if (pivot->left != NIL) {
      pivot->left->parent = nd;
    }
    pivot->parent = nd->parent;
    if (nd->parent == NIL) {
      root = pivot;
    } else if (nd == nd->parent->left) {
      nd->parent->left = pivot;

    } else {
      nd->parent->right = pivot;
    }
    pivot->left = nd;

    nd->parent = pivot;
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::PrintTree(Node *nd) {
  if (nd->left != NIL && nd->color == 0) {
    if (nd->left->color == nd->color) {
      throw;
    }
  }
  if (nd->right != NIL && nd->color == 0) {
    if (nd->right->color == nd->color) {
      throw;
    }
  }
}

template <class Key, class Value>
void BinaryTree<Key, Value>::RotateRight(Node *nd) {
  if (nd->left != NIL) {
    Node *pivot = nd->left;
    nd->left = pivot->right;

    if (pivot->right != NIL) {
      pivot->right->parent = nd;
    }
    pivot->parent = nd->parent;
    if (nd->parent == NIL) {
      root = pivot;
    } else if (nd == nd->parent->right) {
      nd->parent->right = pivot;
    } else {
      nd->parent->left = pivot;
    }
    pivot->right = nd;
    nd->parent = pivot;
  }
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::CreateNode(
    Key K, Value V) {
  Node *nd = new Node();
  nd->key = K;
  nd->val = V;
  nd->parent = nd->right = nd->left = nullptr;

  return nd;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::MinimumTree(
    Node *nd) {
  if (nd == NIL) {
    return NIL;
  }
  if (nd->left == NIL) {
    return nd;
  }
  return MinimumTree(nd->left);
};

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::MaximumTree(
    Node *nd) {
  if (nd == NIL) {
    return NIL;
  }
  if (nd->right == NIL) {
    return nd;
  }
  return MaximumTree(nd->right);
};

template <class Key, class Value>
void BinaryTree<Key, Value>::DeleteNode(Key pos) {
  Node *curr = GetNodeViaKey(pos);
  if (curr == NIL) {
    return;
  }
  Node *y = curr;
  Node *x;
  int y_original_color = y->color;

  if (y->left == NIL) {
    x = curr->right;
    RBTransplant(curr, curr->right);
  } else if (curr->right == NIL) {
    x = curr->left;
    RBTransplant(curr, curr->left);
  } else {
    y = MinimumTree(curr->right);
    y_original_color = y->color;
    x = y->right;

    if (y->parent == curr) {
      x->parent = y;
    } else {
      RBTransplant(y, y->right);
    }
    RBTransplant(curr, y);

    y->left = curr->left;
    y->left->parent = y;
    y->color = curr->color;
  }

  if (y_original_color == 1) {
    RBDeleteFixup(x);
  }

  delete curr;
  curr = nullptr;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::MoveIterator(
    Node *nd) {
  if (nd->right != NIL) {
    return MinimumTree(nd->right);
  }

  Node *parent = nd->parent;
  while (parent != NIL && nd == parent->right) {
    nd = parent;
    parent = parent->parent;
  }

  return parent;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::CreateNIL() {
  Node *NIL = new Node();
  NIL->left = nullptr;
  NIL->right = nullptr;
  NIL->parent = nullptr;
  NIL->color = 1;
  return NIL;
}

template <class Key, class Value>
void BinaryTree<Key, Value>::InsertCheck(Node *nd) {
  int RED = 0;
  int BLACK = 1;
  Node *uncle;
  /*
      При вставке нового узла может нарушиться только свойство 1 и 4:
      1. Корень должен быть черным
      4. Красный узел имеет только черных потомков.
      Проверка вставленной ноды начинается а том случае, если родитель красный.
  */
  while (nd->parent->color == RED) {
    /*
        Проверяем, является ли отец левым потомком или правым.
        Это нужно для того, чтобы понять, какой поворот использовать.
        Как это нам поможет? Правый поворот позволяет поднять левого потомка,
        т.е. сбалансировать дерево для левой добавленной ноды. Левый поворот,
        наоборот, поднимает правого потомка.
    */
    if (nd->parent == nd->parent->parent->right) {
      /*
      Если добавленная нода находится в правом поддереве, значит она
      самая большая для поддерева, которое начинается с дедушки текущего дерева.
      Теперь нужно определить цвет дяди.
      */
      uncle = nd->parent->parent->left;
      if (uncle->color == RED) {
        /* В таком случае возможен свап цветов: дедушка красный, дядя с папой
         * черные */
        nd->parent->parent->color = RED;
        nd->parent->color = BLACK;
        uncle->color = BLACK;
        nd = nd->parent->parent;
        /* Так как мы меняем цвет дедушки на красный, то может нарушится
        свойство 4, так как он может быть сыном красного отца */
        continue;
      } else if (nd == nd->parent->left) {
        nd = nd->parent;
        RotateRight(nd);
        continue;
      }
      nd->parent->color = BLACK;
      nd->parent->parent->color = RED;
      RotateLeft(nd->parent->parent);
    } else {
      /*
      Если добавленная нода находится в правом поддереве, значит она
      самая большая для поддерева, которое начинается с дедушки текущего дерева.
      Теперь нужно определить цвет дяди.
      */
      uncle = nd->parent->parent->right;
      if (uncle->color == RED) {
        /* В таком случае возможен свап цветов: дедушка красный, дядя с папой
         * черные */
        nd->parent->parent->color = RED;
        nd->parent->color = BLACK;
        uncle->color = BLACK;
        nd = nd->parent->parent;
        /* Так как мы меняем цвет дедушки на красный, то может нарушится
        свойство 4, так как он может быть сыном красного отца */
        continue;
      } else if (nd == nd->parent->right) {
        nd = nd->parent;
        RotateLeft(nd);
        continue;
      }
      nd->parent->color = BLACK;
      nd->parent->parent->color = RED;
      RotateRight(nd->parent->parent);
    }
  }

  root->color = 1;
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::Insert(Node *nd) {
  bool status(true);
  Node *curr = root;
  Node *temp = NIL;

  int RED = 0;

  while (curr != NIL) {
    temp = curr;
    if (curr->key == nd->key) {
      delete nd;
      return false;
    }
    if (nd->key < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  nd->parent = temp;

  if (temp == NIL) {
    root = nd;
    root->parent = NIL;
  } else if (nd->key < temp->key) {
    temp->left = nd;
  } else {
    temp->right = nd;
  }

  nd->left = NIL;
  nd->right = NIL;
  nd->color = RED;

  InsertCheck(nd);
  count++;
  return status;
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::InsertValueViaKey(key_type K, mapped_type V,
                                               int assign) {
  Node *curr = root;
  Node *temp = NIL;
  (void)temp;

  if (assign == 0) {
    return Insert(CreateNode(K, V));
  } else {
    while (curr != NIL) {
      temp = curr;
      if (curr->key == K) {
        curr->val = V;
        return false;
      }
      if (K < curr->key) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
  }
  return Insert(CreateNode(K, V));  // working
                                    // return false;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::GetNode(
    const Key &key) {
  Node *nd = root;

  if (key == nd->key) {
    return nd;
  }

  while (nd != NIL) {
    if (key > nd->key) {
      nd = nd->right;
    } else if (key < nd->key) {
      nd = nd->left;
    } else {
      return nd;
    }
  }

  return nullptr;
};

// Конструктор итератора по умолчанию
template <class Key, class Value>
BinaryTree<Key, Value>::Iterator::Iterator() {
  first = nullptr;
  second = nullptr;
  current = nullptr;
  tr = nullptr;
}

template <class Key, class Value>
BinaryTree<Key, Value>::Iterator::Iterator(BinaryTree<Key, Value>::Node *nd) {
  current = nd;
  first = &(nd->key);
  second = &(nd->val);
}

// Конструктор с ссылкой на дерево. Дерево передается для будущих операций
// итерации по дереву.
template <class Key, class Value>
BinaryTree<Key, Value>::Iterator::Iterator(BinaryTree<Key, Value>::Node *nd,
                                           BinaryTree<Key, Value> *tree) {
  current = nd;
  tr = tree;
  first = &(nd->key);
  second = &(nd->val);
}

template <class Key, class Value>
BinaryTree<Key, Value>::Iterator::Iterator(const Iterator &it) {
  first = it.first;
  second = it.second;
  tr = it.tr;
  current = it.current;
}

template <class Key, class Value>
BinaryTree<Key, Value>::Iterator::Iterator(Iterator &&it) {
  if (tr != it.tr) {
    first = it.first;
    second = it.second;
    tr = it.tr;
    current = it.current;
    it.tr = nullptr;
    it.second = nullptr;
    it.first = nullptr;
    it.current = nullptr;
  }
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Iterator
BinaryTree<Key, Value>::Iterator::operator=(Iterator &&other) {
  if (tr != other.tr) {
    first = other.first;
    second = other.second;
    tr = other.tr;
    current = other.current;
    other.tr = nullptr;
    other.second = nullptr;
    other.first = nullptr;
    other.current = nullptr;
  }
  return *this;
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::Iterator::operator!=(Iterator &other) {
  bool res = true;

  if (tr == other.tr && current == other.current) {
    res = false;
  }

  return res;
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::Iterator::operator!=(Iterator &&other) {
  bool res = true;

  if (tr == other.tr && current == other.current) {
    res = false;
  }

  return res;
}

template <class Key, class Value>
BinaryTree<Key, Value>::Iterator::Iterator(const value_type &value) {
  current = GetNode(std::get<0>(value));
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::begin() {
  return BinaryTree<Key, Value>::Iterator(RecursiveMinimum(), this);
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Iterator BinaryTree<Key, Value>::end() {
  BinaryTree<Key, Value>::Iterator it =
      BinaryTree<Key, Value>::Iterator(NIL, this);
  return it;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Iterator *
BinaryTree<Key, Value>::insert_iterator(const value_type &value) {
  BinaryTree<Key, Value>::Iterator *it =
      new BinaryTree<Key, Value>::Iterator(GetNode(std::get<0>(value)));
  return it;
}

// Меняем на возврат референса!
template <class Key, class Value>
typename BinaryTree<Key, Value>::mapped_type
BinaryTree<Key, Value>::Iterator::operator*() {
  return *second;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Iterator
BinaryTree<Key, Value>::Iterator::operator++() {
  current = tr->MoveIterator(current);
  if (current) {
    first = &(current->key);
    second = &(current->val);
  }
  return *this;
}

// template <class Key, class Value>
// typename BinaryTree<Key, Value>::Iterator& BinaryTree<Key,
// Value>::Iterator::operator++()
// {
//     current = tr->MoveIterator(current);
//     if (current) {
//         first = &(current->key);
//         second = &(current->val);
//     }
//     return *this;
// }

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *
BinaryTree<Key, Value>::RecursiveMinimum() {
  return GetMinimumNode(root);
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Iterator
BinaryTree<Key, Value>::Iterator::operator--() {
  current = tr->MoveBackwardIterator(current);
  if (current) {
    first = &(current->key);
    second = &(current->val);
  }
  return *this;
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *
BinaryTree<Key, Value>::RecursiveMaximum() {
  return GetMaximumNode(root);
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::GetMinimumNode(
    Node *nd) {
  if (nd == NIL) {
    return nullptr;
  }
  if (nd->left == NIL) {
    return nd;
  }
  return GetMinimumNode(nd->left);
}

template <class Key, class Value>
typename BinaryTree<Key, Value>::Node *BinaryTree<Key, Value>::GetMaximumNode(
    Node *nd) {
  if (nd == NIL) {
    return nullptr;
  }
  if (nd->right == NIL) {
    return nd;
  }
  return GetMaximumNode(nd->right);
}

#endif  // S21_BINARY_TREE
