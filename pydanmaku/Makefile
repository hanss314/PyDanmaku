# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11 -fPIC -I/usr/include/python3.7m \
	-Wall -Wextra -Wno-unused-parameter -O2 -g \
	-lGL -lGLU -lGLEW -lglfw -lfreeimage \
	-lasan -fsanitize=address,undefined

ODIR = obj

# File names
_OBJ = src/danmaku.o src/bullet.o src/renderer.o src/group.o \
	src/common/shader.o src/common/png.o src/common/trig.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ:src/%=%))

OBJECTS = _pydanmaku.so

obj/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CC_FLAGS)

# Main target
all: $(OBJ)
	$(CC) -o _pydanmaku.so $^ -shared $(CC_FLAGS)

test: $(OBJECTS) test.py pydanmaku.py
	LD_PRELOAD=/lib/libasan.so.5 python3 test.py

# Object files
%.so: $(OBJ)
	$(CC) -o _pydanmaku.so $^ -shared $(CC_FLAGS)

# To remove generated files
clean:
	rm -f *.so obj/**/*.o obj/*.o

.PHONY: all run clean
