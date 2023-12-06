CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -I ../engine/src -L ../engine/build/lib
LDFLAGS = -lHopHopEngine -lvulkan -lglfw3 -ldl -lpthread

test.bin: test.cpp
	$(CC) $(CFLAGS) -DNDEBUG $^ $(LDFLAGS) -o $@

