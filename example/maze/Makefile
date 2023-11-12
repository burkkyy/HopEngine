CC = g++
CFLAGS = -std=c++20 -O2 -I ../../engine/src -L ../../engine/build/lib -L GLFW
LDFLAGS = -lHopHopEngine -lvulkan -lpthread -lm -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
NAME = maze.bin
maze: main.cpp 
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(NAME)
	
.PHONY:clean 

clean:
	rm $(NAME)