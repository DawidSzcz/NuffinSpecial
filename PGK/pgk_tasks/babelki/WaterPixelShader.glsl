#version 120

#define LIGHTS_NUM_MAX 12

// Interpolated values from the vertex shaders
varying vec3 Colour;
varying vec3 Position_worldspace;
varying vec3 Normal_cameraspace;
varying vec3 EyeDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 V;
uniform int LightsNumber;
uniform vec3 LightIntensity[LIGHTS_NUM_MAX];
uniform vec3 LightPosition_worldspace[LIGHTS_NUM_MAX];

void main(){
	gl_FragColor.rgb = vec3(0.16,0.16,0.16) * Colour;		// Ambient lighting

	for(int i=0 ; i < LightsNumber ; i++) {
		// distance to the light
		float distance = length( LightPosition_worldspace[i] - Position_worldspace );

		// Vector that goes from the vertex to the light, in camera space.
		vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace[i],1)).xyz;
		vec3 LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

		// Normal of the computed fragment, in camera space
		vec3 n = normalize( Normal_cameraspace );
		// Direction of the light (from the fragment to the light)
		vec3 l = normalize( LightDirection_cameraspace );
		// Cosine of the angle between the normal and the light direction
		float cosTheta = clamp( dot( n,l ), 0,1 );
		
		// Eye vector (towards the camera)
		vec3 E = normalize(EyeDirection_cameraspace);
		// Direction in which the triangle reflects the light
		vec3 R = reflect(-l,n);
		// Cosine of the angle between the Eye vector and the Reflect vector
		float cosAlpha = clamp( dot( E,R ), 0,1 );

		gl_FragColor.rgb += (
			Colour * cosTheta						// Diffuse lighting
			+ vec3(0.3,0.3,0.3) * pow(cosAlpha,7)	// Specular lighting
		) * LightIntensity[i]/(distance+50.0);
	}

	// imo lepiej wygladajace, ale wtedy musialbym zmieniac shader przy zmianie widoku, bo z daleka g*no widac
	float len = clamp(length(EyeDirection_cameraspace),0,220);
	float rate = 0.000025*pow(len+10,1);
	rate /= 0.000025*pow(110,1);
	if (rate > 1) rate = 1;

	//float len = clamp(length(EyeDirection_cameraspace),0,70);
	//float rate = 0.001*pow(len+10,2);
	gl_FragColor.rgb = (gl_FragColor.rgb*(1-rate) + vec3(0,0.08,0.25) * rate);
	
	
	//gl_FragColor.rgb = (gl_FragColor.rgb + vec3(0,0.08,0.25) * rate) / (1+rate);
}