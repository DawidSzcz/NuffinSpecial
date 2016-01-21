#include "Zad4.hpp"

extern GLFWwindow* window;
extern float** heights;
extern int rowsNum, colsNum;
GLfloat scale = 10.0, scaleY = 2.0;
GLfloat xpos, ypos = -scaleY, zpos = 0.0;

#define PI 3.14159265

double  speed = 1.5;
GLfloat xAngle = 0.0, yAngle = 0.0;
bool subReleased = true, addReleased = true, is3D = false;
float mouseSpeed = 1.0f, border = 0.1;
double move;
int precision = 0;

glm::mat4 getCameraPos()
{
	glm::mat4 projection;
	projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	
	/*model = glm::rotate(model, zAngle, glm::vec3(0.0, 0.0, 1.0));
	model = glm::translate(model, glm::vec3(0, 0, -10.0));*/
	
	glm::mat4 view;
	//view = glm::scale(view, glm::vec3(scale, scale, 1.0));
	view = glm::rotate(view, yAngle, glm::vec3(0.0, 1.0, 0.0));
	view = glm::rotate(view, xAngle, glm::vec3(cos(yAngle/180.0 * PI), 0.0, sin(yAngle/180.0 * PI)));
	view = glm::translate(view, glm::vec3(xpos, ypos, zpos));
		
 	return projection * view;
}
glm::mat4 getModel()
{
	glm::mat4 model;
	//model = glm::rotate(model, zAngle, glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, glm::vec3(scale, scaleY, scale));
	return model;
}

glm::vec3 getPosition()
{
	return glm::vec3(-xpos, ypos, -zpos);
}

int getPrecision()
{
	return precision;
}
bool isPermitted(GLfloat x, GLfloat z, GLfloat y)
{
	if(x < -scale || x > scale || z < -scale || z > scale)
		return false;
	int xI = rowsNum - floor((x/scale+1.0)/2*rowsNum);
	int zI = floor((z/scale+1.0)/2*colsNum);
	double max = std::max(std::max(heights[zI][xI],heights[zI+1][xI]), std::max(heights[zI][xI+1],heights[zI+1][xI+1])) *scaleY;
	//std::cout<<"zI: "<<zI<<" xI: "<<xI<<" x: "<<x<<" z: "<<z<<" y: "<<y << " max: "<< max<<std::endl;
	return  max + border <  -y;		
}

void computeMatricesFromInputs(){
	static double lastTime = glfwGetTime();
	
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	std::cout<<"FPS: "<< 1.0/deltaTime;	
	double mouseX, mouseY;
	
	mouseX = windowWidth/2;
	mouseY = windowWidth/2;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

	// Compute new orientation
	yAngle -= mouseSpeed * float(windowWidth/2 - mouseX ) * deltaTime;
	xAngle -= mouseSpeed * float(windowHeight/2 - mouseY ) * deltaTime;
	
	
	move = speed*deltaTime;
	//std::cout<<"xAngle: "<<xAngle<<" yAngle: "<<yAngle<<" xpos: "<<xpos<<" ypos: "<<ypos<<" zpos: "<<zpos<<std::endl;
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		if(isPermitted(xpos, zpos + cos(xAngle/180.0 * PI)*cos(yAngle/180.0 * PI)*move, ypos)) 
			zpos += cos(xAngle/180.0 * PI)*cos(yAngle/180.0 * PI)*move;
		if(isPermitted(xpos - sin(yAngle/180.0 * PI)*move, zpos, ypos))
			xpos -= sin(yAngle/180.0 * PI)*move;
		if(isPermitted(xpos, zpos, ypos+sin(xAngle/180.0 * PI)*move))
			ypos += sin(xAngle/180.0 * PI)*move;
	}	
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		if(isPermitted(xpos, zpos - cos(xAngle/180.0 * PI)*cos(yAngle/180.0 * PI)*move, ypos))
			zpos -= cos(xAngle/180.0 * PI)*cos(yAngle/180.0 * PI)*move;
		if(isPermitted(xpos + sin(yAngle/180.0 * PI)*move, zpos, ypos))
			xpos += sin(yAngle/180.0 * PI)*move;
		if(isPermitted(xpos, zpos, ypos-sin(xAngle/180.0 * PI)*move))
			ypos -= sin(xAngle/180.0 * PI)*move;
	}
	if (subReleased && glfwGetKey( window, GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS){
		precision++;
		subReleased = false;
	}
	if (addReleased && glfwGetKey( window, GLFW_KEY_KP_ADD    ) == GLFW_PRESS){
		precision--;
		addReleased = false;
	}
	if (glfwGetKey( window, GLFW_KEY_KP_ADD) == GLFW_RELEASE){
		addReleased = true;
	}
	if (glfwGetKey( window, GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE){
		subReleased = true;
	}
	lastTime = currentTime;
}

void print(glm::mat4 temp)
{
		std::cout<<std::endl<<temp[0][0]<<"\t"<<temp[0][1]<<"\t"<<temp[0][2]<<"\t"<<temp[0][3]<<std::endl;
		std::cout<<temp[1][0]<<"\t"<<temp[1][1]<<"\t"<<temp[1][2]<<"\t"<<temp[1][3]<<std::endl;
		std::cout<<temp[2][0]<<"\t"<<temp[2][1]<<"\t"<<temp[2][2]<<"\t"<<temp[2][3]<<std::endl;
		std::cout<<temp[3][0]<<"\t"<<temp[3][1]<<"\t"<<temp[3][2]<<"\t"<<temp[3][3]<<std::endl;
}
