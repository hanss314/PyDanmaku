# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11 -shared -fPIC -I/usr/include/python3.7m \
	-Wall -Wextra -Wno-unused-parameter -O2 -g \
	-lGL -lGLU -lGLEW -lglfw -lfreeimage \
	-lasan -fsanitize=address,undefined

# File names
SOURCES = src/danmaku.cpp src/bullet.cpp src/renderer.cpp src/common/shader.cpp src/common/png.cpp src/common/trig.cpp
OBJECTS = _pydanmaku.so

# Main target
all: $(OBJECTS)

# Object files
%.so: $(SOURCES)
	$(CC) $(CC_FLAGS) $(SOURCES) -o $@



# To remove generated files
clean:
	rm -f *.so

.PHONY: all run clean
