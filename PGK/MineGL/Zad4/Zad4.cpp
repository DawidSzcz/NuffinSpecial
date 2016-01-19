#include "Zad4.hpp"

GLFWwindow* window;
extern int windowWidth, windowHeight;
extern int rowsNum, colsNum;
extern std::vector<GLfloat> cords;
extern std::vector<std::vector<GLint>> elems;


int main(int argc, char * argv[] )
{	
	if(makeWindow(windowWidth, windowHeight, (char*)"Zad4") == -1)
		return -1;
	GLuint texture = bindImage(argv[2]);
	readFile(argv[1]);
	/*float data_f[24] = { -0.5 ,  0.5 , 0.0 ,
						  0.5 , 0.5 , 0.3 , 
						  -0.5, -0.5, 0.6, 
						  0.5, -0.5, 1.0,
						0.6 ,  0.9 , 0.0 , 0.9 , 0.9 , 0.3 , 0.9, 0.6, 0.6, 0.6, 0.6, 1.0 } ; 
	cords.insert( cords.begin() , data_f , data_f + 12 ) ; 
	for(int i =0; i<elems.size(); i++)
		std::cout<<elems[i]<<" ";
	for(int i =0; i<elems.size(); i++)
		std::cout<<elems[i]<<" ";*/
	
	//GLuint indices[] = {  2, 0, 1, 2, 3, 0,6,4,5,6,7,4};
	//elems.insert( elems.begin() , indices , indices + 6 ) ;

	
	genElements(colsNum);
	/*for(int i = 0; i< elems.size(); i++)
	{
		for(int j = 0; j< elems[i].size(); j++)
			std::cout<<elems[i][j]<<" ";
		std::cout<<"\n\n";	
	}*/
	//std::cout<<cords.size() <<" " << elems.size();

 	GLuint programID1 = LoadShaders( "Transform.vertexshader", "FragmentShader.fragmentshader" ); 

	GLuint VAO[elems.size()], VBA[elems.size()][2], EBO[elems.size()];
	for(int i = 0; i < elems.size(); i++)
	{
		glGenVertexArrays(1, &VAO[i]);
		glBindVertexArray(VAO[i]);
		glGenBuffers(1, &VBA[i][0]);
		glBindBuffer(GL_ARRAY_BUFFER,VBA[i][0]);
		glBufferData(GL_ARRAY_BUFFER, cords.size()* sizeof(GLfloat), &cords.front(), GL_STATIC_DRAW);
		glGenBuffers(1, &EBO[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elems[i].size()*sizeof(GLint), &elems[i].front(), GL_STATIC_DRAW); 
		glVertexAttribPointer(
		                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		                3,                  // size
		                GL_FLOAT,           // type
		                GL_FALSE,           // normalized?
		                3*sizeof(GLfloat),                  // stride
		                (void*)0            // array buffer offset
		    );
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &VBA[i][1]);
		glBindBuffer(GL_ARRAY_BUFFER,VBA[i][1]);
		glBufferData(GL_ARRAY_BUFFER, normals.size()* sizeof(glm::vec3), &cords.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(
		                1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		                3,                  // size
		                GL_FLOAT,           // type
		                GL_FALSE,           // normalized?
		                3*sizeof(GLfloat),                  // stride
		                (void*)0            // array buffer offset
		    );
		glEnableVertexAttribArray(1);
		glBindVertexArray(0); 
	}
	
	glEnable(GL_DEPTH_TEST); 
	
	glm::mat4 cameraPos;
	glm::mat4 model;
	GLuint tr1 = glGetUniformLocation(programID1, "transform");
	GLuint mod = glGetUniformLocation(programID1, "model");
	GLuint lp = glGetUniformLocation(programID1, "light_pos");
	
	glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
	do{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		
		computeMatricesFromInputs();		
		cameraPos = getCameraPos();		
		model = getModel();
		glUseProgram(programID1);		
		glUniformMatrix4fv(tr1, 1, GL_FALSE, glm::value_ptr(cameraPos));		
		glUniformMatrix4fv(mod, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(lp, 1, glm::value_ptr(getPosition()));
		
		//std::cout<<getPrecision()%elems.size()<<std::endl;
		glBindVertexArray(VAO[getPrecision()%elems.size()]);		
		glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, elems[getPrecision()%elems.size()].size(), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
