CC = g++
CFLAGS = -I ../../engine/src -L ../../engine/dist
LDFLAGS = -lHopHopEngine -lglfw -lvulkan

triangle.bin: triangle.cpp
	$(CC) $(CFLAGS) triangle.cpp $(LDFLAGS) -o $@
