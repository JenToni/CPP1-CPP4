SHELL=/bin/sh
OS=$(shell uname)
CXX=g++
STD=-std=c++17
OPTIMIZE=-01

APP = viewer.app

SRC_DIRECTORY_MODEL=./Model
SRC_DIRECTORY_VIEW=./View
SRC_DIRECTORY_CONTROLLER=./Controller
SRC_DIRECTORY_OTHER=./
SRC_TEST_DIRECTORY=./tests

SRC=$(SRC_DIRECTORY)/*.cc
SRC_OBJECT=$(SRC_DIRECTORY_MODEL)/object.cc
SRC_TEST=$(SRC_TEST_DIRECTORY)/*.cc
PRO_FILE=3DViewer.pro


LG_TEST= -lgtest
UBUNTU_FLAG= -pthread

EXE_TEST=test

all: uninstall clean install dist tests dvi 

install:
	@rm -rf build
	@mkdir -p build
	@qmake6 View/3DViewer.pro -o build
	$(MAKE) -C build
	
uninstall:
	@rm -rf ./build

tests: clean
	$(CXX) -Wall -Wextra -Werror -o $(EXE_TEST) $(STD) $(SRC_OBJECT) $(SRC_TEST) $(TEST_FLAGS) $(LGMOCK_FLAG) $(LG_TEST) $(UBUNTU_FLAG) && ./$(EXE_TEST)

dvi:
ifeq ($(OS), Linux) 
	@-doxygen Doxyfile
	@firefox html/index.html
else ifeq ($(OS), Darwin) 
	@-doxygen Doxyfile
	@firefox html/index.html
else
	@-Doxygen.exe Doxyfile
	@-firefox html/index.html
endif


dist: clean
	@tar -cf 3DViewer_v2.0.tar command.* controller/ Doxyfile Makefile Model/ tests/ View/


valgrind: clean tests
	valgrind ./test --tool=memcheck --leak-check=full --show-leak-kinds=all -s --show-reachable=yes

stylefix: 
	@clang-format -style="{BasedOnStyle: Google}" -i *.cc *.h controller/*.* Model/*.* View/*.cc View/*.h

stylecheck:
	@clang-format -style="{BasedOnStyle: Google}" -n *.cc *.h controller/*.* Model/*.* View/*.cc View/*.h

cppcheck:
	cppcheck -$(STD) --language=c++ -q --enable=all --inconclusive $(SRC)

clean:
	@rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./gcov_report *.info ./*.info  report test *.tar *.user .qmake.stash html latex *.tar test

