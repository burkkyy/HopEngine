CC = g++ -std=c++17
CFLAGS = -O2 -Wall -I src/Utilities
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR = src

MODULES := $(wildcard $(SRC_DIR)/*/)

source_files = $(foreach dir,$(MODULES),$(wildcard $(dir)/*.cpp))
object_files = $(source_files:.cpp=.o)

$(object_files): $(source_files)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(source_files) -o $@
