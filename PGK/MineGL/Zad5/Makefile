LIBS= -lglfw3 -lGL -lGLU -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXi -lIL #-ltiff -lpng12 -llcms -ljasper -ljpeg -lIlmImf -lz -lImath -lHalf -lIex -lIlmThread 
FLAGS= -std=gnu++11 -O3 -L/home/anl/libs/ -I/home/anl/include/ -I/home/anl/include/GLFW/ -I.. -L.. -I../include -L../lib -I../lib/glew-1.9.0/include

all: Zad5

Zad5:
	g++ ${FLAGS} -o Zad5 *.cpp ${LIBS} 
	
.PHONY: Zad5
