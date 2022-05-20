#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;


out vec3 crntPos;

out vec3 color;

out vec3 Normal;

out vec2 texCoord;



uniform mat4 camMatrix;

uniform mat4 model;

uniform float phi;
uniform float theta;
uniform sampler2D renderedTexture;

void main()
{
  vec3 chargePos1 = vec3(0.0f,0.0f ,0.5f);
  vec3 chargePos2 = vec3(0.1f*cos(phi),0.1f*sin(phi),0.5f);
  vec4 pcolor = texture(renderedTexture,aTex);

  //crntPos = vec3(model * vec4(aPos,1.0f) + vec4(0.0f,0.0f,pcolor.z,0.0f));
  crntPos = vec3(model * vec4(aPos,1.0f));
  //crntPos = vec3(vec4(aPos,1.0f));
  //vec3 movedpos = vec3(crntPos.x,1/((pow(crntPos.x-chargePos1.x,2)+pow(crntPos.y-chargePos1.y,2)+pow(crntPos.z-chargePos1.z,2))),crntPos.z) + vec3(crntPos.x,-1/((pow(crntPos.x-chargePos2.x,2)+pow(crntPos.y-chargePos2.y,2)+pow(crntPos.z-chargePos2.z,2))),crntPos.z);

  gl_Position = camMatrix * vec4(crntPos, 1.0);
  //gl_Position = vec4(crntPos, 1.0);
  gl_PointSize = 1;

  color = aColor;
  Normal = aNormal;
  texCoord = aTex;
}