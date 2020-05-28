CFLAGS = -std=c++11 -g -O3 --coverage
FILE=world.o navigation.o detection.o actionneur.o protocole.o asserv.o robot.o affichage.o ecocup_pdv.o ecocup.o
TEST_FILE=test_protocole.o test_asserv.o test_actionneur.o test_detection.o test_navigation.o
ifdef cross
	CC=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++
else
	CC=g++
endif

.PHONY: doc clean coverage
##
# Project Title
#
# @file Makefile
# @brief Permet de complier le projet
# @author SD & Ptit Lu

all: project doc coverage

# Permet de compiler les sources
%.o: rasp/*/*/%.cpp
	$(CC) $(CFLAGS) -c $<
%.o: rasp/*/%.cpp
	$(CC) $(CFLAGS) -c $<


project: $(FILE) rasp/src/main.cpp
	$(CC) $(CFLAGS) $(FILE)  rasp/src/main.cpp -o project

test: $(FILE) $(TEST_FILE) rasp/tst/test.cpp
	$(CC) $(CFLAGS) $(FILE) $(TEST_FILE) rasp/tst/test.cpp -pg -o test

coverage: $(FILE) $(TEST_FILE) rasp/tst/test.cpp
	$(CC) $(CFLAGS) $(FILE) $(TEST_FILE) rasp/tst/test.cpp -O0 -pg -o test
	./test
	mv *.gc* coverage/
	lcov  --directory coverage/ -c -o coverage/rapport.info
	lcov --remove coverage/rapport.info '/usr/include/*'
	genhtml -o coverage/ -t "couverture de code des tests" coverage/rapport.info
	firefox coverage/src/index.html &

clean:
	rm -f *.o project test test_protocole *.gcno *.gcov *.gcda *.out
	rm -r -f doc/html
	rm -f -r coverage/* && touch coverage/.gitkeep

doc:
	doxygen Doxyfile
	firefox doc/html/globals.html &

upload:
	scp test_protocole pi@eirboat:~
	ssh pi@eirboat ./test_protocole

final:
	scp projet pi@192.168.43.32:~
	ssh pi@192.168.43.32  ./project
# end
