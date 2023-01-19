CC := gcc
FLAGS := -Wall -Wextra -Werror -lm -std=c11

DEBUG_FLAGS := -g -fsanitize=address

SOURCE_PATH := backend
CHECK_FLAGS := -lcheck -lsubunit -coverage -pthread -lrt

all: clean lib_calc.a

test:
	$(CC) $(SOURCE_PATH)/*.c tests/*.c $(FLAGS) $(CHECK_FLAGS)
	./a.out
	
lib_calc.a:
	$(CC) $(FLAGS) -c $(SOURCE_PATH)/*.c
	ar rc lib_calc.a *.o
	ranlib lib_calc.a
	mv *.o *.a build/
	
rebuild:
	all

install: uninstall
	@mkdir build
	@cp -r gifs build
	@make && bash cm_install.sh
	@./build/SmartCalcv1.0

uninstall: clean
	rm -rf build

dvi:
	open ../docs/html/index.html

dist: clean
	mkdir Archive_SmartCalc_v1.0
	cp Makefile backend/*.c backend/include/*.h gui/*.cpp gui/*.h gui/include/*.h  gui/*.ui Archive_SmartCalc_v1.0/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/	


gcov_report: clean
	$(CC) $(FLAGS) $(SOURCE_PATH)/*.c tests/*.c -lm $(CHECK_FLAGS) -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html
	
.PHONY: clean

clean:
	rm -rf *.o *.html *.gcda *.gcno *.a *.css *.gcov *.info *.tgz
	rm -rf *.out *.cfg *.txt gcov_main test_build gcov_report Archive*
