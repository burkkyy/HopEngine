include buildenv/config.mk

# NOTE: The following variables must be defined in a seperate config.mk file:
# 	$(CC) 		- The compilier to be used
# 	$(CFLAGS) 	- Compilier flags
# 	$(LDFLAGS) 	- Linker flags
 
_ROOT = .
_BUILD = $(_ROOT)/build
_SRC = $(_ROOT)/src
_MODULE := $(wildcard $(_SRC)/*/)

SRC = $(foreach dir,$(_MODULE),$(wildcard $(dir)*.cpp))

OBJ = $(patsubst %.cpp,$(_BUILD)/obj/%.o,$(notdir $(SRC)))
OBJ_HACK = $(SRC:.cpp=.o)	# A work around

ENGINE = $(_BUILD)/lib/libHopHopEngine.a

all: CFLAGS += -DNDEBUG
all: $(ENGINE)

$(ENGINE): $(OBJ) shaders
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $(OBJ)

# Prolly the most hacky, gross code ever
$(OBJ): $(OBJ_HACK)
$(OBJ_HACK): $(SRC)
	@mkdir -p $(dir $(patsubst %.o,$(_BUILD)/obj/%.o,$(notdir $@)))
	$(CC) $(CFLAGS) -I $(dir $@) -c $(patsubst %.o,%.cpp,$@) -o $(patsubst %.o,$(_BUILD)/obj/%.o,$(notdir $@)) $(LDFLAGS)

shaders: $(_BUILD)/shaders/shader.vert.spv $(_BUILD)/shaders/shader.frag.spv

# Compilie shaders
$(_BUILD)/shaders/shader.vert.spv: shaders/shader.vert
	@mkdir -p $(dir $@)
	glslc $^ -o $@

$(_BUILD)/shaders/shader.frag.spv: shaders/shader.frag
	@mkdir -p $(dir $@)
	glslc $^ -o $@

.PHONY: clean dev
clean:
	-rm -rf $(_BUILD)

dev: $(ENGINE)
