// Texture example, some code based on   http://www.opengl-tutorial.org/
// X.2015 (c) A. Łukaszewski
// ===========================================================================
// Kompilacja :
// g++ -std=c++11 -c -I. -I/home/anl/include/ -I/home/anl/include/GLFW/  image.cpp
// g++ -L/home/anl/libs/ image.o -o image -lGL -lX11 -lglfw3 -lGLEW -lX11 -lXxf86vm -lpthread -lXrandr -lXinerama -lXi -lXcursor
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <glfw3.h>

// ===========================================================================
// 1. GetGLFWWindow()
// Funkcja która opakowuje incjalizacje GLFW.... i stworzenie okna.....
// można użyć i kod reszty prostszy, nic ciekawego nie ma poza tym co było. 
// ===========================================================================
GLFWwindow* GetGLFWwindow(int& w, int& h, const char *name){
   GLFWwindow* window;
   // Initialise GLFW
   if( !glfwInit() ) {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      exit(-1);
   }
   glfwWindowHint(GLFW_SAMPLES, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   if (w==0 || h==0) {
      // if 0 than WINDOWLESS FULL SCREEN :
      GLFWmonitor* monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode    = glfwGetVideoMode(monitor);
      glfwWindowHint(GLFW_RED_BITS, mode->redBits);
      glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
      glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
      glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
      window = glfwCreateWindow(mode->width, mode->height, name, monitor, NULL);
      w=mode->width; h=mode->height;
   } else {
      // Open a window and create its OpenGL context
      window = glfwCreateWindow( w, h, name, NULL, NULL);
   }

   if( window == NULL ) {
      fprintf( stderr, "Failed to open GLFW window. .... \n" );
      glfwTerminate();
      exit(-1);
   }
   glfwMakeContextCurrent(window);

   // Initialize GLEW
   glewExperimental = true; // Needed for core profile
   if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      exit(-1);
   }
   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
   return window;
}

// ===========================================================================
// 2. klasa AGLDrawable() 
// Zawiera metody do kompilacji shaderów, kasowanie buforów, w ten sposób 
// można sobie uprościć właściwą klasę która ma własne shadery, bufory 
// i definiuje format dancych poniżej w punkcie 4. 
//#include "AGLDrawable.hpp"
// ===========================================================================
class AGLDrawable {
 public:
   AGLDrawable(GLuint _pid=0) { 
      vaoId=0; vboId=0; pId=_pid;
   }
   ~AGLDrawable() {   // Cleanup VBO,VBO,Prog
      glDeleteBuffers     (1, &vboId);
      glDeleteVertexArrays(1, &vaoId);
      glDeleteProgram(           pId);
   }
   int CompileShaders(GLuint v, GLuint f){
      GLint Result = GL_FALSE;
      int InfoLogLength;
      glCompileShader(v);
      glGetShaderiv(v, GL_COMPILE_STATUS, &Result);
      glGetShaderiv(v, GL_INFO_LOG_LENGTH, &InfoLogLength);
      if ( InfoLogLength > 0 && !Result ) {
         std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
         glGetShaderInfoLog(v, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
         printf("VS: %s\n", &VertexShaderErrorMessage[0]);  //exit(1);
      } else Result = GL_FALSE;

      glCompileShader(f);
      glGetShaderiv(f, GL_COMPILE_STATUS, &Result);
      glGetShaderiv(f, GL_INFO_LOG_LENGTH, &InfoLogLength);
      if ( InfoLogLength > 0 && !Result ) {
         std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
         glGetShaderInfoLog(f, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
         printf("FS: %s\n", &VertexShaderErrorMessage[0]);  //exit(2);
      }

      pId = glCreateProgram();
      glAttachShader(pId,v);
      glAttachShader(pId,f);
      glLinkProgram(pId);
   }
   GLuint p(){return pId; }
   // VAO, VBO, Prog to clean in destructor
   GLuint vaoId, vboId, pId;
};
// ===========================================================================
// 3. klasa AImage                       <<<<<<<<<<<<<<<<<<<<<< do przepisania
// #include "AImage.H"
// Tu trzeba zaimplementować prostą klasę do czytania obrazów z plików, 
// która dalej jest używana do ładowania tekstury 
// np. przy pomocy DevIL: http://openil.sourceforge.net   
//#include <IL/il.h>
//#include <IL/ilu.h>
// obecnie na sztywno mamy wpisany obrazek 2x2
// ===========================================================================
#ifdef AIMAGE
#include "AImage.H"
#else
typedef unsigned char AByte;
class AImage 
{
public:
   AImage ()              { xsize = 2; ysize = 2; };
   AImage (char *filename){ xsize = 2; ysize = 2; };   // Init Load from file
   unsigned char Load (const char *filename){};// Load file deleting what was

   AByte *Ptr ()               { return ptr; };   
   inline int XRes () const    { return xsize;  };   
   inline int YRes () const    { return ysize;  };

private:
   int xsize, ysize;
   //unsigned char *ptr; 
   AByte            ptr[12] = { 255,0,0, 0,255,0, 0,0,255, 255,255,255  };
};
#endif
// ===========================================================================
// 4. klasa MyMap     <<<<<<<<<<<<<<<<<<<<<< WLASCIWY PRZYKLAD użycia tekstury 
// Ta klasa wyświetla obrazek wieć po zaimplementowaniu klasy AImage
// program powinien wyświetlać wczytany obrazek
// ===========================================================================
class MyMap : public AGLDrawable
{
public:
   MyMap(float _bb[4]) : AGLDrawable(0) {
      for (int i=0; i<4; i++) bb[i]=_bb[i];
      setShaders();
   }
   void setShaders() {
      const GLchar* vs[] = {
         "#version 330 core \n",
         "in vec2 pos;",
         "in vec2 tex;",
         "out vec2 vtex;",
         "void main(void) {",
         "   gl_Position = vec4(pos, 0.0, 1.0); ", 
         "   vtex=tex;",
         "}"
      };
      const GLchar* fs[] = {
         "#version 330 core \n",
         "uniform sampler2D texunit;",
         "in  vec2 vtex;",
         "out vec4 color;",
         "void main(void) {",
         "   color = texture2D(texunit, vtex);",
         "} "
      };
      GLuint v = glCreateShader(GL_VERTEX_SHADER);
      GLuint f = glCreateShader(GL_FRAGMENT_SHADER);   
      glShaderSource(v, 8, vs, NULL);   // Można też czytać z pliku
      glShaderSource(f, 7, fs, NULL);   // ...

      CompileShaders(v,f);
      glUseProgram(p());
   
      a0 = glGetAttribLocation(p(),  "pos");
      a1 = glGetAttribLocation(p(),  "tex");
      u1 = glGetUniformLocation(p(), "texunit");
   }
   void setBuffers() {
      glGenVertexArrays(1, &vaoId);
      glGenBuffers(     1, &vboId);
      glBindVertexArray(            vaoId);
      glBindBuffer(GL_ARRAY_BUFFER, vboId);
   
      GLfloat vert[][2] = {  // TRI FAN
         { bb[0],  bb[1] },
         { bb[2],  bb[1] },
         { bb[2],  bb[3] },
         { bb[0],  bb[3] },
         { 0., 1. },
         { 1., 1. },
         { 1., 0. },
         { 0., 0. }
      };
      glBufferData(GL_ARRAY_BUFFER, 8*2*sizeof(float), vert, GL_STATIC_DRAW );
      glEnableVertexAttribArray(a0);
      glVertexAttribPointer(
         a0,                 // attribute 0, must match the layout in the shader.
         2,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,//24,             // stride
         (void*)0            // array buffer offset
      );
      glEnableVertexAttribArray(a1);
      glVertexAttribPointer(
         a1,                 // attribute 1, but must match the layout in the shader.
         2,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,//24,             // stride
         (void*)(4*2*sizeof(float))          // array buffer offset of Texture Coords
      ); 
   }
   void setTexture(AImage img){
      glEnable( GL_TEXTURE_2D ); 
      glGenTextures( 1, &texture );
      glActiveTexture(GL_TEXTURE0);   // We use texture unit 0 only fixed!
      glBindTexture( GL_TEXTURE_2D, texture );
      glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, img.XRes(),
   	 img.YRes(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.Ptr() );
      glGenerateMipmap( GL_TEXTURE_2D );
   }
   void draw(float bb_xyst[4]) {      
      glUseProgram(p());
      glBindVertexArray(           vaoId);
      glBindBuffer(GL_ARRAY_BUFFER,vboId);
     
      glActiveTexture(GL_TEXTURE0);
      glUniform1i(u1, 0);  // texture unit 0
      glBindTexture(GL_TEXTURE_2D, texture); 
   
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
   }
public:
   GLuint a0,u0, a1,u1;   // Attrib and Uniform  Ids
   GLuint texture;
   float bb[4];
};

// ===========================================================================
// 5. main()  
// Tu już za dużo ciekawego nie ma, pętla główna zdarzeń i wywołanie
// rysowania przy pomocy metody klasy MyMap (można by mieć kilka 
// obiektów dla podobnych klas, każdy z własnymi danymi i shaderami.
// ===========================================================================
int main(int argc, char *argv[])
{
   int wd=800, ht=600;
   //int wd=0, ht=0;    // full screen
   GLFWwindow* window = GetGLFWwindow(wd, ht, "Image Viewer" ); // Pkt 1.

   AImage img(argv[1]);
   float unitbb[]={-.9, -.9, .9, .9};       // Bounding box, rectangle
   MyMap  Map(unitbb);                                          // Pkt.4
   Map.setBuffers();
   Map.setTexture(img);

   glClearColor(0.0f, 0.0f, 0.3f, 0.0f);    // Background
   do {
      // Clear the screen
      glClear( GL_COLOR_BUFFER_BIT );
    
      // My Map: rectangle
      Map.draw(unitbb);
   
      // Swap buffers
      glfwSwapBuffers(window);
      //glfwPollEvents();   // more real time high cpu usage 
      glfwWaitEvents();     // low cpu usage:    usleep 

   } // Check if the ESC key was pressed or the window was closed
   while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
   // Close OpenGL window and terminate GLFW
   glfwTerminate();
   return 0;
}
