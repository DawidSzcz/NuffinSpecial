#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <array>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "shader.hpp"


GLFWwindow* window;
int windowWidth =400, windowHeight = 400;

ILubyte bindImage(std::string path)
{
	ILuint width;// = ilGetInteger(IL_IMAGE_WIDTH);
	ILuint height;
	GLuint texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture); 
	ilInit();
	ILuint ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ILboolean success = ilLoadImage((ILstring)path.c_str());
	if(success == false)
	{
		ILenum Error ;
		while ((Error = ilGetError()) != IL_NO_ERROR) 
		    fprintf(stderr, "%d\n",Error);
	}
	else
		std::cout<<"Poszlo\n";
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT); 
	ILubyte *Data = ilGetData(); 
	std::cout<<width<<" "<<height<<"\n"; 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	std::cout<<"Wygenerowałem obrazek\n";
	glGenerateMipmap(GL_TEXTURE_2D);
std::cout<<"Wygenerowałem obrazek\n";
	glBindTexture(GL_TEXTURE_2D, 0); 
	return texture;
}

int makeWindow(int x, int y, char* str)
{        
	if( !glfwInit() )
        {
                fprintf( stderr, "Failed to initialize GLFW\n" );
                return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow( x, y, str, NULL, NULL);
        if( window == NULL ){
                fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);
        // Initialize GLEW
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
                fprintf(stderr, "Failed to initialize GLEW\n");
                return -1;
        }

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Dark blue background
        glClearColor(0.0f, 0.5f, 0.4f, 0.0f);
}

int main(int argc, char * argv[] )
{
std::cout<<"Wygenerowałem obrazek\n";
    	struct stat sb;
	time_t oldModif;
	double mouseX, mouseY;

   	if (argc != 2) {
        	fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        	exit(EXIT_FAILURE);
    	}

   	if (stat(argv[1], &sb) == -1) {
        	perror("stat");
        	exit(EXIT_FAILURE);
    	}
	oldModif = sb.st_mtime;
	
	glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
	if(makeWindow(windowWidth, windowHeight, (char*)"Zad3") == -1)
		return -1;
		
	
	GLuint texture = bindImage("tex.png");

 	GLuint programID1 = LoadShaders( "shader.vertexshader", argv[1] );
	GLfloat vertexes[] = {
    		-1.0f, 1.0f, 
     		1.0f, 1.0f, 
     		-1.0f, -1.0f, 
		1.0f, -1.0f
	};  
	GLuint indices[] = {  2, 0, 1, 2, 3, 1};
        
	GLuint VAO, VBA, EBO;
	
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
	glGenBuffers(1, &VBA);
    glBindBuffer(GL_ARRAY_BUFFER,VBA);
	glBufferData(GL_ARRAY_BUFFER, 8* sizeof(GLfloat), vertexes, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
	glVertexAttribPointer(
                    0,                  
                    2,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    2*sizeof(GLfloat),                  // stride
                    (void*)0            // array buffer offset
        );
	glEnableVertexAttribArray(0);
	

	GLuint res = glGetUniformLocation(programID1, "iResolution");
	GLuint mouse = glGetUniformLocation(programID1, "iMouse");
	GLuint time = glGetUniformLocation(programID1, "iGlobalTime");
	GLuint channel = glGetUniformLocation(programID1, "iChannel0");
	glm::vec3 resV = glm::vec3(0.1, 1.0, 1.0);
	float x =0.1;
	glm::vec4 mouseV = glm::vec4(x,x,x,x);
	//glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
		
		glfwGetCursorPos(window, &mouseX, &mouseY);
		//std::cout<<mouseX<<" "<<mouseY<<std::endl;
		
		mouseV = glm::vec4(mouseX,mouseY,x,x);
		
		stat(argv[1], &sb);
		if(oldModif != sb.st_mtime)
			programID1 = LoadShaders( "shader.vertexshader", argv[1] );
		oldModif = sb.st_mtime;
		//std::cout<<sb.st_mtime<<std::endl;
		glUseProgram(programID1);	
		glUniform1f(time, glfwGetTime());	
		glUniform3fv(res, 1, glm::value_ptr(resV));	
		glUniform4fv(mouse, 1, glm::value_ptr(mouseV));
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);		
        	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
