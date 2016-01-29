#ifndef PHONG_SHADER_HPP
#define PHONG_SHADER_HPP

#include <string>
#include "BasicHeader.hpp"
#include <glm/gtc/matrix_inverse.hpp>
#include "IDrawable.hpp"
#include "PointLight.hpp"
#include "IShader.hpp"
#include "ICamera.hpp"

class PhongShader : public IShader {
public:
	virtual void SetUniforms(const IDrawable& d,const ICamera* camera,const std::vector<const PointLight*>& lights) {
		Transformation_t View = camera->GetView();
		Transformation_t Projection = camera->GetProjection();
		Transformation_t Model = d.Model;
		Transformation_t MV = View * Model;
		Transformation_t normalMatrix = glm::inverseTranspose(MV);
		Transformation_t MVP = Projection * MV;

		assert(lights.size() <= LightsNumberMax);
		Colour_t intensities[LightsNumberMax];
		Position_t positions[LightsNumberMax];
		for(unsigned int i=0 ; i < lights.size() ; i++) {
			intensities[i] = lights[i]->Intensity;
			positions[i] = lights[i]->Position;
		}

		setViewMatrix(View);
		setMVPMatrix(MVP);
		setModelMatrix(Model);
		setNormalMatrix(normalMatrix);
		setLightsNumber(lights.size());
		setLightIntensity(intensities,lights.size());
		setLightPosition(positions,lights.size());	
	}

	virtual void OnBind() {
		glUseProgram(id);
		enableAttributes();
		resetUniforms();
	}

	virtual void OnUnbind() {
		disableAttributes();
	}

	virtual void OnArrayBufferBind() {
		setAttributesPointers();
	}

	PhongShader(const std::string vshader,const std::string pshader)
	: IShader(vshader,pshader) {
		getUniformsIDs();
		getAttributesIDs();
	}

	static const GLuint LightsNumberMax = 12;
protected:
	virtual void getAttributesIDs() {
		vertexPosition_modelspaceID = glGetAttribLocation(id, "vertexPosition_modelspace");
		vertexColourID = glGetAttribLocation(id, "vertexColour");
		vertexNormal_modelspaceID = glGetAttribLocation(id, "vertexNormal_modelspace");
	}

	virtual void enableAttributes() {
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glEnableVertexAttribArray(vertexColourID);
		glEnableVertexAttribArray(vertexNormal_modelspaceID);
	}

	virtual void disableAttributes() {
		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexColourID);
		glDisableVertexAttribArray(vertexNormal_modelspaceID);
	}

	virtual void setAttributesPointers() {
		glVertexAttribPointer(vertexPosition_modelspaceID,3,COORD_TYPE,GL_FALSE,sizeof(Vertex_t),(void *)offsetof(Vertex_t,position));
		glVertexAttribPointer(vertexColourID,3,PRIMCOLUOR_TYPE,GL_FALSE,sizeof(Vertex_t),(void *)offsetof(Vertex_t,colour));
		glVertexAttribPointer(vertexNormal_modelspaceID,3,NCOORD_TYPE,GL_FALSE,sizeof(Vertex_t),(void *)offsetof(Vertex_t,normal));
	}

	virtual void getUniformsIDs() {
		MVPMatrixID = glGetUniformLocation(id, "MVP");
		viewMatrixID = glGetUniformLocation(id, "V");
		modelMatrixID = glGetUniformLocation(id, "M");
		normalMatrixID = glGetUniformLocation(id,"NormalMatrix");

		lightsNumberID = glGetUniformLocation(id,"LightsNumber");
		lightIntensityID = glGetUniformLocation(id,"LightIntensity");
		lightPositionID = glGetUniformLocation(id,"LightPosition_worldspace");
	}

	virtual void resetUniforms() {
		isSetModelMatrix = isSetViewMatrix = isSetMVPMatrix = isSetNormalMatrix
		= isSetLightsNumber = isSetLightIntensity = isSetLightPosition = false;
	}

	//atrybuty
	GLuint vertexPosition_modelspaceID;
	GLuint vertexColourID;
	GLuint vertexNormal_modelspaceID;

	//TODO: uniform template (o ile sie da)
	// uniformy
	bool isSetModelMatrix = false;
	Transformation_t modelMatrixCache;
	GLuint modelMatrixID;
	virtual void setModelMatrix(Transformation_t val) {
		if(!isSetModelMatrix || modelMatrixCache != val) {
			isSetModelMatrix = true;
			modelMatrixCache = val;
			glUniformMatrix4fv(modelMatrixID,1,GL_FALSE,&modelMatrixCache[0][0]);
		}
	}

	bool isSetViewMatrix = false;
	Transformation_t viewMatrixCache;
	GLuint viewMatrixID;
	virtual void setViewMatrix(Transformation_t val) {
		if(!isSetViewMatrix || viewMatrixCache != val) {
			isSetViewMatrix = true;
			viewMatrixCache = val;
			glUniformMatrix4fv(viewMatrixID,1,GL_FALSE,&viewMatrixCache[0][0]);
		}
	}

	bool isSetMVPMatrix = false;
	Transformation_t MVPMatrixCache;
	GLuint MVPMatrixID;
	virtual void setMVPMatrix(Transformation_t val) {
		if(!isSetMVPMatrix || MVPMatrixCache != val) {
			isSetMVPMatrix = true;
			MVPMatrixCache = val;
			glUniformMatrix4fv(MVPMatrixID,1,GL_FALSE,&MVPMatrixCache[0][0]);
		}
	}

	bool isSetNormalMatrix = false;
	Transformation_t normalMatrixCache;
	GLuint normalMatrixID;
	virtual void setNormalMatrix(Transformation_t val) {
		if(!isSetNormalMatrix || normalMatrixCache != val) {
			isSetNormalMatrix = true;
			normalMatrixCache = val;
			glUniformMatrix4fv(normalMatrixID,1,GL_FALSE,&normalMatrixCache[0][0]);
		}
	}

	bool isSetLightsNumber = false;
	GLuint lightsNumberCache;
	GLuint lightsNumberID;
	virtual void setLightsNumber(GLuint val) {
		assert(val <= LightsNumberMax);
		if(!isSetLightsNumber || lightsNumberCache != val) {
			isSetLightsNumber = true;
			lightsNumberCache = val;
			glUniform1i(lightsNumberID,lightsNumberCache);
		}
	}

	bool isSetLightIntensity = false;
	Colour_t lightIntensityCache[LightsNumberMax];
	GLuint lightIntensityID;
	virtual void setLightIntensity(Colour_t* intensities,GLuint size) {
		assert(size <= LightsNumberMax);
		bool shouldSend = false;
		if(!isSetLightIntensity) shouldSend = true;
		for(GLuint i=0 ; i < size ; i++)
			if(intensities[i] != lightIntensityCache[i]) {
				lightIntensityCache[i] = intensities[i];
				shouldSend = true;
			}
		isSetLightIntensity = true;
		if(shouldSend) {
			glUniform3fv(lightIntensityID,size,&lightIntensityCache[0][0]);
		}
	}

	bool isSetLightPosition = false;
	Position_t lightPositionCache[LightsNumberMax];
	GLuint lightPositionID;
	virtual void setLightPosition(Position_t* pos,GLuint size) {
		assert(size <= LightsNumberMax);
		bool shouldSend = false;
		if(!isSetLightPosition) shouldSend = true;
		for(GLuint i=0 ; i < size ; i++)
			if(pos[i] != lightPositionCache[i]) {
				lightPositionCache[i] = pos[i];
				shouldSend = true;
			}
		isSetLightPosition = true;
		if(shouldSend) {
			glUniform3fv(lightPositionID,size,&lightPositionCache[0][0]);
		}
	}
};

#endif