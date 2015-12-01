CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Wformat -Wfloat-equal -W `pkg-config --cflags glfw3 glew`
LDLIBS = `pkg-config --static --libs glfw3 glew` 
TARGETS = memory
 
all: $(TARGETS)

memory: common/shader.o common/texture.o common/text2D.o Card.o CardsDeck.o IGameState.o Game.o

clean:
	rm -f *.o ; rm -f common/*.o

distclean: clean
	rm -f $(TARGETS)
