CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Wformat -Wfloat-equal -W `pkg-config --cflags glfw3 glew`
LDLIBS = `pkg-config --static --libs glfw3 glew` 
TARGETS = babelki
 
all: $(TARGETS)

babelki:	common/shader.o \
			CollisionPrimitive.o \
			MonochromaticSphere.o


clean:
	rm -f *.o ; rm -f common/*.o

distclean: clean
	rm -f $(TARGETS)

real: distclean all