CC = g++
CFLAGS = -std=c++20 -O2 -Wall -Wextra -I ../../engine/src -L ../../engine/build/lib -L GLFW/
LDFLAGS = -lHopHopEngine -lvulkan -lpthread -lm -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl

app.bin: app.cpp
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
