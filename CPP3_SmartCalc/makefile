CC= g++
CXXFLAGS= -std=c++17 -Wall -Werror -Wextra -pedantic
GCOV= --coverage
OUTNAME= Calck2.app

#.PHONY гарантирует, что make не будет пытаться сравнивать временные метки файлов и выполнять эту цель,
# если файл с таким именем существует.

.PHONY: build
install: 
	@mkdir -p build && cd build && cmake .. && make && cd ..
	@read -p "Запустить программу? [y/N]: " answer; \
    if [ "$$answer" = "y" ]; then \
       open ./build/$(OUTNAME); \
    fi

.PHONY: tests
tests: clean
	$(CC) -c ./Model/Calck.cc tests.cc
	$(CC) tests.o Calck.o -lgtest -o test

.PHONY: clean
clean:
	rm -rf build ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./gcov_report *.info ./*.info tests

.PHONY: uninstall
uninstall:
	@rm -rf build*

.PHONY: dist
dist:
	@tar -cf calc.tar *.cc *.h Makefile build

.PHONY: dvi
dvi:
	open ../materials/doc.tex
	# pdflatex ../materials/doc.tex