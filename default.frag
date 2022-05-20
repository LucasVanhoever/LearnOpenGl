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
	//vec4 pcolor = texture(renderedTexture, texCoord);

	//FragColor = vec4(pcolor.x,pcolor.y,pcolor.z,pcolor.z);
	FragColor = texture(renderedTexture, texCoord);
}