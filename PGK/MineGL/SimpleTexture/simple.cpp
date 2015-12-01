//
// Lighthouse3D.com OpenGL Simple Texture Sample
//
//
// This demo was built for learning purposes only.
// Some code could be severely optimised, but I tried to
// keep as simple and clear as possible.
//
// The code comes with no warranties, use it at your own risk.
// You may use it, or parts of it, wherever you want.
//
// If you do use it I would love to hear about it. Just post a comment
// at Lighthouse3D.com

// Have Fun :-)


#include <string>


#ifdef _WIN32
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"devil.lib")
#endif

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// include DevIL to load images
#include <IL/il.h>

// FreeGLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>

// routines to  read the source code from file
#include "textfile.h"

// holder for the program id
GLuint p;
// holder for the vertex array object id
GLuint vao, textureID;

// ------------------------------------------------------------
//
//			Reshape Callback Function
//
// ------------------------------------------------------------

void changeSize(int w, int h) {

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
}


// --------------------------------------------------------
//
//			Render Stuff
//
// --------------------------------------------------------

void renderScene() {

	// clear the framebuffer (color and depth)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the program p
	glUseProgram(p);
	// Bind the vertex array object
	glBindVertexArray(vao);
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	// draw the 6 vertices
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// swap buffers
	glutSwapBuffers();
}


// --------------------------------------------------------
//
//			Shader Stuff
//
// --------------------------------------------------------

void setupShaders() {

	// variables to hold the shader's source code
	char *vs = NULL,*fs = NULL;
 
	// holders for the shader's ids
    GLuint v,f;
 
	// create the two shaders
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
 
	// read the source code from file
    vs = textFileRead("texture.vert");
    fs = textFileRead("texture.frag");
 
	// castings for calling the shader source function
    const char * vv = vs;
    const char * ff = fs;
 
	// setting the source for each shader
    glShaderSource(v, 1, &vv, NULL);
    glShaderSource(f, 1, &ff, NULL);
 
	// free the source strings
    free(vs);free(fs);
 
	// compile the sources
    glCompileShader(v);
    glCompileShader(f);
  
	// create a program and attach the shaders
    p = glCreateProgram();
    glAttachShader(p,v);
    glAttachShader(p,f);

	// Bind the fragment data output variable location
	// requires linking afterwards
	glBindFragDataLocation(p, 0, "outputF");

	// link the program
	glLinkProgram(p);

	GLint myLoc = glGetUniformLocation(p, "texUnit");
	glProgramUniform1d(p, myLoc, 0);

	// get the logs from the compile and link procedures
	GLint infologLength, charsWritten;
	char *infoLog;

	glGetShaderiv(v, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(v, infologLength, &charsWritten, infoLog);
			printf("\n%s\n", infoLog);
		}
	glGetShaderiv(f, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(f, infologLength, &charsWritten, infoLog);
			printf("\n%s\n", infoLog);
		}
	glGetProgramiv(p, GL_INFO_LOG_LENGTH,&infologLength);

		if (infologLength > 0)
		{
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(p, infologLength, &charsWritten, infoLog);
			printf("\n%s\n", infoLog);
		}
}



// ------------------------------------------------------------
//
//			OpenGL setup
//
// ------------------------------------------------------------


void initGL()
{
// Data for the two triangles
	float position[] = {-1.0f, -1.0f, 0.0f, 1.0f,
						 1.0f,  1.0f, 0.0f, 1.0f,
						-1.0f,  1.0f, 0.0f, 1.0f,

						 1.0f,  1.0f, 0.0f, 1.0f,
						-1.0f, -1.0f, 0.0f, 1.0f,
						 1.0f, -1.0f, 0.5f, 1.0f,
	};
 
	float textureCoord[] = {	
						0.0f, 0.0f, 
						1.0f, 1.0f,
						0.0f, 1.0f, 

						1.0f, 1.0f,
						0.0f, 0.0f, 
						1.0f, 0.0f};


	GLuint vertexLoc, texCoordLoc;

	// Get the locations of the attributes in the current program
	vertexLoc = glGetAttribLocation(p, "position");
	texCoordLoc = glGetAttribLocation(p, "texCoord");

	// Generate and bind a Vertex Array Object
	// this encapsulates the buffers used for drawing the triangle
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	// Generate two slots for the position and color buffers
    GLuint buffers[2];
    glGenBuffers(2, buffers);

    // bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
 
    // bind buffer for normals and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoord), textureCoord, GL_STATIC_DRAW);
    glEnableVertexAttribArray(texCoordLoc);
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, 0, 0, 0);

	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}


// ------------------------------------------------------------
//
//			Loading the image
//
// ------------------------------------------------------------

unsigned int ilLoadImage(std::string filename) {

	ILboolean success;
	unsigned int imageID;
 
	// init DevIL. This needs to be done only once per application
	ilInit();
	// generate an image name
	ilGenImages(1, &imageID); 
	// bind it
	ilBindImage(imageID); 
	// match image origin to OpenGL’s
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	// load  the image
	success = ilLoadImage((ILstring)filename.c_str());
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	// check to see if everything went OK
	if (!success) {
		ilDeleteImages(1, &imageID); 
		return 0;
	}
	else return imageID;
}


// ------------------------------------------------------------
//
//			Prepare texture
//
// ------------------------------------------------------------

void prepareTexture(int w, int h, unsigned char* data) {

	/* Create and load texture to OpenGL */
	glGenTextures(1, &textureID); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, textureID); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
                w, h, 
                0, GL_RGBA, GL_UNSIGNED_BYTE,
                data); 
	glGenerateMipmap(GL_TEXTURE_2D);
}


// ------------------------------------------------------------
//
//			Main function
//
// ------------------------------------------------------------


int main(int argc, char **argv) {

	int w,h,id;
	unsigned char* data;

	// load image first so that window opens with image size
	id = ilLoadImage("test.jpg");
	// image not loaded
	if (id == 0)
		return(2);

	ilBindImage(id);
	w = ilGetInteger(IL_IMAGE_WIDTH);
	h = ilGetInteger(IL_IMAGE_HEIGHT);
	data = ilGetData();

//  GLUT initialization
	glutInit(&argc, argv);
	// Standard display mode plus multisample (to provide some antialiasing)
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_MULTISAMPLE);
	// the OpenGL version (major, minor)
	glutInitContextVersion (3, 3);
	// Profile selection, the core profile ensures no deprecated functions are used
	glutInitContextProfile (GLUT_CORE_PROFILE );

	// standard glut settings
	glutInitWindowPosition(100,100);
	glutInitWindowSize(w,h);
	glutCreateWindow("Lighthouse3D - Simplest Texture Demo");

//  Callback Registration
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

//	Init GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	// check if the required version is supported
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported\n");
		return(1);
	}

//	Display some general info
	printf ("Vendor: %s\n", glGetString (GL_VENDOR));
	printf ("Renderer: %s\n", glGetString (GL_RENDERER));
	printf ("Version: %s\n", glGetString (GL_VERSION));
	printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));

//	Set up texture with the image data we got earlier
	prepareTexture(w,h,data);

//	Load and prepare shaders
	setupShaders();
	
//	Init buffers 
	initGL();

//	GLUT main loop
	glutMainLoop();

//	because standard C++ requires a return value
	return(0);
}

