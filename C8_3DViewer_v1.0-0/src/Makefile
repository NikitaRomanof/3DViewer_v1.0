.PHONY: all clean check tests gcov_report dvi install uninstall dist
CC=gcc
FILES= readObjFile.c\
	   affineTransformations.c\
	   s21_matrix.c\

LDFLAGS= -Wall -Wextra -Werror -std=c11 -g
OS := $(shell uname -s)
LCHECK= `pkg-config --libs check`

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all

all: clean install tests

dist:
	tar -cvzf dist/dist.tgz *.cpp *.c *.h *.ui

dvi:
	open files/manual.html

install:
	tar -xf dist/viewer.tgz -C dist/
uninstall:
	rm -rf dist/viewer.app
tests:
	tar xvf files/test.tar.xz
ifeq ($(OS), Darwin)
	$(CC) $(LDFLAGS) tests.c $(FILES) -o tests $(LCHECK)
else
	$(CC) $(LDFLAGS) tests.c $(FILES) -o tests -lcheck -lsubunit -lrt -lpthread -lm
endif
	./tests

clean:
	rm -rf tests *.a *.o *.cfg *.gcda *.gcno *.html *.info report test.obj tests.dSYM

check: clean tests
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./tests
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./tests
endif

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) --coverage $(FILES) tests.c -o tests $(LCHECK)
	tar xvf files/test.tar.xz
	./tests
	rm test.obj
	lcov -t "tests" -c -d . -o tests.info
	genhtml tests.info -o report
	open -a "Google Chrome" report/index.html
else
	$(CC) -fprofile-arcs -ftest-coverage $(FILES) tests.c -o tests -lcheck -lsubunit -lrt -lpthread -lm -g
	tar xvf files/test.tar.xz
	./tests
	rm test.obj
	lcov -t "tests" -c -d . -o tests.info
	genhtml tests.info -o report
	xdg-open report/index.html
endif
