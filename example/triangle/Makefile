CC = g++
CFLAGS = -std=c++20 -O2 -Wall -Wextra -I ../../engine/src -L ../../engine/build/lib
LDFLAGS = -lHopHopEngine -lvulkan -lglfw3 -ldl -lpthread

a.bin: triangle.cpp
	$(CC) $(CFLAGS) triangle.cpp $(LDFLAGS) -o $@
