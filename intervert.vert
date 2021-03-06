#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;


out vec3 crntPos;

out vec3 color;

out vec3 Normal;

out vec2 texCoord;


void main()
{

  crntPos = vec3(vec4(aPos,1.0f));
  gl_Position = vec4(crntPos, 1.0);
  gl_PointSize = 1;

  color = aColor;
  Normal = aNormal;
  texCoord = aTex;
}
