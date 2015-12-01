CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Wformat -Wfloat-equal -W `pkg-config --cflags glfw3 glew assimp`
LDLIBS = -lSOIL `pkg-config --static --libs glfw3 glew assimp`
TARGETS = models
 
all: $(TARGETS)

models:	common/shader.o \
	Model.o \
	Scene.o \
	Camera.o \
	ShaderSwitcher.o \
	Renderer.o

clean:
	rm -f *.o ; rm -f common/*.o

distclean: clean
	rm -f $(TARGETS)

real: distclean all
