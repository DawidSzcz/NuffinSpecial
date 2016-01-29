#version 120

#define LIGHTS_NUM_MAX 12

// Interpolated values from the vertex shaders
varying vec3 Normal_cameraspace;
varying vec2 UV;
varying vec3 EyeDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 V;
uniform sampler2D TextureSampler;

void main(){
	vec3 Color = texture2D(TextureSampler,UV).rgb;
	vec3 LightIntensity = vec3(2,2,2);
	vec3 LightDirection_cameraspace = normalize( (V * vec4(1,1,1,0)).xyz );

	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);
	float cosTheta = clamp( dot(n,l), 0,1 );
	
	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R = reflect(-l,n);
	float cosAlpha = clamp( dot(E,R), 0,1 );

	gl_FragColor.rgb = vec3(0.16,0.16,0.16) * Color;	// Ambient lighting
	gl_FragColor.rgb += (
		Color * cosTheta						// Diffuse lighting
		+ vec3(0.3,0.3,0.3) * pow(cosAlpha,20)	// Specular lighting
	) * LightIntensity;
}