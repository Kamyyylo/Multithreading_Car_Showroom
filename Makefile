all:
	g++ -Wall -g -std=c++11 main.cpp -Werror -o projekt  -lncurses -pthread
clean:
	rm -f projekt
