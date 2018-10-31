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


# Object files
%.so: $(SOURCES)
	$(CC) $(CC_FLAGS) $(SOURCES) -o $@





# To remove generated files
clean:
	rm -f *.so

.PHONY: all run clean
