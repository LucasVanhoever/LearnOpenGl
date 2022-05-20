#version 460 core

out vec4 FragColor;

in vec3 crntPos;

in vec3 color;

in vec3 Normal;

in vec2 texCoord;




//uniform sampler2D renderedTexture;

uniform sampler2D inputTexture;





uniform float phi;

uniform vec3 chargePos2;
vec3 customcolor;
const float offset = (1.0 / 1400.0); 
const int KernalSize = 1;

ivec2 offsets[((KernalSize*2)+1)*((KernalSize*2)+1)];
//vec3 kernel[((KernalSize*2)+1)*((KernalSize*2)+1)];

vec3 sampleTex[((KernalSize*2)+1)*((KernalSize*2)+1)];

void main()
{
	vec4 previousFrame =  max(vec4(0.0,0.0,0.0,0.0),texture(inputTexture,texCoord));
	vec3 chargePos1 = vec3(0.0,0.0,0.0);
	//vec3 chargePos2 = vec3(0.5*cos(phi) ,0.5*sin(phi*2),0.1*sin(phi*2));
	
	int kindex = 0;
	float kMag = 0;
	float kDecayFactor = 0.7;

	
	for(int r = -KernalSize; r < KernalSize+1;r++)
	{
		for(int c = -KernalSize; c < KernalSize+1; c++)
		{

			offsets[kindex] = ivec2(c,r);
			kMag = ((KernalSize*2)+1)*((KernalSize*2)+1);

			
			if(r == 0 && c == 0)
			{
				//kernel[kindex] = vec3(kDecayFactor/kMag,kDecayFactor/kMag,kDecayFactor/kMag);
			}
			else
			{
				//kernel[kindex] = vec3(1.0/kMag,1.0/kMag,1.0/kMag);
			}
			kindex++;
		}
	}
	
	vec3 kernel[9] = vec3[](
        vec3(0,0,0),   vec3(0.25,0.25,0.27),  vec3(0,0,0.25),
        vec3(0.25,0.25,0.25),   vec3(-0.5,-0.5,-0.5), vec3(0.25,0.26,0.25),
        vec3(0.25,0,0),   vec3(0.26,0.25,0.25), vec3(0,0.25,0)
    );
	

    for(int i = 0; i < ((KernalSize*2)+1)*((KernalSize*2)+1); i++)
    {
        sampleTex[i] = vec3(textureOffset(inputTexture, texCoord,offsets[i]));
    }


  vec3 col = vec3(0.0);
  
  for(int i = 0; i < (((KernalSize*2)+1)*((KernalSize*2)+1)); i++)
  {
    col += sampleTex[i] * kernel[i];
  }
  
  if(col.x < 0 || col.x > 1.0)
  {
       col.z = 0.0;
	   col.y = 0.0;
	   col.x -= 0.5;
  }
  if(col.y < 0 || col.y > 1.0)
  {
      col.z = 0.0;
	  col.x = 0.0;
	  col.y -= 0.5;
  }
  if(col.z < 0 || col.z > 1.0)
  {
       col.x = 0.0;
	   col.y = 0.0;
	   col.z -=0.5;
  }
  
  col -= 0.001;

    if(distance(crntPos,chargePos2) < 0.1 && phi < 1)
   {
		customcolor = vec3(1.0,1.0f,1.0f);
		FragColor = vec4(customcolor,1.0f);
	}
	else
	{
		customcolor = vec3(0.0f,0.0f,0.0f);
		//FragColor = vec4(customcolor,1.0f) + vec4(previousFrame.x-0.007,previousFrame.y-0.006f,previousFrame.z-0.005f,0.0f);
		FragColor = vec4(customcolor,1.0f) + vec4(col,0.0f);
	}

}