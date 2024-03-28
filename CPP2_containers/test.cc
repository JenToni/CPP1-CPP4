#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "s21_containers.h"
#include "s21_containers_plus.h"

TEST(Vector, BaseConstructor) {
  s21::vector<int> s21v;
  std::vector<int> v;
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
}

TEST(Vector, ParamConstructor) {
  s21::vector<int> s21v(3);
  std::vector<int> v(3);
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
}

TEST(Vector, CopyConstructor) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<int> s21v_2(s21v_1);
  std::vector<int> v_1 = {1, 2, 3};
  std::vector<int> v_2(v_1);
  EXPECT_EQ(v_2.capacity(), s21v_2.capacity());
  EXPECT_EQ(v_2.size(), s21v_2.size());
  for (size_t i = 0; i < v_2.size(); i++) EXPECT_EQ(v_2[i], s21v_2[i]);
}

TEST(Vector, MoveConstructor) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<int> s21v_2(std::move(s21v_1));
  std::vector<int> v_1 = {1, 2, 3};
  std::vector<int> v_2(std::move(v_1));
  EXPECT_EQ(v_2.capacity(), s21v_2.capacity());
  EXPECT_EQ(v_2.size(), s21v_2.size());
  for (size_t i = 0; i < v_2.size(); i++) EXPECT_EQ(v_2[i], s21v_2[i]);
}

TEST(Vector, EqOperator) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<int> s21v_2 = {4, 5, 6};
  s21v_1 = s21v_2;
  std::vector<int> v_1 = {1, 2, 3};
  std::vector<int> v_2 = {4, 5, 6};
  v_1 = v_2;
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
}

TEST(Vector, EqOperator2) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<int> s21v_2 = {4, 5, 6, 5};
  s21v_1 = std::move(s21v_2);
  std::vector<int> v_1 = {1, 2, 3};
  std::vector<int> v_2 = {4, 5, 6, 5};
  v_1 = std::move(v_2);
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
}

TEST(Vector, EqOperator3) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<int> s21v_2 = {4, 5, 6, 5};
  s21v_1 = s21v_2;
  std::vector<int> v_1 = {1, 2, 3};
  std::vector<int> v_2 = {4, 5, 6, 5};
  v_1 = v_2;
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
}

TEST(Vector, At) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<double> s21v_2 = {4.45645, 5.97709, -6.34, 9.8};
  EXPECT_EQ(s21v_1.at(2), 3);
  EXPECT_EQ(s21v_2.at(3), 9.8);
}

TEST(Vector, At2) {
  s21::vector<double> s21v_2 = {4.45645, 5.97709, -6.34, 9.8};
  EXPECT_ANY_THROW(s21v_2.at(8));
}

TEST(Vector, BracketOperator) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<double> s21v_2 = {4.45645, 5.97709, -6.34, 9.8};
  EXPECT_EQ(s21v_1[2], 3);
  EXPECT_EQ(s21v_2[3], 9.8);
}

TEST(Vector, Front) {
  s21::vector<int> s21v = {5, 8, 9, 112};
  std::vector<int> v = {5, 8, 9, 112};
  EXPECT_EQ(v.front(), s21v.front());
}

TEST(Vector, Back) {
  s21::vector<int> s21v = {5, 8, 9, 112};
  std::vector<int> v = {5, 8, 9, 112};
  EXPECT_EQ(v.back(), s21v.back());
}

TEST(Vector, Data) {
  s21::vector<int> s21v = {5, 8, 9, 112};
  std::vector<int> v = {5, 8, 9, 112};
  EXPECT_EQ(*v.data(), *s21v.data());
}

TEST(Vector, Empty) {
  s21::vector<int> s21v = {5, 8, 9, 112};
  std::vector<int> v = {5, 8, 9, 112};
  EXPECT_EQ(v.empty(), s21v.empty());
}

TEST(Vector, Empty2) {
  s21::vector<int> s21v;
  std::vector<int> v;
  EXPECT_EQ(v.empty(), s21v.empty());
}

TEST(Vector, Empty3) {
  s21::vector<int> s21v = {5, 8, 9, 112};
  std::vector<int> v = {5, 8, 9, 112};
  for (size_t i = 0; i < v.size(); i++) {
    s21v.pop_back();
    v.pop_back();
  }
  EXPECT_EQ(v.empty(), s21v.empty());
}

TEST(Vector, Empty4) {
  s21::vector<int> s21v = {5, 8, 9, 112, 56, 7779};
  std::vector<int> v = {5, 8, 9, 112};
  v.clear();
  s21v.clear();
  EXPECT_EQ(v.empty(), s21v.empty());
}

TEST(Vector, Reserve) {
  s21::vector<double> s21v(4);
  std::vector<double> v(4);
  EXPECT_ANY_THROW(v.reserve(v.max_size() + 23));
  EXPECT_ANY_THROW(s21v.reserve(s21v.max_size() + 23));
}

TEST(Vector, Reserve2) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};
  v.reserve(23);
  s21v.reserve(23);
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, ShrinkToFit) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};
  v.reserve(23);
  s21v.reserve(23);
  v.shrink_to_fit();
  s21v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, Clear2) {
  s21::vector<double> s21v;
  std::vector<double> v;
  v.clear();
  s21v.clear();
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  EXPECT_EQ(v.empty(), s21v.empty());
}

TEST(Vector, Clear) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};
  v.clear();
  s21v.clear();
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  EXPECT_EQ(v.empty(), s21v.empty());
}

TEST(Vector, Insert) {
  s21::vector<double> s21v;
  std::vector<double> v;

  EXPECT_EQ(*v.insert(v.begin(), 23.345), *s21v.insert(s21v.begin(), 23.345));

  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);

  try {
    s21v.insert(s21v.begin() + 100, 23.345);
  } catch (const std::exception &e) {
    EXPECT_EQ(e.what(),
              std::string("Requested position is out of vector range"));
  }
}

TEST(Vector, Erase) {
  s21::vector<double> s21v_1 = {1, 23, 54, 56};
  std::vector<double> v_1 = {1, 23, 54, 56};

  v_1.erase(v_1.begin() + 2);
  s21v_1.erase(s21v_1.begin() + 2);
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
}

TEST(Vector, Erase2) {
  s21::vector<double> s21v_1 = {1, 23, 54};
  std::vector<double> v_1 = {1, 23, 54};

  v_1.erase(v_1.begin() + 2);
  s21v_1.erase(s21v_1.begin() + 2);
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
}

TEST(Vector, PushBack) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};

  v.push_back(2.678);
  s21v.push_back(2.678);
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, PushBack2) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};
  v.reserve(8);
  s21v.reserve(8);
  v.push_back(2.678);
  s21v.push_back(2.678);
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, PushBack3) {
  s21::vector<double> s21v;
  std::vector<double> v;

  v.push_back(2.678);
  s21v.push_back(2.678);
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, PopBack) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};
  v.pop_back();
  s21v.pop_back();
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, PopBack2) {
  s21::vector<double> s21v = {1, 23, 54, 56};
  std::vector<double> v = {1, 23, 54, 56};
  v.reserve(23);
  s21v.reserve(23);
  v.pop_back();
  s21v.pop_back();
  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, Swap) {
  s21::vector<int> s21v_1 = {1, 2, 3};
  s21::vector<int> s21v_2 = {4, 5, 6};
  std::vector<int> v_1 = {1, 2, 3};
  std::vector<int> v_2 = {4, 5, 6};
  v_1.swap(v_2);
  s21v_1.swap(s21v_2);
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_2.capacity(), s21v_2.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  EXPECT_EQ(v_2.size(), s21v_2.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
  for (size_t i = 0; i < v_2.size(); i++) EXPECT_EQ(v_2[i], s21v_2[i]);
}

TEST(Vector, Swap2) {
  s21::vector<int> s21v_1 = {1, 2, 3, 4};
  s21::vector<int> s21v_2 = {4, 5, 6};
  std::vector<int> v_1 = {1, 2, 3, 4};
  std::vector<int> v_2 = {4, 5, 6};
  v_1.swap(v_2);
  s21v_1.swap(s21v_2);
  EXPECT_EQ(v_1.capacity(), s21v_1.capacity());
  EXPECT_EQ(v_2.capacity(), s21v_2.capacity());
  EXPECT_EQ(v_1.size(), s21v_1.size());
  EXPECT_EQ(v_2.size(), s21v_2.size());
  for (size_t i = 0; i < v_1.size(); i++) EXPECT_EQ(v_1[i], s21v_1[i]);
  for (size_t i = 0; i < v_2.size(); i++) EXPECT_EQ(v_2[i], s21v_2[i]);
}

TEST(Vector, Begin) {
  s21::vector<int> s21v = {5, 8, 9, 112};
  std::vector<int> v = {5, 8, 9, 112};
  EXPECT_EQ(*v.begin(), *s21v.begin());
}

TEST(Vector, End) {
  s21::vector<int> s21v;
  std::vector<int> v;
  EXPECT_EQ(v.end() - v.begin(), s21v.end() - s21v.begin());
}

TEST(Vector, erase) {
  s21::vector<int> s21v = {1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

  s21v.erase(s21v.begin() + 2);
  v.erase(v.begin() + 2);

  EXPECT_EQ(v.capacity(), s21v.capacity());
  EXPECT_EQ(v.size(), s21v.size());

  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);

  try {
    s21v.erase(s21v.begin() + 100);
  } catch (const std::exception &e) {
    EXPECT_EQ(e.what(),
              std::string("Requested position is out of vector range"));
  }
}

TEST(Vector, insert_many) {
  s21::vector<char> s21v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  std::vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  s21v.insert_many(s21v.begin() + 2, 'x', 'y', 'z');
  v.insert(v.begin() + 2, 'x');
  v.insert(v.begin() + 3, 'y');
  v.insert(v.begin() + 4, 'z');
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);

  s21v.insert_many_back('Q', 'W', 'E', 'R', 'T', 'Y', 'c', 'd', 'e', 'f', 'i',
                        'n');
  v.insert(v.end(), 'Q');
  v.insert(v.end(), 'W');
  v.insert(v.end(), 'E');
  v.insert(v.end(), 'R');
  v.insert(v.end(), 'T');
  v.insert(v.end(), 'Y');
  v.insert(v.end(), 'c');
  v.insert(v.end(), 'd');
  v.insert(v.end(), 'e');
  v.insert(v.end(), 'f');
  v.insert(v.end(), 'i');
  v.insert(v.end(), 'n');
  EXPECT_EQ(v.size(), s21v.size());
  for (size_t i = 0; i < v.size(); i++) EXPECT_EQ(v[i], s21v[i]);
}

TEST(Vector, size) {
  s21::vector<int> s21v = {1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};

  EXPECT_EQ(v.size(), s21v.size());
  EXPECT_EQ(v.capacity(), s21v.capacity());

  s21v.push_back(9);
  v.push_back(9);

  s21v.insert(s21v.begin() + 2, 10);
  v.insert(v.begin() + 2, 10);

  EXPECT_EQ(v.size(), s21v.size());
  EXPECT_EQ(v.capacity(), s21v.capacity());

  s21v.pop_back();
  v.pop_back();

  EXPECT_EQ(v.size(), s21v.size());
  EXPECT_EQ(v.capacity(), s21v.capacity());

  EXPECT_EQ(v.max_size(), s21v.max_size());
}

TEST(Vector, max_size) {
  s21::vector<int> s21v1;
  s21::vector<char> s21v2;
  s21::vector<double> s21v3;
  s21::vector<float> s21v4;
  s21::vector<long> s21v5;
  s21::vector<long long> s21v6;
  s21::vector<short> s21v7;
  s21::vector<unsigned int> s21v8;
  s21::vector<unsigned char> s21v9;
  s21::vector<unsigned long> s21v10;
  s21::vector<unsigned long long> s21v11;
  s21::vector<unsigned short> s21v12;
  s21::vector<std::string> s21v13;
  s21::vector<std::vector<int>> s21v14;
  s21::vector<std::vector<std::string>> s21v15;
  s21::vector<std::vector<std::vector<int>>> s21v16;

  std::vector<int> v1;
  std::vector<char> v2;
  std::vector<double> v3;
  std::vector<float> v4;
  std::vector<long> v5;
  std::vector<long long> v6;
  std::vector<short> v7;
  std::vector<unsigned int> v8;
  std::vector<unsigned char> v9;
  std::vector<unsigned long> v10;
  std::vector<unsigned long long> v11;
  std::vector<unsigned short> v12;
  std::vector<std::string> v13;
  std::vector<std::vector<int>> v14;
  std::vector<std::vector<std::string>> v15;
  std::vector<std::vector<std::vector<int>>> v16;

  EXPECT_EQ(v1.max_size(), s21v1.max_size());
  EXPECT_EQ(v2.max_size(), s21v2.max_size());
  EXPECT_EQ(v3.max_size(), s21v3.max_size());
  EXPECT_EQ(v4.max_size(), s21v4.max_size());
  EXPECT_EQ(v5.max_size(), s21v5.max_size());
  EXPECT_EQ(v6.max_size(), s21v6.max_size());
  EXPECT_EQ(v7.max_size(), s21v7.max_size());
  EXPECT_EQ(v8.max_size(), s21v8.max_size());
  EXPECT_EQ(v9.max_size(), s21v9.max_size());
  EXPECT_EQ(v10.max_size(), s21v10.max_size());
  EXPECT_EQ(v11.max_size(), s21v11.max_size());
  EXPECT_EQ(v12.max_size(), s21v12.max_size());
  EXPECT_EQ(v13.max_size(), s21v13.max_size());
  EXPECT_EQ(v14.max_size(), s21v14.max_size());
  EXPECT_EQ(v15.max_size(), s21v15.max_size());
  EXPECT_EQ(v16.max_size(), s21v16.max_size());
}

template <typename value_type>
bool compare_stacks(s21::stack<value_type> my_stack,
                    std::stack<value_type> std_stack) {
  bool result = true;
  if (my_stack.size() == std_stack.size()) {
    while (!my_stack.empty() && !std_stack.empty()) {
      if (my_stack.top() != std_stack.top()) {
        result = false;
        break;
      }
      my_stack.pop();
      std_stack.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Stack, Constructor_default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(Stack, Constructor_initializer_list) {
  s21::stack<int> s21_stack{1, 2, 4};
  std::initializer_list<int> b = {1, 2, 4};
  std::stack<int> std_stack{b};
  EXPECT_TRUE(compare_stacks(s21_stack, std_stack));
  s21_stack.push(20);
  EXPECT_FALSE(compare_stacks(s21_stack, std_stack));
  std_stack.push(21);
  EXPECT_FALSE(compare_stacks(s21_stack, std_stack));
}

TEST(Stack, Constructor_copy) {
  std::initializer_list<int> A = {1, 2, 3};

  s21::stack<int> s21_stack{A};
  s21::stack<int> s21_stack_copy{s21_stack};

  std::stack<int> std_stack{A};
  std::stack<int> std_stack_copy{std_stack};

  EXPECT_TRUE(compare_stacks(s21_stack, std_stack));
}

TEST(Stack, Constructor_move) {
  std::initializer_list<int> A = {1, 2, 3};

  s21::stack<int> s21_stack{A};
  s21::stack<int> s21_stack_move{s21_stack};

  std::stack<int> std_stack{A};
  std::stack<int> std_stack_move{std_stack};

  EXPECT_TRUE(compare_stacks(s21_stack, std_stack));
}

TEST(Stack, Empty) {
  std::initializer_list<int> A = {4, 5, 6, 7};

  s21::stack<int> s21_stack{A};
  std::stack<int> std_stack{A};

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Empty_2) {
  std::initializer_list<int> A;

  s21::stack<int> s21_stack{A};
  std::stack<int> std_stack{A};

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack, Push_1) {
  std::initializer_list<int> A = {4, 5, 6, 7};

  s21::stack<int> s21_stack{A};
  std::stack<int> std_stack{A};
  s21_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Push_2) {
  std::initializer_list<int> A;

  s21::stack<int> s21_stack{A};
  std::stack<int> std_stack{A};
  s21_stack.push(1);
  std_stack.push(1);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Pop) {
  std::initializer_list<int> A = {4, 5, 6, 7};

  s21::stack<int> s21_stack{A};
  std::stack<int> std_stack{A};

  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack, Swap_1) {
  std::initializer_list<int> A = {4, 5, 6, 7};
  std::initializer_list<int> B = {1, 2, 3};

  s21::stack<int> s21_stack{A};
  s21::stack<int> s21_stack_swap{B};

  std::stack<int> std_stack{A};
  std::stack<int> std_stack_swap{B};

  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_TRUE(compare_stacks(s21_stack, std_stack));
  EXPECT_TRUE(compare_stacks(s21_stack_swap, std_stack_swap));
}

TEST(Stack, Swap_2) {
  std::initializer_list<int> A = {4, 5, 6, 7};

  s21::stack<int> s21_stack{A};
  s21::stack<int> s21_stack_swap;

  s21_stack.swap(s21_stack_swap);

  std::stack<int> std_stack{A};
  std::stack<int> std_stack_swap;

  std_stack.swap(std_stack_swap);

  EXPECT_TRUE(compare_stacks(s21_stack, std_stack));
  EXPECT_TRUE(compare_stacks(s21_stack_swap, std_stack_swap));
}

TEST(Stack, InsertManyFront) {
  s21::stack<int> our_stack_int;
  our_stack_int.insert_many_front(1, 2, 3);
  EXPECT_EQ(our_stack_int.top(), 3);
}

template <typename value_type>
bool compare_queues(s21::queue<value_type> my_queue,
                    std::queue<value_type> std_queue) {
  bool result = true;
  if (my_queue.size() == std_queue.size()) {
    while (!my_queue.empty() && !std_queue.empty()) {
      if (my_queue.front() != std_queue.front()) {
        result = false;
        break;
      }
      my_queue.pop();
      std_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(Queue, Constructor_default) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(Queue, Constructor_initializer_list) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::initializer_list<int> b = {1, 3, 10, -5, 20};
  std::queue<int> std_queue{b};
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
  my_queue.push(21);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
}

TEST(Queue, Constructor_copy) {
  std::initializer_list<int> A = {1, 2, 3, 7, 9};

  s21::queue<int> my_queue{A};
  s21::queue<int> my_queue_copy(my_queue);

  std::queue<int> std_queue{A};
  std::queue<int> std_queue_copy(std_queue);

  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(Queue, Constructor_move) {
  std::initializer_list<int> A = {1, 2, 3, 7, 20};

  s21::queue<int> my_queue{A};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));

  std::queue<int> std_queue{A};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));

  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(Queue, Back) {
  std::initializer_list<int> A = {99, 1, 3, 5, 4, 7, 99};

  s21::queue<int> my_queue{A};

  std::queue<int> std_queue{A};

  EXPECT_EQ(my_queue.back(), std_queue.back());
}

TEST(Queue, Empty) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;

  EXPECT_EQ(my_queue.empty(), std_queue.empty());

  my_queue.push(2354);
  std_queue.push(2354);

  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(Queue, Empty_2) {
  std::initializer_list<int> A;
  s21::queue<int> my_queue{A};
  std::queue<int> std_queue{A};

  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(Queue, Push) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  my_queue.push(627);
  std_queue.push(627);
  my_queue.push(2354);
  std_queue.push(2354);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(Queue, Pop) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> A = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{A};
  my_queue.pop();
  my_queue.pop();
  std_queue.pop();
  std_queue.pop();
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(Queue, Swap) {
  std::initializer_list<int> A = {1, 2, 3, 4, 5};
  std::initializer_list<int> B = {6, 7, 8, 9, 10, 11};

  s21::queue<int> my_queue1{A};
  s21::queue<int> my_queue2{B};

  my_queue1.swap(my_queue2);

  std::queue<int> std_queue1{A};
  std::queue<int> std_queue2{B};

  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(Queue, Swap_2) {
  std::initializer_list<int> A = {1, 2, 99, 4, 242};

  s21::queue<int> my_queue1{A};
  s21::queue<int> my_queue2;

  my_queue1.swap(my_queue2);

  std::queue<int> std_queue1{A};
  std::queue<int> std_queue2;

  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(Queue, InsertManyBack) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

TEST(Map, MapConstructorDefualt) {
  s21::map<int, int> it;

  EXPECT_TRUE(it.empty());
};

TEST(Map, MapConstructorList) {
  s21::map<int, char> map1({{1, 'a'},
                            {2, 'b'},
                            {3, 'c'},
                            {4, 'd'},
                            {5, 'e'},
                            {6, 'f'},
                            {7, 'j'},
                            {8, 'x'}});
  EXPECT_EQ(map1.at(1), 'a');
  EXPECT_EQ(map1.at(2), 'b');
  EXPECT_EQ(map1.at(3), 'c');
  EXPECT_EQ(map1.at(4), 'd');
  EXPECT_EQ(map1.at(5), 'e');
  EXPECT_EQ(map1.at(6), 'f');
  EXPECT_EQ(map1.at(7), 'j');
  EXPECT_EQ(map1.at(8), 'x');
  EXPECT_FALSE(map1.empty());
};

TEST(Map, MapConstructorCopyOperator) {
  s21::map<int, char> map2({{1, 'a'},
                            {2, 'b'},
                            {3, 'c'},
                            {4, 'd'},
                            {5, 'e'},
                            {6, 'f'},
                            {7, 'j'},
                            {8, 'x'}});
  s21::map<int, char> map1 = map2;
  EXPECT_EQ(map2.at(1), 'a');
  EXPECT_EQ(map2.at(2), 'b');
  EXPECT_EQ(map2.at(3), 'c');
  EXPECT_EQ(map2.at(4), 'd');
  EXPECT_EQ(map2.at(5), 'e');
  EXPECT_EQ(map2.at(6), 'f');
  EXPECT_EQ(map2.at(7), 'j');
  EXPECT_EQ(map2.at(8), 'x');
};

TEST(Map, MapConstructorCopy) {
  s21::map<int, char> map2({{1, 'a'},
                            {2, 'b'},
                            {3, 'c'},
                            {4, 'd'},
                            {5, 'e'},
                            {6, 'f'},
                            {7, 'j'},
                            {8, 'x'}});
  s21::map<int, char> map1(map2);
  EXPECT_EQ(map1[1], 'a');
  EXPECT_EQ(map1[2], 'b');
  EXPECT_EQ(map1[3], 'c');
  EXPECT_EQ(map1[4], 'd');
  EXPECT_EQ(map1[5], 'e');
  EXPECT_EQ(map1[6], 'f');
  EXPECT_EQ(map1[7], 'j');
  EXPECT_EQ(map1[8], 'x');
};

TEST(Map, MapConstructorMove) {
  s21::map<int, char> map2({{1, 'a'},
                            {2, 'b'},
                            {3, 'c'},
                            {4, 'd'},
                            {5, 'e'},
                            {6, 'f'},
                            {7, 'j'},
                            {8, 'x'}});
  s21::map<int, char> map1 = std::move(map2);
  EXPECT_EQ(map1[1], 'a');
  EXPECT_EQ(map1[2], 'b');
  EXPECT_EQ(map1[3], 'c');
  EXPECT_EQ(map1[4], 'd');
  EXPECT_EQ(map1[5], 'e');
  EXPECT_EQ(map1[6], 'f');
  EXPECT_EQ(map1[7], 'j');
  EXPECT_EQ(map1[8], 'x');
  EXPECT_EQ(map2.empty(), true);
};

TEST(Map, MapIteratorBegin) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}});
  s21::map<int, char>::MapIterator it = map1.begin();
  EXPECT_EQ(std::get<1>(*it), 'a');
};

TEST(Map, MapIteratorEndBegin) {
  s21::map<int, char> map1;
  s21::map<int, char>::MapIterator start = map1.begin();
  s21::map<int, char>::MapIterator end = map1.end();
  EXPECT_FALSE(start != end);
};

TEST(Map, MapIteratorEnd) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  s21::map<int, char>::MapIterator it = map1.end();
  --it;
  EXPECT_EQ(std::get<1>(*it), 'v');
  --it;
};

TEST(Map, MapSize) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(map1.size(), 3);
};

TEST(Map, MapSizeMax) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}});
  std::map<int, char> map2({{1, 'a'}, {2, 'b'}});
  EXPECT_EQ(map1.max_size(), map2.max_size() * 10 + 1);
};

TEST(Map, MapInsert) {
  std::pair<const int, char> pair(3, 'f');
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(true, std::get<1>(map1.insert(pair)));
  EXPECT_EQ(map1.at(3), 'f');
};

TEST(Map, MapInsertError) {
  std::pair<const int, char> pair(1, 'f');
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(false, std::get<1>(map1.insert(pair)));
};

TEST(Map, MapInsertViaValue) {
  int K(3);
  char V('z');
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(true, std::get<1>(map1.insert(K, V)));
  EXPECT_EQ(map1.at(3), 'z');
};

TEST(Map, MapInsertViaValueError) {
  int K(2);
  char V('z');
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(false, std::get<1>(map1.insert(K, V)));
};

TEST(Map, MapInsertAssign) {
  int K(2);
  char V('z');
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(false, std::get<1>(map1.insert_or_assign(K, V)));
  EXPECT_EQ(map1.at(2), 'z');
};

TEST(Map, MapInsertAssignInsert) {
  int K(6);
  char V('z');
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  EXPECT_EQ(true, std::get<1>(map1.insert_or_assign(K, V)));
  EXPECT_EQ(map1.at(6), 'z');
};

TEST(Map, MapEraseSimple1) {
  s21::map<int, char> e;
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  map1.erase(map1.begin());
  EXPECT_EQ(map1.contains(1), false);
  EXPECT_EQ(map1.contains(19), true);
  e.erase(e.begin());
};

TEST(Map, MapEraseAdvanced1) {
  s21::map<int, char> map1({{1, 'a'},
                            {2, 'b'},
                            {19, 'v'},
                            {124, 'c'},
                            {243, 'v'},
                            {454, 'z'},
                            {100, 'x'},
                            {3553, 'b'}});
  s21::map<int, char>::MapIterator t1 = map1.begin();
  EXPECT_EQ(map1.contains(1), true);
  map1.erase(t1);
  EXPECT_EQ(map1.contains(1), false);
  s21::map<int, char>::MapIterator t2 = map1.end();
  --t2;
  map1.erase(t2);
  EXPECT_EQ(map1.contains(3553), false);
};

TEST(Map, MapEraseAdvanced2) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {3, 'v'}, {4, 'c'}});
  s21::map<int, char>::MapIterator t1 = map1.begin();
  map1.erase(t1);
  EXPECT_EQ(map1.contains(1), false);
};

TEST(Map, MapEraseAdvanced3) {
  s21::map<int, char> map1({{2, 'b'}, {3, 'v'}, {4, 'c'}, {5, 'x'}});
  s21::map<int, char>::MapIterator t1 = map1.begin();
  map1.erase(t1);
  EXPECT_EQ(map1.contains(2), false);
};

TEST(Map, MapEraseAdvanced4) {
  s21::map<int, char> map1(
      {{20, 'b'}, {30, 'v'}, {35, 'c'}, {40, 'x'}, {50, 'x'}});
  s21::map<int, char>::MapIterator t1 = map1.begin();
  map1.erase(t1);
  EXPECT_EQ(map1.contains(20), false);
};

TEST(Map, MapEraseAdvanced5) {
  s21::map<int, char> map1(
      {{10, 'b'}, {20, 'v'}, {30, 'c'}, {25, 'd'}, {35, 'x'}});
  s21::map<int, char>::MapIterator t1 = map1.begin();
  map1.erase(t1);
  EXPECT_EQ(map1.contains(10), false);
};

TEST(Map, MapEraseAdvanced6) {
  s21::map<int, char> map1({{1, 'a'},
                            {2, 'b'},
                            {19, 'v'},
                            {124, 'c'},
                            {243, 'v'},
                            {454, 'z'},
                            {100, 'x'},
                            {3553, 'b'}});
  s21::map<int, char>::MapIterator t1 = map1.begin();
  EXPECT_EQ(map1.contains(1), true);
  map1.erase(t1);
  EXPECT_EQ(map1.contains(1), false);
  s21::map<int, char>::MapIterator t2 = map1.end();
  --t2;
  map1.erase(t2);

  EXPECT_EQ(map1.contains(3553), false);
};

TEST(Map, MapConstIterator1) {
  s21::map<int, char> map1({{1, 'a'},
                            {2, 'b'},
                            {19, 'v'},
                            {124, 'c'},
                            {243, 'v'},
                            {454, 'z'},
                            {100, 'x'},
                            {3553, 'b'},
                            {354, 'b'}});
  s21::map<int, char>::MapConstIterator et = map1.end();
  for (s21::map<int, char>::MapConstIterator it = map1.begin(); it != et;
       ++it) {
    EXPECT_EQ(map1.contains(std::get<0>(*it)), true);
  }
};

TEST(Map, MapSwapSimple) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  s21::map<int, char> map2({{2, 'w'}, {4, 'd'}, {22000, 'g'}});
  map1.swap(map2);
  EXPECT_EQ(map1.at(2), 'w');
  EXPECT_EQ(map2.at(19), 'v');
  EXPECT_EQ(map1.contains(22000), true);
};

TEST(Map, MapMergeSimple) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}, {19, 'v'}});
  s21::map<int, char> map2({{3, 'w'}, {4, 'd'}, {10, 'g'}});
  map1.merge(map2);
  EXPECT_EQ(map1.at(2), 'b');
  EXPECT_EQ(map1.at(19), 'v');
  EXPECT_EQ(map1.at(10), 'g');
};

TEST(Map, MapInsertManySimple) {
  s21::map<int, char> map1({{1, 'a'}, {2, 'b'}});

  std::vector<std::pair<s21::map<int, char>::iterator, bool>> gg =
      map1.insert_many(std::pair<int, char>(3, 'c'),
                       std::pair<int, char>(4, 'd'));
  EXPECT_EQ(map1.at(3), 'c');
  EXPECT_EQ(map1.at(4), 'd');
};

TEST(Map, MapInsertMany1) {
  s21::map<int, char> map1;

  std::vector<std::pair<s21::map<int, char>::iterator, bool>> gg =
      map1.insert_many(std::pair<int, char>(3, 'c'),
                       std::pair<int, char>(4, 'd'));
  EXPECT_EQ(map1.at(3), 'c');
  EXPECT_EQ(map1.at(4), 'd');
};

TEST(Map, MapInsertMany2) {
  s21::map<double, char> map1;

  std::vector<std::pair<s21::map<double, char>::iterator, bool>> gg =
      map1.insert_many(
          std::pair<double, char>(3, 'c'), std::pair<double, char>(4, 'd'),
          std::pair<double, char>(5, 'x'), std::pair<double, char>(6, 'y'));
  EXPECT_EQ(map1.at(3), 'c');
  EXPECT_EQ(map1.at(4), 'd');
  EXPECT_EQ(map1.at(5), 'x');
  EXPECT_EQ(map1.at(6), 'y');
};

TEST(Map, MapComparison) {
  s21::map<double, std::string> map_mine({{1, "Carpe"},
                                          {2, "Diem"},
                                          {2355.2, "Noctem"},
                                          {113, "Nihilo"},
                                          {198.22, "Nihim"},
                                          {198.22, "Salve"}});
  std::map<double, std::string> map_orig({{1, "Carpe"},
                                          {2, "Diem"},
                                          {2355.2, "Noctem"},
                                          {113, "Nihilo"},
                                          {198.22, "Nihim"},
                                          {198.22, "Salve"}});

  EXPECT_EQ(map_mine.at(1), map_orig.at(1));
  EXPECT_EQ(map_mine[2355.2], map_orig[2355.2]);

  EXPECT_EQ(map_mine.size(), map_orig.size());

  const std::pair<double, std::string> p1(90, "Audere");
  EXPECT_EQ(std::get<1>(map_mine.insert(p1)), std::get<1>(map_orig.insert(p1)));

  EXPECT_EQ(map_mine.size(), map_orig.size());
  EXPECT_EQ(std::get<1>(map_mine.insert_or_assign(2., std::string("Audere"))),
            std::get<1>(map_orig.insert_or_assign(2., std::string("Audere"))));

  map_mine.erase(map_mine.begin());
  map_orig.erase(map_orig.begin());

  EXPECT_EQ(map_mine.size(), map_orig.size());

  s21::map<double, std::string>::iterator it = map_mine.end();
  std::map<double, std::string>::iterator it1 = map_orig.end();
  --it;
  --it1;

  EXPECT_EQ(map_mine.size(), map_orig.size());
  map_mine.erase(it);
  map_orig.erase(it1);

  EXPECT_EQ(map_mine.size(), map_orig.size());

  map_mine.clear();
  map_orig.clear();

  EXPECT_EQ(map_mine.size(), map_orig.size());
};

template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = true;
  if (my_list.size() == std_list.size() &&
      my_list.front() == std_list.front() &&
      my_list.back() == std_list.back() &&
      my_list.empty() == std_list.empty()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      ++my_it;
      ++std_it;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(List, Constructor_Default) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, Constructor_initializer_list) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  EXPECT_TRUE(compare_lists(s21_list, std_list));

  s21::list<int> s21_list3 = {1};
  std::list<int> std_list3 = {1};

  EXPECT_TRUE(compare_lists(s21_list3, std_list3));

  s21::list<int> s21_list1 = {1, 2, 3};
  std::list<int> std_list1 = {1, 2, 3, 4};

  EXPECT_FALSE(compare_lists(s21_list1, std_list1));

  s21::list<int> s21_list2;
  s21_list2.push_front(4);
  s21_list2.push_front(9);
  s21_list2.push_front(3);
  s21_list2.push_front(1);

  std::list<int> std_list2 = {1, 2, 9, 4};

  EXPECT_FALSE(compare_lists(s21_list2, std_list2));
}

TEST(List, Constructor_Parameterized) {
  s21::list<double> s21_list(10);
  std::list<double> std_list(10);

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Constructor_Copy) {
  s21::list<int> s21_list = {9, 8, 7, 6};
  std::list<int> std_list = {9, 8, 7, 6};
  s21::list<int> s21_list_2 = s21_list;
  std::list<int> std_list_2 = std_list;

  EXPECT_TRUE(compare_lists(s21_list_2, std_list_2));
}

TEST(List, Constructor_Move) {
  s21::list<char> s21_list = {'a', 'b', 'c', 'd'};
  std::list<char> std_list = {'a', 'b', 'c', 'd'};
  s21::list<char> s21_list_2 = std::move(s21_list);
  std::list<char> std_list_2 = std::move(std_list);

  EXPECT_TRUE(compare_lists(s21_list_2, std_list_2));
}

TEST(List, Insert) {
  s21::list<int> s21_list = {'a', 'c', 'd'};
  std::list<int> std_list = {'a', 'b', 'c', 'd'};

  auto it = s21_list.begin();
  ++it;
  s21_list.insert(it, 'b');

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Insert2) {
  s21::list<int> s21_list;

  auto it = s21_list.begin();
  s21_list.insert(it, 'b');

  std::list<int> std_list;

  auto std_it = std_list.begin();
  std_list.insert(std_it, 'b');

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Modifier_Erase) {
  s21::list<int> s21_list = {'a', 'b', 'c', 'd'};
  std::list<int> std_list = {'a', 'c', 'd'};

  auto it = s21_list.begin();
  ++it;
  s21_list.erase(it);

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Modifier_Erase2) {
  s21::list<int> s21_list = {'a', 'b', 'c', 'd'};
  std::list<int> std_list = {'b', 'c'};

  auto it = s21_list.begin();
  s21_list.erase(it);
  it = s21_list.end();
  --it;
  s21_list.erase(it);

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Push) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.push_back(5);
  s21_list.push_front(0);
  std_list.push_back(5);
  std_list.push_front(0);

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Pop) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  s21_list.pop_back();
  s21_list.pop_front();
  std_list.pop_back();
  std_list.pop_front();

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Swap) {
  s21::list<int> s21_list{1, 2, 3, 4, 5, 6};
  s21::list<int> s21_list2{0, 0, 0, 0, 0};
  s21_list.swap(s21_list2);

  std::list<int> std_list{1, 2, 3, 4, 5, 6};
  std::list<int> std_list2{0, 0, 0, 0, 0};
  std_list.swap(std_list2);

  EXPECT_TRUE(compare_lists(s21_list, std_list));
  EXPECT_TRUE(compare_lists(s21_list2, std_list2));
}

TEST(List, Merge) {
  s21::list<int> s21_list = {1, 3, 7};
  s21::list<int> s21_list2 = {-1, 0, 5, 8};

  std::list<int> std_list = {1, 3, 7};
  std::list<int> std_list2 = {-1, 0, 5, 8};

  s21_list.merge(s21_list2);
  std_list.merge(std_list2);

  EXPECT_TRUE(compare_lists(s21_list, std_list));

  EXPECT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List, Merge2) {
  s21::list<int> s21_list;
  s21::list<int> s21_list2 = {-1, 0, 5, 8};

  std::list<int> std_list;
  std::list<int> std_list2 = {-1, 0, 5, 8};

  s21_list.merge(s21_list2);
  std_list.merge(std_list2);

  EXPECT_TRUE(compare_lists(s21_list, std_list));

  EXPECT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List, Merge3) {
  s21::list<int> s21_list = {-1, 0, 5, 8};
  s21::list<int> s21_list2 = {-1};

  std::list<int> std_list = {-1, 0, 5, 8};
  std::list<int> std_list2 = {-1};

  s21_list.merge(s21_list2);
  std_list.merge(std_list2);

  EXPECT_TRUE(compare_lists(s21_list, std_list));

  EXPECT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List, Reverse) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  s21_list.reverse();

  std::list<int> std_list = {1, 2, 3, 4};
  std_list.reverse();

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Unique) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.unique();

  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std_list.unique();

  EXPECT_TRUE(compare_lists(s21_list, std_list));

  s21::list<int> s21_list2{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list2.sort();
  s21_list2.unique();

  std::list<int> std_list2{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std_list2.sort();
  std_list2.unique();

  EXPECT_TRUE(compare_lists(s21_list2, std_list2));
}

TEST(List, Modifier_Sort) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.sort();

  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std_list.sort();

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(List, Insert_Many) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, Insert_Many_Back) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(List, Insert_Many_Front) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(List, Max_size) {
  s21::list<int> our_list;
  EXPECT_EQ(our_list.max_size(),
            std::numeric_limits<std::size_t>::max() / sizeof(s21::list<int>));
}

template <typename value_type, std::size_t N, std::size_t B>
bool compare_arrays(s21::array<value_type, N> my_array,
                    std::array<value_type, B> std_array) {
  bool result = true;
  if (my_array.size() == std_array.size() &&
      my_array.empty() == std_array.empty()) {
    for (size_t i = 0; i < my_array.size() && result; i++) {
      if (my_array[i] != std_array[i]) {
        result = false;
      }
    }
  } else
    result = false;
  return result;
}

TEST(Array, Constructor_Default) {
  s21::array<std::string, 4> my_array;

  EXPECT_EQ(my_array.size(), 4);
}

TEST(Array, Constructor_initializer_list) {
  s21::array<int, 5> my_array{1, 9, 1, 3, 19};

  std::array<int, 5> std_array{1, 9, 1, 3, 19};

  EXPECT_TRUE(compare_arrays(my_array, std_array));
}

TEST(Array, Constructor_Default_2) {
  s21::array<int, 5> my_array{1, 2, 3, 4, 5};

  std::array<int, 2> std_array{1, 2};

  EXPECT_FALSE(compare_arrays(my_array, std_array));
}

TEST(Array, Constructor_Default_3) {
  s21::array<int, 5> my_array{1, 2, 3, 4, 5};

  std::array<int, 5> std_array{1, 2, 4, 5, 6};

  EXPECT_FALSE(compare_arrays(my_array, std_array));
}

TEST(Array, Constructor_initializer_list_and_copy) {
  s21::array<int, 4> my_array{1, 4, 8, 9};
  s21::array<int, 4> my_array_2(my_array);

  std::array<int, 4> std_array{1, 4, 8, 9};
  std::array<int, 4> std_array_2{std_array};

  EXPECT_TRUE(compare_arrays(my_array_2, std_array_2));
}

TEST(Array, Constructor_initializer_list_with_move) {
  s21::array<int, 4> my_array{1, 4, 8, 9};
  s21::array<int, 4> my_array_2 = std::move(my_array);

  std::array<int, 4> std_array{1, 4, 8, 9};
  std::array<int, 4> std_array_2 = std::move(std_array);

  EXPECT_TRUE(compare_arrays(my_array_2, std_array_2));
}

TEST(Array, Constructor_initializer_list_with_move_2) {
  s21::array<int, 4> my_array{1, 4, 8, 9};
  s21::array<int, 4> my_array_2;
  my_array_2 = std::move(my_array);

  std::array<int, 4> std_array{1, 4, 8, 9};
  std::array<int, 4> std_array_2;
  std_array_2 = std::move(std_array);

  EXPECT_TRUE(compare_arrays(my_array_2, std_array_2));
}

TEST(Array, at) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  std::array<int, 4> std_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.at(0), std_array.at(0));
  EXPECT_EQ(my_array.at(3), std_array.at(3));

  EXPECT_THROW(my_array.at(5), std::out_of_range);
}

TEST(Array, front) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  std::array<int, 4> std_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.front(), std_array.front());
}

TEST(Array, back) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  std::array<int, 4> std_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.back(), std_array.back());
}

TEST(Array, data) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.data(), &my_array[0]);
}

TEST(Array, begin) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.begin(), &my_array[0]);
}

TEST(Array, end) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.end(), &my_array[0] + 4);
}

TEST(Array, array_max_size) {
  s21::array<int, 4> my_array{1, 4, 8, 9};

  std::array<int, 4> std_array{1, 4, 8, 9};

  EXPECT_EQ(my_array.max_size(), std_array.max_size());
}

TEST(Array, array_swap) {
  s21::array<int, 4> my_array{1, 4, 8, 9};
  s21::array<int, 4> my_array_2{21, 21, 21, 21};

  std::array<int, 4> std_array{1, 4, 8, 9};
  std::array<int, 4> std_array_2{21, 21, 21, 21};

  my_array.swap(my_array_2);

  std_array.swap(std_array_2);

  EXPECT_TRUE(compare_arrays(my_array, std_array));
  EXPECT_TRUE(compare_arrays(my_array_2, std_array_2));
}

TEST(Array, array_fill) {
  s21::array<int, 4> my_array_int{1, 4, 8, 9};
  s21::array<double, 4> my_array_double{1.4, 4.8, 8.9, 9.1};
  s21::array<std::string, 4> my_array_string{"Hello", ",", "world", "!"};

  my_array_int.fill(21);
  my_array_double.fill(21.0);
  my_array_string.fill("21");

  std::array<int, 4> std_array_int{1, 4, 8, 9};
  std::array<double, 4> std_array_double{1.4, 4.8, 8.9, 9.1};
  std::array<std::string, 4> std_array_string{"Hello", ",", "world", "!"};

  std_array_int.fill(21);
  std_array_double.fill(21.0);
  std_array_string.fill("21");

  EXPECT_TRUE(compare_arrays(my_array_int, std_array_int));
  EXPECT_TRUE(compare_arrays(my_array_double, std_array_double));
  EXPECT_TRUE(compare_arrays(my_array_string, std_array_string));
}

TEST(Set, constructors) {
  s21::set<int> s1;
  s21::set<int> s2{1, 2, 3, 4, 5};
  s21::set<int> s3(s2);
  s21::set<int> s4(std::move(s3));
  s21::set<int> s5 = s4;
  s21::set<int> s6 = std::move(s5);

  std::set<int> std1;
  std::set<int> std2{1, 2, 3, 4, 5};
  std::set<int> std3(std2);
  std::set<int> std4(std::move(std3));
  std::set<int> std5 = std4;
  std::set<int> std6 = std::move(std5);

  EXPECT_EQ(s1.size(), std1.size());
  EXPECT_EQ(s2.size(), std2.size());
  EXPECT_EQ(s3.size(), std3.size());
  EXPECT_EQ(s4.size(), std4.size());
  EXPECT_EQ(s5.size(), std5.size());
  EXPECT_EQ(s6.size(), std6.size());
}

TEST(Set, operators) {
  s21::set<int> s1{1, 2, 3, 4, 5};
  s21::set<int> s2{1, 2, 3, 4, 5};
  s21::set<int> s3{6, 7, 8};
  s1 = s2;
  s1 = std::move(s3);
  s3 = s2;

  std::set<int> std1{1, 2, 3, 4, 5};
  std::set<int> std2{1, 2, 3, 4, 5};
  std::set<int> std3{6, 7, 8};
  std1 = std2;
  std1 = std::move(std3);
  std3 = std2;

  EXPECT_EQ(s1.size(), std1.size());
  EXPECT_EQ(s2.size(), std2.size());
  EXPECT_EQ(s3.size(), std3.size());

  bool b12 = s1 == s2;
  bool b13 = s1 == s3;
  bool b23 = s2 == s3;

  bool std_b12 = std1 == std2;
  bool std_b13 = std1 == std3;
  bool std_b23 = std2 == std3;

  EXPECT_EQ(b12, std_b12);
  EXPECT_EQ(b13, std_b13);
  EXPECT_EQ(b23, std_b23);

  b12 = s1 != s2;
  b13 = s1 != s3;
  b23 = s2 != s3;

  std_b12 = std1 != std2;
  std_b13 = std1 != std3;
  std_b23 = std2 != std3;

  EXPECT_EQ(b12, std_b12);
  EXPECT_EQ(b13, std_b13);
  EXPECT_EQ(b23, std_b23);
}

TEST(Set, test_txt) {
  std::ifstream file("test.txt");
  std::string str;
  s21::set<std::string> s21;
  std::set<std::string> std;
  const char *delimiters = " \n\t,.:;!?-()[]{}'\"";
  while (getline(file, str)) {
    char *word = strtok((char *)str.data(), delimiters);
    while (word != nullptr) {
      s21.insert(word);
      std.insert(word);
      word = strtok(nullptr, delimiters);
    }
  }
  EXPECT_EQ(s21.size(), std.size());
  auto it1 = s21.begin();
  auto it2 = std.begin();
  for (; it1 != s21.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  s21::set<std::string> s21_1{"the", "red", "black", "tree", "fox"};
  std::set<std::string> std_1{"the", "red", "black", "tree", "fox"};

  s21_1.merge(s21);
  std_1.merge(std);
  EXPECT_EQ(s21.size(), std.size());
  EXPECT_EQ(s21_1.size(), std_1.size());
  it1 = s21_1.begin();
  it2 = std_1.begin();
  for (; it1 != s21_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }

  s21_1.insert("Lorem");
  s21_1.insert("ipsum");
  s21_1.insert("dolor");
  s21_1.insert("sit");
  s21_1.insert("amet");
  std_1.insert("Lorem");
  std_1.insert("ipsum");
  std_1.insert("dolor");
  std_1.insert("sit");
  std_1.insert("amet");

  EXPECT_EQ(s21_1.size(), std_1.size());
  it1 = s21_1.begin();
  it2 = std_1.begin();
  for (; it1 != s21_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }

  s21_1.erase(s21_1.find("Figure"));
  s21_1.erase(s21_1.find("right"));
  s21_1.erase(s21_1.find("left"));
  s21_1.erase(s21_1.find("color"));
  std_1.erase(std_1.find("Figure"));
  std_1.erase(std_1.find("right"));
  std_1.erase(std_1.find("left"));
  std_1.erase(std_1.find("color"));

  EXPECT_EQ(s21_1.size(), std_1.size());
  it1 = s21_1.begin();
  it2 = std_1.begin();
  for (; it1 != s21_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }

  it1 = s21_1.find("the");
  it2 = std_1.find("the");
  EXPECT_EQ(*it1, *it2);
  --it1;
  --it2;
  EXPECT_EQ(*it1, *it2);
  it1--;
  it2--;
  EXPECT_EQ(*it1, *it2);

  it1 = s21_1.find("bebra");
  it2 = std_1.find("bebra");
  EXPECT_TRUE(it1 == s21_1.end());
  EXPECT_TRUE(it2 == std_1.end());

  bool b211 = s21_1.contains("root");
  bool b212 = s21_1.contains("bebra");
  EXPECT_TRUE(b211);
  EXPECT_FALSE(b212);

  s21_1.clear();
  std_1.clear();
  EXPECT_EQ(s21_1.size(), std_1.size());
  s21_1.swap(s21);
  EXPECT_FALSE(s21_1.empty());
  EXPECT_TRUE(s21.empty());
}

TEST(Set, insert_many) {
  s21::set<int> s1;
  s1.insert_many(97, 58, 8, 74, 30, 81, 41, 15, 8, 3, 93, 93, 22, 32, 84, 46,
                 96, 100, 91, 72, 60, 94, 25, 46, 89, 69, 45, 51, 88, 54, 27,
                 95, 12, 13, 91, 29, 15, 29, 56, 97);
  s21::set<int> s2{97, 58, 8,  74,  30, 81, 41, 15, 8,  3,  93, 93, 22, 32,
                   84, 46, 96, 100, 91, 72, 60, 94, 25, 46, 89, 69, 45, 51,
                   88, 54, 27, 95,  12, 13, 91, 29, 15, 29, 56, 97};
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s1 == s2);
}

TEST(Multiset, constructors) {
  s21::multiset<int> s1;
  s21::multiset<int> s2{1, 2, 3, 4, 5};
  s21::multiset<int> s3(s2);
  s21::multiset<int> s4(std::move(s3));
  s21::multiset<int> s5 = s4;
  s21::multiset<int> s6 = std::move(s5);

  std::multiset<int> std1;
  std::multiset<int> std2{1, 2, 3, 4, 5};
  std::multiset<int> std3(std2);
  std::multiset<int> std4(std::move(std3));
  std::multiset<int> std5 = std4;
  std::multiset<int> std6 = std::move(std5);

  EXPECT_EQ(s1.size(), std1.size());
  EXPECT_EQ(s2.size(), std2.size());
  EXPECT_EQ(s3.size(), std3.size());
  EXPECT_EQ(s4.size(), std4.size());
  EXPECT_EQ(s5.size(), std5.size());
  EXPECT_EQ(s6.size(), std6.size());
}

TEST(Multiset, operators) {
  s21::multiset<int> s1{1, 2, 3, 4, 5};
  s21::multiset<int> s2{1, 2, 3, 4, 5};
  s21::multiset<int> s3{6, 7, 8};
  s1 = s2;
  s1 = std::move(s3);
  s3 = s2;

  std::multiset<int> std1{1, 2, 3, 4, 5};
  std::multiset<int> std2{1, 2, 3, 4, 5};
  std::multiset<int> std3{6, 7, 8};
  std1 = std2;
  std1 = std::move(std3);
  std3 = std2;

  EXPECT_EQ(s1.size(), std1.size());
  EXPECT_EQ(s2.size(), std2.size());
  EXPECT_EQ(s3.size(), std3.size());

  bool b12 = s1 == s2;
  bool b13 = s1 == s3;
  bool b23 = s2 == s3;

  bool std_b12 = std1 == std2;
  bool std_b13 = std1 == std3;
  bool std_b23 = std2 == std3;

  EXPECT_EQ(b12, std_b12);
  EXPECT_EQ(b13, std_b13);
  EXPECT_EQ(b23, std_b23);

  b12 = s1 != s2;
  b13 = s1 != s3;
  b23 = s2 != s3;

  std_b12 = std1 != std2;
  std_b13 = std1 != std3;
  std_b23 = std2 != std3;

  EXPECT_EQ(b12, std_b12);
  EXPECT_EQ(b13, std_b13);
  EXPECT_EQ(b23, std_b23);
}

TEST(Multiset, test_txt) {
  std::ifstream file("test.txt");
  std::string str;
  s21::multiset<std::string> s21;
  std::multiset<std::string> std;
  const char *delimiters = " \n\t,.:;!?-()[]{}'\"";
  while (getline(file, str)) {
    char *word = strtok((char *)str.data(), delimiters);
    while (word != nullptr) {
      s21.insert(word);
      std.insert(word);
      word = strtok(nullptr, delimiters);
    }
  }
  EXPECT_EQ(s21.size(), std.size());
  auto it1 = s21.begin();
  auto it2 = std.begin();
  for (; it1 != s21.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(s21.count("the"), std.count("the"));
  EXPECT_EQ(s21.count("red"), std.count("red"));
  EXPECT_EQ(s21.count("black"), std.count("black"));
  EXPECT_EQ(s21.count("tree"), std.count("tree"));
  EXPECT_EQ(s21.count("fox"), std.count("fox"));

  s21::multiset<std::string> s21_1{"the", "red", "black", "tree", "fox"};
  std::multiset<std::string> std_1{"the", "red", "black", "tree", "fox"};

  s21_1.merge(s21);
  std_1.merge(std);
  EXPECT_EQ(s21.size(), std.size());
  EXPECT_EQ(s21_1.size(), std_1.size());
  it1 = s21_1.begin();
  it2 = std_1.begin();
  for (; it1 != s21_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }

  s21_1.insert("Lorem");
  s21_1.insert("ipsum");
  s21_1.insert("dolor");
  s21_1.insert("sit");
  s21_1.insert("amet");
  std_1.insert("Lorem");
  std_1.insert("ipsum");
  std_1.insert("dolor");
  std_1.insert("sit");
  std_1.insert("amet");

  EXPECT_EQ(s21_1.size(), std_1.size());
  it1 = s21_1.begin();
  it2 = std_1.begin();
  for (; it1 != s21_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }

  s21_1.erase(s21_1.find("Figure"));
  s21_1.erase(s21_1.find("right"));
  s21_1.erase(s21_1.find("left"));
  s21_1.erase(s21_1.find("color"));
  std_1.erase(std_1.find("Figure"));
  std_1.erase(std_1.find("right"));
  std_1.erase(std_1.find("left"));
  std_1.erase(std_1.find("color"));

  EXPECT_EQ(s21_1.size(), std_1.size());
  it1 = s21_1.begin();
  it2 = std_1.begin();
  for (; it1 != s21_1.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }

  it1 = s21_1.find("the");
  it2 = std_1.find("the");
  EXPECT_EQ(*it1, *it2);
  --it1;
  --it2;
  EXPECT_EQ(*it1, *it2);
  it1--;
  it2--;
  EXPECT_EQ(*it1, *it2);

  it1 = s21_1.find("bebra");
  it2 = std_1.find("bebra");
  EXPECT_TRUE(it1 == s21_1.end());
  EXPECT_TRUE(it2 == std_1.end());

  it1 = s21_1.lower_bound("up");
  it2 = std_1.lower_bound("up");
  EXPECT_EQ(*it1, *it2);
  it1 = s21_1.lower_bound("down");
  it2 = std_1.lower_bound("down");
  EXPECT_EQ(*it1, *it2);

  it1 = s21_1.upper_bound("up");
  it2 = std_1.upper_bound("up");
  EXPECT_EQ(*it1, *it2);
  it1 = s21_1.upper_bound("down");
  it2 = std_1.upper_bound("down");
  EXPECT_EQ(*it1, *it2);

  bool b211 = s21_1.contains("root");
  bool b212 = s21_1.contains("bebra");
  EXPECT_TRUE(b211);
  EXPECT_FALSE(b212);

  s21.insert("the");
  s21_1.clear();
  std_1.clear();
  EXPECT_EQ(s21_1.size(), std_1.size());
  s21_1.swap(s21);
  EXPECT_FALSE(s21_1.empty());
  EXPECT_TRUE(s21.empty());
}

TEST(Multiset, insert_many) {
  s21::multiset<int> s1;
  s1.insert_many(97, 58, 8, 74, 30, 81, 41, 15, 8, 3, 93, 93, 22, 32, 84, 46,
                 96, 100, 91, 72, 60, 94, 25, 46, 89, 69, 45, 51, 88, 54, 27,
                 95, 12, 13, 91, 29, 15, 29, 56, 97);
  s21::multiset<int> s2{97, 58, 8,  74,  30, 81, 41, 15, 8,  3,  93, 93, 22, 32,
                        84, 46, 96, 100, 91, 72, 60, 94, 25, 46, 89, 69, 45, 51,
                        88, 54, 27, 95,  12, 13, 91, 29, 15, 29, 56, 97};
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s1 == s2);
}

TEST(rbtree, operators) {
  s21::RBTree<double> rb1;
  s21::RBTree<double> rb2;
  rb1.Insert_Many(1.0, 2.0, 3.0, 4.0, 5.0);
  rb2.Insert_Many(1.0, 2.0, 3.0, 4.0, 5.0);
  rb1 = rb1;
  rb2 = rb1;
  EXPECT_TRUE(rb1 == rb2);
  rb2 = std::move(rb2);
  rb2 = std::move(rb1);
  EXPECT_FALSE(rb1 == rb2);
  EXPECT_EQ(rb1.Size(), 0);
  rb1.Insert_Many_Multi(1.0, 2.0, 3.0, 4.0, 5.0);
  rb2.Insert_Many_Multi(1.0, 2.0, 3.0, 4.0, 5.0);
  rb1.MergeMulti(rb2);
  EXPECT_EQ(rb2.Size(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
