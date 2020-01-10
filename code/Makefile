CFLAGS = -Wall -Wextra -std=c++11 -g
##
# Project Title
#
# @file
# @version 0.1

all: project

code :
	g++ $(CFLAGS) -c src/navigation.cpp

project: code
	g++ $(CFLAGS) navigation.o src/main.cpp -o project

test: code
	g++ $(CFLAGS) navigation.o tst/test.cpp -o test

clean:
	rm -f *.o project test

launch:
	./project
# end
