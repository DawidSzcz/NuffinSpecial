CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Wformat -Wfloat-equal -W `pkg-config --cflags glfw3 glew`
LDLIBS = `pkg-config --static --libs glfw3 glew` 
TARGETS = arkanoid
 
all: $(TARGETS)

arkanoid:	common/shader.o \
			common/texture.o \
			common/text2D.o \
			IShader.o \
			TranslationVertexShader.o \
			IDrawable.o \
			CollisionPrimitive.o \
			ICollidable.o \
			IObservable.o \
			DrawableCircle.o \
			Ball.o \
			DrawableRectangle.o \
			PersistentBrick.o \
			Brick.o \
			DrawableCircularSegment.o \
			Paddle.o \
			DrawableHexagonExterior.o \
			Borders.o \
			DrawableHexagon.o \
			Background.o \
			EscapeLine.o \
			DrawingManager.o \
			MotionManager.o \
			CollisionManager.o \
			Game.o

clean:
	rm -f *.o ; rm -f common/*.o

distclean: clean
	rm -f $(TARGETS)

real: distclean all