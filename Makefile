include buildenv/config.mk

# NOTE: The following variables must be defined in a seperate config.mk file:
# 	$(ARCH) 	- The target system ex. linux
# 	$(OUT) 		- The target file ex. $(_ARCH_BUILD)/bin/app.exe
# 	$(CC) 		- The compilier to be used
# 	$(CFLAGS) 	- Compilier flags
# 	$(LDFLAGS) 	- Linker flags

# Project root dir 
_ROOT = .

# Where all built files go
_BUILD = $(_ROOT)/build

# Where all built files for target system go
_ARCH_BUILD = $(_BUILD)/$(ARCH)

# The root folder for project source code and header files
_SRC = $(_ROOT)/src

# Each module that holds all the source files
_MODULE := $(wildcard $(_SRC)/*/)
#$(info _MODULE: $(_MODULE))

# Source code from each module
SRC = $(foreach dir,$(_MODULE),$(wildcard $(dir)*.cpp))
#$(info SRC: $(SRC))

# Object files from source code
OBJ = $(patsubst %.cpp,$(_ARCH_BUILD)/obj/%.o,$(notdir $(SRC)))
OBJ_HACK = $(SRC:.cpp=.o)	# A work around

#$(info OBJ: $(OBJ))

# Graphics engine from object files
ENGINE = $(_ARCH_BUILD)/lib/libHopHopEngine.a

all: $(OUT)

$(OUT): $(_SRC)/app.cpp $(ENGINE) shader.frag.spv shader.vert.spv
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(ENGINE) -o $@ $(LDFLAGS)

$(ENGINE): $(OBJ)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJ)

# Prolly the most hacky, gross code ever
$(OBJ): $(OBJ_HACK)
$(OBJ_HACK): $(SRC)
	@mkdir -p $(dir $(patsubst %.o,$(_ARCH_BUILD)/obj/%.o,$(notdir $@)))
	$(CC) $(CFLAGS) -I $(dir $@) -c $(patsubst %.o,%.cpp,$@) -o $(patsubst %.o,$(_ARCH_BUILD)/obj/%.o,$(notdir $@)) $(LDFLAGS)

# Compilie shaders
shader.vert.spv: shaders/shader.vert
	glslc $^ -o $(dir $(OUT))/$@

shader.frag.spv: shaders/shader.frag	
	glslc $^ -o $(dir $(OUT))/$@

.PHONY: clean
clean:
	-rm -rf $(_BUILD)
