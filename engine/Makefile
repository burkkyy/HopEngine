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

# Source code from each module
SRC = $(foreach dir,$(_MODULE),$(wildcard $(dir)*.cpp))

# Object files from source code
OBJ = $(patsubst %.cpp,$(_ARCH_BUILD)/obj/%.o,$(notdir $(SRC)))
OBJ_HACK = $(SRC:.cpp=.o)	# A work around

# Graphics engine from object files
ENGINE = $(_ARCH_BUILD)/lib/libHopHopEngine.a
ENGINE_OUT = dist/$(notdir $(ENGINE))

# Compilie the shaders first
all: shader.frag.spv shader.vert.spv
CFLAGS += -DSHADER_VERT_DATA="\"$(dir $(ENGINE_OUT))shader.vert.spv\""
CFLAGS += -DSHADER_FRAG_DATA="\"$(shell cat $(dir $(ENGINE_OUT))shader.frag.spv)\""

$(info CFLAGS)
all: CFLAGS += -DNDEBUG
all: $(ENGINE)

$(ENGINE): $(OBJ) shader.frag.spv shader.vert.spv
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJ)
	@mkdir -p $(dir $(ENGINE_OUT))
	cp $(ENGINE) $(ENGINE_OUT)

# Prolly the most hacky, gross code ever
$(OBJ): $(OBJ_HACK)
$(OBJ_HACK): $(SRC)
	@mkdir -p $(dir $(patsubst %.o,$(_ARCH_BUILD)/obj/%.o,$(notdir $@)))
	$(CC) $(CFLAGS) -I $(dir $@) -c $(patsubst %.o,%.cpp,$@) -o $(patsubst %.o,$(_ARCH_BUILD)/obj/%.o,$(notdir $@)) $(LDFLAGS)

# Compilie shaders
shader.vert.spv: shaders/shader.vert
	@mkdir -p $(dir $(ENGINE_OUT))
	glslc $^ -o $(dir $(ENGINE_OUT))/$@

shader.frag.spv: shaders/shader.frag
	@mkdir -p $(dir $(ENGINE_OUT))
	glslc $^ -o $(dir $(ENGINE_OUT))/$@

.PHONY: clean dev
clean:
	-rm -rf $(_BUILD)

dev: $(ENGINE)
