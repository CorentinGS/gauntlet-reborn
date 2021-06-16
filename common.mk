OUT = bin

SEARCHPATH += src
vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += defs.h structs.h

_OBJS += camera.o
_OBJS += draw.o
_OBJS += entities.o
_OBJS += init.o input.o io.o
_OBJS += main.o map.o
_OBJS += pizza.o door.o menu.o chest.o potion.o key.o spawner.o player.o 
_OBJS += sound.o stage.o
_OBJS += textures.o text.o
_OBJS += util.o

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
$(OUT)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<
	
# cleaning everything that can be automatically recreated with "make".
clean:
	$(RM) -rf $(OUT) $(PROG)
