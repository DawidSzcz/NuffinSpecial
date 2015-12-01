LIBS= -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lIL -lILU
FLAGS= -std=gnu++11 -O3  -I../../Libs/devil-1.7.8/include -I../../Libs/glfw-3.0.3/include -I../../Libs/glew-1.9.0/include -I../../Libs/glm-0.9.4.0 -ImineCommon

all: clean Zad1 Zad4 Zad5 picture 

train: clean
	g++ ${FLAGS} -o train train.cpp ${LIBS} ${COMMON}

Zad5: shader.o Zad3utils.o
	g++ ${FLAGS} -o Zad3/Zad3 Zad3/Zad3.cpp shader.o Zad3utils.o ${LIBS} ${COMMON}

Zad1: shader.o controls.o 
	g++ ${FLAGS} -o Zad1/Zad1 Zad1/Zad1.cpp shader.o controls.o  ${LIBS} ${COMMON} # dlaczego nie $<

simple: textfile.o
	g++ ${FLAGS} -o SimpleTexture/simple SimpleTexture/simple.cpp textfile.o ${LIBS} ${COMMON} # dlaczego nie $<

picture: 
	g++ ${FLAGS} -o Zad2/picture Zad2/picture.cpp ${LIBS} ${COMMON} # dlaczego nie $<

Zad4: shader.o controls2.o utils.o
	g++ ${FLAGS} -o Zad2/Zad2 Zad2/Zad2.cpp shader.o controls2.o utils.o ${LIBS} ${COMMON} # dlaczego nie $<

shader.o:
	g++ ${FLAGS} mineCommon/shader.cpp -c ${LIBS}

utils.o:
	g++ ${FLAGS} mineCommon/utils.cpp -c ${LIBS}

Zad3utils.o:
	g++ ${FLAGS} mineCommon/Zad3utils.cpp -c ${LIBS}

textfile.o:
	g++ ${FLAGS} SimpleTexture/textfile.cpp -c ${LIBS}


controls.o:
	g++ ${FLAGS} mineCommon/controls.cpp -c ${LIBS}

controls2.o:
	g++ ${FLAGS} mineCommon/controls2.cpp -c ${LIBS}

clean:
	touch sth.o && rm *.o 
