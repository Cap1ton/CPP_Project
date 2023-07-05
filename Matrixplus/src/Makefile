CC = gcc
FLAGS = -lstdc++ -std=c++17 -Wall -Werror -Wextra 
FUNC = s21_matrix.cc s21_const_dest.cc s21_overload.cc
FUNC_O = s21_matrix.o s21_const_dest.o s21_overload.o
TEST = s21_test.cc

all: test 

clean:
	rm -rf *.o report *.info *.gcda *.gcno *.gcov *.gch *.out *.a *.txt test main

test: clean s21_matrix_oop.a
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST) s21_matrix_oop.a -lgtest -o test
	./test

s21_matrix_oop.a:
	gcc $(FLAGS) -c $(FUNC)
	ar rc s21_matrix_oop.a $(FUNC_O)
	ranlib s21_matrix_oop.a 

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cc
	clang-format -n *.cc
	clang-format -i *.h

main: clean
	$(CC) $(FLAGS) $@.cc $(FUNC)
	./a.out

valgrind:
	valgrind --leak-check=full -s --track-origins=yes --log-file=valgrind-out.txt ./test

.PHONY: s21_matrix_oop.a test
