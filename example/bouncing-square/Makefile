# Release build
app.bin: $(_SRC)/app.cpp $(ENGINE) shader.frag.spv shader.vert.spv
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -NDEBUG $< $(ENGINE) -o $@ $(LDFLAGS)
