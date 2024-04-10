cc = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g

SRC = *.c
SRC_TEST = tests/*.c
OBJ = $(patsubst %.c, %.o, $(wildcard $(SRC)))
OBJ_TEST = $(patsubst %.c, %.o, $(wildcard $(SRC_TEST))) 

.PHONY: all clean test 
$(OBJ): s21_decimal.h
$(OBJ_TEST): tests/main.h
NAME:=$(shell uname -s)

ifeq ($(NAME), Linux)
	LDFLAGS= -lcheck -lsubunit -lm -lrt -lpthread
else ifeq ($(NAME),Darwin)
	LDFLAGS=-lcheck 
endif
all: clean s21_decimal.a

s21_decimal.a: $(OBJ)
		ar rcs s21_decimal.a $^
		ranlib s21_decimal.a
test: $(OBJ_TEST) s21_decimal.a
		$(cc) $^ $(LDFLAGS) -o $@ 
		./test
%.o: %.c
		@$(cc) $(CFLAGS) -c	$< -o $@
check:
		@cp ../materials/linters/.clang-format ./
		clang-format -n *.c *.h tests/*.c tests/*.h
		@rm -rf .clang-format
check2:
		@cp ../materials/linters/.clang-format ./
		clang-format -i *.c *.h tests/*.c tests/*.h
		@rm -rf .clang-format

clean:
		@rm -rf $(OBJ) $(OBJ_TEST)
		@rm -rf s21_decimal.a test test.dSYM
		@rm -rf a.out a.out* 
		@rm -rf *.info *.gcno *.gcda report
		@rm -rf tests/*.info tests/*.gcno tests/*.gcda

gcov_report: s21_decimal.a 
		$(cc) $(CFLAGS) --coverage $(SRC_TEST) $(SRC) $(LDFLAGS) -o test
		./test
		mkdir report
		lcov -t "test" -o test.info -c -d . 
		genhtml -o report test.info
		open report/index.html
		rm -rf *.gcda *.gcno *.out

#add_coverage:
#	$(eval CFLAGS += --coverage)

rebuild: clean test
