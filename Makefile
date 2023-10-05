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

# Graphics engine from object files
ENGINE = $(_ARCH_BUILD)/lib/libHopHopEngine.a

all: $(OUT) $(ENGINE) $(OBJ) $(SRC)

$(OUT): $(_SRC)/app.cpp $(ENGINE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(ENGINE) -o $@ $(LDFLAGS)

$(ENGINE): $(OBJ) $(SRC)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(OBJ): $(SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	-rm -rf $(_BUILD)
