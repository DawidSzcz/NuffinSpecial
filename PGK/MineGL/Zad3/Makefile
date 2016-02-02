LIBS= -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lIL #-ltiff -lpng12 -llcms -ljasper -ljpeg -lIlmImf -lz -lImath -lHalf -lIex -lIlmThread 
FLAGS= -std=gnu++11 -O3 -L/home/anl/libs/ -I/home/anl/include/ -I/home/anl/include/GLFW/  -I../include -L../lib

all: Zad3

Zad3:
	g++ ${FLAGS} -o Zad3 *.cpp ${LIBS} 
	
.PHONY: Zad3
