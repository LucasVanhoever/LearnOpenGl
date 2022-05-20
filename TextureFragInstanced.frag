#version 460 core

out vec4 FragColor;

in vec3 crntPos;

in vec3 color;

in vec3 Normal;


in vec2 texCoord;


uniform sampler2D tex0;

uniform sampler2D renderedTexture;

uniform vec4 lightColor;

uniform vec3 lightPos;

uniform vec3 camPos;




void main()
{
	vec3 CustomColor = normalize(vec3(color.y+1.0f,1.0f,-color.y+1.0f));
	FragColor = vec4(CustomColor,1.0f);
	//FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}