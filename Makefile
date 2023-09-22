CC = g++ -std=c++17
CFLAGS = -O2 -Wall
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR = src/

# MODULES := $(wildcard $(SRC_DIR/*/))
MODULES = Window/

source_files = $(foreach dir,$(MODULES),$(wildcard $(dir)/*.cpp))
object_files = $(source_files:.cpp=.o) 

libgfxEngine.a:
	ar rcs $@ $^

$(object_files): $(source_files)
	echo $@ $^
# @mkdir -l $(dir $@)
# $(CC) $(CFLAGS) $(LDFLAGS)

.PHONY: clean
