#version 460 core

out vec4 FragColor;

in vec3 crntPos;

in vec3 color;

in vec3 Normal;


in vec2 texCoord;



uniform sampler2D renderedTexture;




 

void main()
{

	FragColor = texture(renderedTexture, texCoord);
	//FragColor = vec4(1.0,0.5,0.3,1.0);
}