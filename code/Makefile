CFLAGS = -Wall -Wextra -std=c++11 -g -O3
OBJS=navigation.o asserv.o affichage.o world.o
##
# Project Title
#
# @file
# @version 0.1

all: project

%.o: rasp/src/%.cpp
	g++ $(CFLAGS) -c $<

project: $(OBJS)
	g++ $(CFLAGS) $(OBJS) rasp/src/main.cpp -o project

test: $(OBJS) rasp/tst/test.cpp
	g++ $(CFLAGS) $(OBJS) rasp/tst/test.cpp -o test

clean:
	rm -f *.o project test massif.out.*

launch:
	./project
# end
