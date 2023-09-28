CC = g++ -std=c++17
CFLAGS = -O2 -Wall -I src/Utilities
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR = src
BUILD_DIR = build

MODULES := $(wildcard $(SRC_DIR)/*/)

source_files = $(foreach dir,$(MODULES),$(wildcard $(dir)*.cpp))
object_files =  $(patsubst %.cpp,$(BUILD_DIR)/obj/%.o,$(notdir $(source_files)))

ENGINE_LIB = $(BUILD_DIR)/libHopHopEngine.a

app: app.cpp $(ENGINE_LIB)
	$(CC) $< -L $(BUILD_DIR)/ -lHopHopEngine -o $@

$(ENGINE_LIB): $(object_files)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(object_files): $(source_files)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(source_files) -o $@

.PHONY: run clean
run: app
	./app

clean: 
	rm -rf build/
