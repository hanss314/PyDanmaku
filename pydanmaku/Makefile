# Declaration of variables
CC = g++
CC_FLAGS = -shared -fPIC -I/usr/include/python3.7m \
	-Wall -Wextra -Wno-unused-parameter -O2 -g \
	-lGL -lGLU -lGLEW -lglfw -lfreeimage \
#	-static-libasan -fsanitize=address,undefined

# File names
SOURCES = danmaku.cpp bullet.cpp renderer.cpp common/shader.cpp common/png.cpp common/trig.cpp
OBJECTS = danmaku.so

# Main target
all: $(OBJECTS)

# Object files
%.so: $(SOURCES)
	$(CC) $(CC_FLAGS) $(SOURCES) -o $@



# To remove generated files
clean:
	rm -f *.so

.PHONY: all run clean
