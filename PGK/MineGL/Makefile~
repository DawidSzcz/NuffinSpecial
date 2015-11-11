LIBS= -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXi
FLAGS= -std=gnu++11 -O3  -Iglfw-3.0.3/include/GLFW -Iglfw-3.0.3/src -Iglew-1.9.0/include -Iglm-0.9.4.0
COMMON= -ImineCommon

all: clean shader.o controls.o program2.cpp
	g++ ${FLAGS} -o program program2.cpp shader.o controls.o  ${LIBS} ${COMMON} # dlaczego nie $<

#program2: 
#	g++ ${FLAGS} -o program2 program2.cpp shader.o controls.o  ${LIBS} ${COMMON} # dlaczego nie $<
shader.o:
	g++ ${FLAGS} mineCommon/shader.cpp -c ${LIBS}


controls.o:
	g++ ${FLAGS} mineCommon/controls.cpp -c ${LIBS}

clean:
	rm *.o
