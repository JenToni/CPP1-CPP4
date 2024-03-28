SHELL = /bin/bash
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -g -O2
LIBS = -lgtest -lgmock -pthread
COVFLAGS = --coverage
EXE = test
MAIN = test.cc
OBJ = $(MAIN:.cpp=.o)
UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Linux)
OPEN = firefox
endif
ifeq ($(UNAME_S),Darwin)
OPEN = open
endif

all: clean test

test:
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(EXE) $(LIBS)
	./$(EXE)

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(COVFLAGS) $(MAIN) -o $(EXE) $(LIBS)
	./$(EXE)
	lcov -t "result" -o result.info -c -d . --no-external 
	genhtml -o result result.info
	$(OPEN) result/index.html

clean:
	rm -rf *.o *.a $(EXE) *.gcda *.gcno *.gcov gcovr*html gcov*css result result.info

style: 
	@cp ../materials/linters/.clang-format ./
	clang-format -i containers/*.h test.cc
	@rm .clang-format

check:
	@cp ../materials/linters/.clang-format ./
	clang-format -n containers/*.h test.cc
	@rm .clang-format

valgrind: test
	valgrind --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(EXE)