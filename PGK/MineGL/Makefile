LIBS= -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lIL -ltiff -lpng12 -llcms -ljasper -ljpeg -lIlmImf -lz -lImath -lHalf -lIex -lIlmThread 
FLAGS= -std=gnu++11 -O3 -ImineCommon -Iinclude -Llib

all: clean Zad1 Zad2 Zad3 picture 

train: clean
	g++ ${FLAGS} -o train train.cpp ${LIBS} ${COMMON}


Zad1: shader controls
	g++ ${FLAGS} -o Zad1/Zad1 Zad1/Zad1.cpp shader.o controls.o  ${LIBS} # dlaczego nie $<
Zad2: shader controls2 Zad2utils
	g++ ${FLAGS} -o Zad2/Zad2 Zad2/Zad2.cpp shader.o controls2.o utils.o ${LIBS}
Zad3: shader utilsZ3 controlsZ3
	g++ ${FLAGS} -o Zad3/Zad3 Zad3/Zad3.cpp shader.o utils.o controls.o ${LIBS} 



simple: textfile.o
	g++ ${FLAGS} -o SimpleTexture/simple SimpleTexture/simple.cpp textfile.o ${LIBS} ${COMMON} # dlaczego nie $<

picture: 
	g++ ${FLAGS} -o Zad2/picture Zad2/picture.cpp ${LIBS} ${COMMON} # dlaczego nie $<

shader:
	g++ ${FLAGS} mineCommon/shader.cpp -c ${LIBS}

Zad2utils:
	g++ ${FLAGS} Zad2/utils.cpp -c ${LIBS}

utilsZ3:
	g++ ${FLAGS} -o utils.o Zad3/utils.cpp -c ${LIBS}

textfile:
	g++ ${FLAGS} SimpleTexture/textfile.cpp -c ${LIBS}


controls:
	g++ ${FLAGS} mineCommon/controls.cpp -c ${LIBS}

controls2:
	g++ ${FLAGS} mineCommon/controls2.cpp -c ${LIBS}

controlsZ3:
	g++ ${FLAGS} Zad3/controls.cpp -c ${LIBS}

.PHONY: Zad1 Zad2 Zad3

clean:
	touch sth.o && rm *.o 
