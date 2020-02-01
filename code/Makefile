CFLAGS = -Wall -Wextra -std=c++11 -g -O3
FILE=navigation.o detection.o asserv.o world.o affichage.o protocole.o
##
# Project Title
#
# @file
# @version 0.1

all: project

%.o: rasp/src/%.cpp
	g++ $(CFLAGS) -c $<

project: $(FILE) rasp/src/main.cpp
	g++ $(CFLAGS) $(FILE) rasp/src/main.cpp -o project

test: $(FILE) rasp/tst/test.cpp
	g++ $(CFLAGS) $(FILE) rasp/tst/test.cpp -o test

test_protocole: protocole.o
	g++ $(CFLAGS) protocole.o rasp/tst/test_protocole.cpp -o test_protocole

clean:
	rm -f *.o project test test_protocole

launch:
	./test
# end
