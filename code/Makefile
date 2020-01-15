CFLAGS = -Wall -Wextra -std=c++11 -g -O3
FILE=navigation.o asserv.o world.o
##
# Project Title
#
# @file
# @version 0.1

all: project

%.o: src/%.cpp
	g++ $(CFLAGS) -c $@ $<

code : world.o navigation.o asserv.o
	# g++ $(CFLAGS) -c src/world.cpp
	# g++ $(CFLAGS) -c src/navigation.cpp
	# g++ $(CFLAGS) -c src/asserv.cpp

project: code
	g++ $(CFLAGS) world.o navigation.o asserv.o src/main.cpp -o project

test: code
	g++ $(CFLAGS) $(FILE) tst/test.cpp -o test

clean:
	rm -f *.o project test

launch:
	./project
# end
