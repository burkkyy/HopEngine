CC = g++
CFLAGS = -std=c++20 -O2 -Wall -Wextra -I ../../engine/src -I ../../engine/ext_lib -L ../../engine/ext_lib/GLFW -L ../../engine/build/lib -L GLFW/
LDFLAGS = -lHopHopEngine -lvulkan -lpthread -lm -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl


app.bin: app.cpp ../../engine/build/lib/libHopHopEngine.a ../../engine/src/hop.hpp
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: clean

clean:
	rm *.bin