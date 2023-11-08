CC = g++
CFLAGS = -std=c++20 -O2 -Wall -Wextra -I ../../engine/src -L ../../engine/build/lib
LDFLAGS = -lHopHopEngine -lvulkan -lglfw3 -ldl -lpthread

physics.bin: physics.cpp
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
