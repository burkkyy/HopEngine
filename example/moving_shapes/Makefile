CC = g++
CFLAGS = -std=c++20 -O2 -Wall -Wextra -I ../../engine/src -I ../../engine/ext_lib -L ../../engine/ext_lib/GLFW -L ../../engine/build/lib -L GLFW/
LDFLAGS = -lHopHopEngine -lvulkan -lglfw3 -ldl -lpthread

app.bin: app.cpp
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
