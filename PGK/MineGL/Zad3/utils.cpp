#include "Zad3.hpp"

#define PI 3.14159265

ILuint width;// = ilGetInteger(IL_IMAGE_WIDTH);
ILuint height;
double minZ = 1000, maxZ = -1000;



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

ILubyte bindImage(std::string path)
{
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
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0); 
	return texture;
}
