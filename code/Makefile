CFLAGS = -Wall -Wextra -std=c++11 -g -O3
FILE=navigation.o asserv.o world.o affichage.o
##
# Project Title
#
# @file
# @version 0.1

all: project

%.o: rasp/src/%.cpp
	g++ $(CFLAGS) -c $<

project: $(FILE)
	g++ $(CFLAGS) $(FILE) rasp/src/main.cpp -o project

test: $(FILE)
	g++ $(CFLAGS) $(FILE) rasp/tst/test.cpp -o test

clean:
	rm -f *.o project test

launch:
	./test
# end
