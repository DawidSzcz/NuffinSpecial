#include "Zad4.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int windowWidth = 1024, windowHeight = 1024;
int rowsNum, colsNum;

float** heights;
std::vector<GLfloat> cords;
std::vector<glm::vec3> normals;
std::vector<std::vector<GLint>> elems;

glm::vec3 normal(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 e1, e2, norm;
	float max;
	e1 = a-b;
	e2 = a-c;
	
	norm = glm::vec3(e1.y*e2.z -e1.z*e2.y, e1.z*e2.x - e1.x*e2.z, e1.x*e2.y - e1.y*e2.x);
	max = std::max(std::max(norm.x, norm.y), norm.z);
	
	return norm / max;
}

void readFile(std::string fName)
{
	int count = 0, x = 0, y = 0, tri = 0;
	glm::vec3 triangle[3];
	float maxValue, height;
	std::ifstream ifs;

	ifs.open (fName, std::ifstream::in);

	char dimensionsS[50];
	char maxValueS[50];
	char c, d;
	ifs.getline(dimensionsS, 50);
	ifs.getline(dimensionsS, 50);
	ifs.getline(maxValueS, 50);
	sscanf(dimensionsS, "%d %d", &rowsNum, &colsNum);
	sscanf(maxValueS, "%f", &maxValue); 

	heights = new float*[colsNum];
	for(int i = 0; i < colsNum; i++)
		heights[i] = new float[rowsNum];
		
	std::cout<<rowsNum<<" "<<colsNum<<" "<< maxValue<<std::endl;
	c = ifs.get();
	while (ifs.good()) {
		d = ifs.get();
		height = ((float)c+128.0)*256+(float)d+128;
		//std::cout<<colsNum-1-y/scale<<" "<<x/scale<<std::endl;
		heights[colsNum-1-y][x] = height/maxValue;
		cords.push_back((float)x * 2/ colsNum - 1.0);
		cords.push_back(height/maxValue);
		cords.push_back((float)y * 2/ rowsNum - 1.0);
		triangle[tri++] = glm::vec3((float)x * 2/ colsNum - 1.0, height/maxValue, (float)y * 2/ rowsNum - 1.0);
		if(tri == 3)
		{
			glm::vec3 norm = normal(triangle[0], triangle[1], triangle[2]);
			normals.push_back(norm);
			normals.push_back(norm);
			normals.push_back(norm);
			tri = 0;
		}
		x++;
		if(x >= rowsNum)
		{			
			x = 0;
			y++;
		}	
		c = ifs.get();			
	}
	//std::cout<<x<<" "<<y<<" "<<count;
	ifs.close();
	//for(int i = 0; i < 4000; i+=3)
		//std::cout<<cords[i]<<" "<<cords[i+1]<<" "<<cords[i+2]<<"\n";*/
}

void genElements(int x)
{
	int ind = 0;
	for(int d = x; d > 2; d=d/2+1)
	{
		int m = (x-1)/(d-1);
		std::vector<GLint> el;
		for(int i = 0; i<x-m; i+=m)
			for(int j = 0; j<x-m; j+=m)
			{
				el.push_back((x*i)+j);
				el.push_back((x*i)+j+m);
				el.push_back((x*(i+m))+j);
				el.push_back((x*i)+j+m);
				el.push_back((x*(i+m))+j);
				el.push_back((x*(i+m))+j+m);
			}
		elems.push_back(el);
	}
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
	glBindTexture(GL_TEXTURE_2D, 0); 
	return texture;
}
