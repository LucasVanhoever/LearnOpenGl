#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;
layout (location = 4) in mat4 instanceMatrix;

out vec3 crntPos;

out vec3 color;

out vec3 Normal;

out vec2 texCoord;



uniform mat4 camMatrix;

uniform float phi;
uniform float theta;


void main()
{
  vec3 tempPos = vec3(instanceMatrix * vec4(aPos,1.0f));
  vec3 chargePos1 = vec3(0.5f,0.0f ,0.5f);
  vec3 chargePos2 = vec3(0.1f*cos(phi)+0.5f,0.0f,0.1f*sin(phi)+0.5f);

  //crntPos = vec3(tempPos.x,1/((pow(tempPos.x-chargePos1.x,2)+pow(tempPos.y-chargePos1.y,2)+pow(tempPos.z-chargePos1.z,2))),tempPos.z) + vec3(tempPos.x,-1/((pow(tempPos.x-chargePos2.x,2)+pow(tempPos.y-chargePos2.y,2)+pow(tempPos.z-chargePos2.z,2))),tempPos.z);
  crntPos = tempPos;
  color = vec3(tempPos.x,1/((pow(tempPos.x-chargePos1.x,2)+pow(tempPos.y-chargePos1.y,2)+pow(tempPos.z-chargePos1.z,2))),tempPos.z) + vec3(tempPos.x,-1/((pow(tempPos.x-chargePos2.x,2)+pow(tempPos.y-chargePos2.y,2)+pow(tempPos.z-chargePos2.z,2))),tempPos.z);


  //gl_Position = camMatrix * vec4(crntPos, 1.0);
  gl_Position =camMatrix * vec4(tempPos, 1.0);
  gl_PointSize = 1;

  //color = aColor;
  Normal = aNormal;
  texCoord = aTex;
}