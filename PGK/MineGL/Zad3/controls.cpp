#include "Zad3.hpp"

extern GLFWwindow* window;
extern GLfloat xpos, ypos;

#define PI 3.14159265

double  speed = 0.3;
GLfloat zAngle = 0.0, xAngle = -90.0;
bool released = true, is3D = false;
float mouseSpeed = 0.5f;

using namespace glm;

glm::mat4 getCameraPos()
{
	glm::mat4 projection;
	projection = glm::perspective(45.0f, 1.0f, 0.1f, 10.0f);
	
	glm::mat4 model;
	model = glm::rotate(model, xAngle, glm::vec3(1.0, 0.0, 0.0));
	model = glm::translate(model, glm::vec3(-xpos, zpos, zpos));
	model = glm::rotate(model, zAngle, glm::vec3(0.0, 0.0, 1.0));
	model = glm::translate(model, glm::vec3(xpos, -zpos, -zpos));
	
	glm::mat4 view;
	view = glm::scale(view, glm::vec3(2.0, 1.0, 2.0));
	view = glm::translate(view, glm::vec3(xpos, -1.0/SIZE, zpos));
	
 	return projection * view * model;
}

bool isBanned(GLfloat x, GLfloat y)
{
	float border = 2.0/SIZE/4;
	return banned(x,y) 
		|| banned(x+border, y)
		|| banned(x-border, y) 
		|| banned(x, y + border)
		|| banned(x, y - border)
		|| banned(x+border, y+border)
		|| banned(x-border, y-border) 
		|| banned(x + border, y - border)
		|| banned(x - border, y + border);
}

bool banned(GLfloat x, GLfloat z)
{
	int xI = (int)((-x+1.0)*(float)SIZE/2.0);
	int zI = (int)((-z+1.0)*(float)SIZE/2.0);
	if(x < -1 || x > 1 || z < -1 || z > 1)
		return true;
	//std::cout<<"isBanned: " << " "<< xI <<" - " << x << " ; " << zI  << " - " << z << std::endl;
	return isWall[xI][zI];		
}
bool isEnd()
{
	int xI = (int)((-xpos+1.0)*(float)SIZE/2.0);
	int zI = (int)((-zpos+1.0)*(float)SIZE/2.0);
	//std::cout<<"Meta:" << mX << " : " << xI << mZ << " : " << zI << "\n";
	return xI == mZ && zI == mX;	
}

void computeMatricesFromInputs(){

	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

	// Compute new orientation
	zAngle -= mouseSpeed * float(1024/2 - mouseX ) * deltaTime;
	
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		if(!isBanned(zpos + cos(zAngle/180.0 * PI)*speed*deltaTime, xpos))
			zpos += cos(zAngle/180.0 * PI)*speed*deltaTime;
		if(!isBanned(zpos, xpos - sin(zAngle/180.0 * PI)*speed*deltaTime))
			xpos -= sin(zAngle/180.0 * PI)*speed*deltaTime;
	}	
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		if(!isBanned(zpos - cos(zAngle/180.0 * PI)*speed*deltaTime, xpos))
			zpos -= cos(zAngle/180.0 * PI)*speed*deltaTime;
		if(!isBanned(zpos, xpos + sin(zAngle/180.0 * PI)*speed*deltaTime))
			xpos += sin(zAngle/180.0 * PI)*speed*deltaTime;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		zAngle += speed * 100*deltaTime;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		zAngle -= speed * 100*deltaTime;
	}
	lastTime = currentTime;
}

void print(mat4 temp)
{
		std::cout<<std::endl<<temp[0][0]<<"\t"<<temp[0][1]<<"\t"<<temp[0][2]<<"\t"<<temp[0][3]<<std::endl;
		std::cout<<temp[1][0]<<"\t"<<temp[1][1]<<"\t"<<temp[1][2]<<"\t"<<temp[1][3]<<std::endl;
		std::cout<<temp[2][0]<<"\t"<<temp[2][1]<<"\t"<<temp[2][2]<<"\t"<<temp[2][3]<<std::endl;
		std::cout<<temp[3][0]<<"\t"<<temp[3][1]<<"\t"<<temp[3][2]<<"\t"<<temp[3][3]<<std::endl;
}
