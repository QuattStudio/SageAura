CC = gcc
NAME = SageAura

# Flags
CFLAGS = -Iexternal/include \
         -Iinclude \
         -Isrc \
         -Iinclude/internals \
         -Iinclude/renderer \
         -Iinclude/core
         
DEFINES = -DSA_BUILD -DGLFW_STATIC

# Source files - recurse into subfolders automatically
SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
SRC += external/src/glad.c

LDFLAGS = -Lexternal/libs
LIBS = -lglfw3 -lopengl32 -lgdi32 -limm32

# ─────────────────────────────────────────
# Detect OS
# ─────────────────────────────────────────
ifeq ($(OS), Windows_NT)
    TARGET = $(NAME).dll
    SHARED = -shared
    IMPLIB = -Wl,--out-implib,lib$(NAME).a
#     CLEAR = cls
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME), Darwin)
        TARGET = lib$(NAME).dylib
        SHARED = -dynamiclib
        IMPLIB =
        LIBS = -lglfw -framework OpenGL
    else
        TARGET = lib$(NAME).so
        SHARED = -shared -fPIC
        IMPLIB =
        LIBS = -lglfw -lGL -lm -ldl
    endif
    CLEAR = clear
endif

# ─────────────────────────────────────────
# Build
# ─────────────────────────────────────────
all: clear $(TARGET)
	@echo ""
	@echo "Build SUCCESS ✅  →  $(TARGET)"

$(TARGET): $(SRC)
	$(CC) $(SHARED) $(DEFINES) $(SRC) \
		$(LDFLAGS) $(CFLAGS) \
		-o $(TARGET) \
		$(LIBS) \
		$(IMPLIB)

clear:
	@$(CLEAR)

clean:
	rm -f $(NAME).dll lib$(NAME).a lib$(NAME).so lib$(NAME).dylib

run:
	@cd game && build.bat || sh game/build.sh

.PHONY: all clean clear run