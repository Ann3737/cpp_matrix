# all, clean, test, s21_matrix_oop.a
CPPFLAGS = g++ -Wall -Werror -Wextra -std=c++20
GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage -lgtest -fprofile-update=atomic
SRC = s21_matrix_oop.cpp tests/s21_matrix_tests.cpp

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
OPEN = open
endif

ifeq ($(UNAME), Linux)
OPEN = xdg-open
GCOV_FLAGS += -lsubunit -lm
endif

all: clean test s21_matrix_oop.a

clean:
	rm -rf gcov
	rm -f tests/test
	rm -f *.gcda *.gcno
	rm -f *.a *.o
	cd tests && rm -f *.gcda *.gcno

test: clean
	$(CPPFLAGS) $(SRC) $(GCOV_FLAGS) -o tests/test
	cd tests && ./test

s21_matrix_oop.a: clean
	$(CPPFLAGS) -c s21_matrix_oop.cpp
	ar -crs s21_matrix_oop.a s21_matrix_oop.o

gcov_report: clean
	mkdir -p gcov
	$(CPPFLAGS) $(SRC) $(GCOV_FLAGS) -o gcov/gcov_test
	cd gcov && ./gcov_test
	gcovr --html-details -o gcov/report.html --exclude-unreachable-branches --exclude-throw-branches
	$(OPEN) gcov/report.html

clang_format: clean
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.cpp *.h
	clang-format -i tests/*.cpp
	rm -f .clang-format

check_format:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp *.h
	clang-format -n tests/*.cpp
	rm -f .clang-format