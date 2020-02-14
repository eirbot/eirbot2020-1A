CFLAGS = -Wall -Wextra -std=c++11 -g -O3
FILE=navigation.o detection.o protocole.o asserv.o world.o affichage.o
#CC=/home/lucas/Documents/eirbot/robot_coupe_1A/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++
CC=g++
##
# Project Title
#
# @file
# @version 0.1

all: project

%.o: rasp/src/%.cpp
	$(CC) $(CFLAGS) -c $<

project: $(FILE) rasp/src/main.cpp
	$(CC) $(CFLAGS) $(FILE) rasp/src/main.cpp -o project

test: $(FILE) rasp/tst/test.cpp
	$(CC) $(CFLAGS) $(FILE) rasp/tst/test.cpp -o test

test_protocole: protocole.o
	$(CC) $(CFLAGS) protocole.o rasp/tst/test_protocole.cpp -o test_protocole

clean:
	rm -f *.o project test test_protocole

launch:
	./test
# end
