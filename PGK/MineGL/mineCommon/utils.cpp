#include "Zad2.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define PI 3.14159265

ILuint width;// = ilGetInteger(IL_IMAGE_WIDTH);
ILuint height;
double minZ = 1000, maxZ = -1000;

int makeWindow(char* str)
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

        window = glfwCreateWindow( 1024, 768, str, NULL, NULL);
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

GLfloat resize(int args, char* path)
{
	FILE* file = fopen (path , "r");
	char wiersz[1000];
	GLfloat minX = 10000, maxX = -10000, minY = 10000, maxY = -10000, scaleX, scaleY, scaleZ, moveX, moveY, x, y;
	std::cout << path<<std::endl;
	while (fgets(wiersz, 1000, file) != NULL){
		std::cout << wiersz<<std::endl;
                        if (strstr(wiersz, "MMPLL")){
                                sscanf( wiersz, "MMPLL, %*d, %f, %f", &x, &y);
				if(x > maxX) maxX = x;
				if(x < minX) minX = x;
				if(y > maxY) maxY = y;
				if(y < minY) minY = y;
                        }
	}
	GLfloat cosin = cos(((maxY - minY)/2 + minY) * PI / 180)* width / height;
	
	std::cout << (maxY - minY)/2 + minY << " bounds" << maxX << " " << minX <<" " << maxY << " " << minY<<std::endl;
	scaleX = (maxX - minX)/2;
        scaleY = (maxY - minY)/2;
		scaleZ = maxZ - minZ;
        moveX = (maxX + minX)/2 ;
        moveY = (maxY + minY)/2;
		std::cout << "cosin: " << cosin <<" scaleX" << scaleX << " scaleY " << scaleY << "moveX" << moveX << " moveY " << moveY<<std::endl;
		for(int arg = 0; arg < args; arg++)		
				for(int i = 0; i < data[arg].size();i++)
				{
						//std::cout << "Przed " <<data[arg][i] << " " << data[arg][i+1];
				        data[arg][i] = ((data[arg][i]) -moveY) / scaleY;
				        data[arg][++i] = ((data[arg][i]) -moveX) *cosin/ scaleX;
						data[arg][++i] = ((data[arg][i]) -minZ)/ scaleZ; 
				} 
	return cosin;      
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

int loadVertex(int arg, char * argv)
{
        std::cout << arg << std::endl;
                FILE* file = fopen (argv , "r");
                char wiersz[1000];
                char latlon=0;
                std::cout << "laduje\n";
                while (fgets(wiersz, 1000, file) != NULL){
                        float lat,lon,ele;
                        char *p;
                        if (strstr(wiersz, "<trkpt ")){
                                 sscanf( strstr(wiersz, "lat=\"")+5, "%f", &lat);
                                 sscanf( strstr(wiersz, "lon=\"")+5, "%f", &lon);
                                 data[arg].push_back(lat);
                                 data[arg].push_back(lon);
								 data[arg].push_back(0);
                                 data[arg].push_back(lat);
                                 data[arg].push_back(lon);
                                 latlon = 1;
                        }
                        else if (p=strstr(wiersz, "<ele>")){
                                sscanf( p+5, "%f</ele>", &ele); 
                                if (latlon == 1) {
                                 	data[arg].push_back(ele);
									if(ele > maxZ) maxZ = ele;
									if(ele < minZ) minZ = ele;				
                                }
                        }
                }

                std::cout << "done" << std::endl;
		std::cout << data[arg].size() << std::endl;
}
