CC=g++ -std=c++17 -Wall -Werror -Wextra
CHECKFLAGS=-lgtest
OS = $(shell uname)

all: clean s21_matrix_oop.a test gcov_report

s21_matrix_oop.a:
	$(CC) -c s21_matrix_oop.cpp -o s21_matrix_oop.o
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm *.o

test: clean 
	$(CC) -c s21_matrix_oop.cpp test.cpp 
	$(CC) test.o s21_matrix_oop.o $(CHECKFLAGS) -o matrix_test
	./matrix_test

stylefix: 
	clang-format -style="{BasedOnStyle: Google}" -i *.cpp *.h
check:
	clang-format -style="{BasedOnStyle: Google}" -n *.cpp *.h

leaks:
	$(CC) -c s21_matrix_oop.cpp test.cpp 
	$(CC)  test.o s21_matrix_oop.o $(CHECKFLAGS) -o matrix_test
ifeq ($(OS), Linux)
	valgrind --leak-check=yes ./matrix_test
else
	leaks -atExit -- ./matrix_test
endif

gcov_report: clean
	$(CC) -c test.cpp -o test.o
	$(CC) --coverage test.o s21_matrix_oop.cpp -o test $(CHECKFLAGS)
	./test
	lcov -t "s21_matrix_oop.a" -o s21_matrix_oop.info -c -d . --no-external
	genhtml -o report s21_matrix_oop.info
	rm *.info test *.gcda *.gcno *.o
	open report/index.html

clean:
	rm -rf *.info test *.gcda *.gcno *.o report matrix_test *.a

