#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;
attribute vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
varying vec3 Normal_cameraspace;
varying vec2 UV;
varying vec3 EyeDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat4 NormalMatrix; // inverse transpose of a MV

void main(){
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	UV = vertexUV;
	Normal_cameraspace = (NormalMatrix * vec4(vertexNormal_modelspace,0)).xyz;
}

