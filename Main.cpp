
#include "Object.h"


const int width = 1400;
const int height = 1400;

const int numObjectsx = 1;
const int numObjectsy = 1;
const int numObjectsz = 1;

float xscale = 2.0f;
float yscale = 2.0f;
float zscale = 1.0f;

/*
Vertex vertices[] =
{//	POSITION					COLOR					NORMAL						TEXTURE
	glm::vec3(-0.5f,  0.0f,  0.0f),		glm::vec3(0.0f, 0.5f, 1.0f),		 glm::vec3( - 0.5f,  0.0f,   0.0f),			glm::vec2(0.0f,0.0f),
	glm::vec3( 0.0f,  0.5f,  0.0f),		glm::vec3(0.0f, 0.5f, 1.0f),		 glm::vec3(0.0f,  0.5f,   0.0f),			glm::vec2(0.0f,1.0f),
	glm::vec3( 0.5f,  0.0f,  0.0f),		glm::vec3(0.5f, 1.0f, 1.0f),		 glm::vec3(0.5f,  0.0f,  0.0f),			    glm::vec2(1.0f,1.0f),
	glm::vec3( 0.0f, -0.5f,  0.0f),		glm::vec3(0.0f, 0.0f, 1.0f),         glm::vec3(0.0f, -0.5f,   0.0f),			glm::vec2(1.0f,0.0f),
	glm::vec3( 0.0f,  0.0f,  0.5f),		glm::vec3(0.0f, 1.0f, 0.5f),		 glm::vec3(0.0f,  0.0f,   0.5f),			glm::vec2(0.5f,0.5f),
	glm::vec3( 0.0f,  0.0f, -0.5f),		glm::vec3(0.0f, 1.0f, 0.0f),		 glm::vec3(0.0f,  0.0f,  -0.5f),			glm::vec2(0.5f,0.5f),
};

GLuint indices[] =
{
	3, 4, 0,
	3, 4, 2,
	3, 5, 0,
	3, 5, 2,
	1, 4, 0,
	1, 4, 2,
	1, 5, 0,
	1, 5, 2

};
*/


//SQUARE
Vertex Screenvertices[] =
{//	POSITION					COLOR					NORMAL						TEXTURE
	glm::vec3(-1.0f, -1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 1.0f),		 glm::vec3(-0.5f,  0.0f,   0.0f),			glm::vec2(0.0f,0.0f),
	glm::vec3(1.0f,  -1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 1.0f),		 glm::vec3(0.0f,  0.5f,   0.0f),			glm::vec2(1.0f,0.0f),
	glm::vec3(1.0f,  1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 1.0f),		 glm::vec3(0.5f,  0.0f,  0.0f),			    glm::vec2(1.0f,1.0f),
	glm::vec3(-1.0f, 1.0f,  0.0f),		glm::vec3(1.0f, 1.0f, 1.0f),         glm::vec3(0.0f, -0.5f,   0.0f),			glm::vec2(0.0f,1.0f),
};

GLuint Screenindices[] =
{
	1, 0, 3, // Upper triangle
	1, 2, 3 // Lower triangle
};

const int subdivisions = 1;
Vertex vertices[((subdivisions + 1) * (subdivisions + 1))];




int main()
{
	int vertindex = 0;
	for (float j = 0; j < subdivisions + 1; j++)
	{
		for (float i = 0; i < subdivisions + 1; i++)
		{
			vertices[vertindex].position = glm::vec3(((i/subdivisions) * xscale)-1, ((j/subdivisions) * yscale)-1, 0.0f);
			vertices[vertindex].color = glm::vec3(1.0f, 1.0f, 1.0f);
			vertices[vertindex].normal = glm::vec3(0.0f, 0.0f, -1.0f);
			vertices[vertindex].texUV = glm::vec2(i / subdivisions, j / subdivisions);
			vertindex++;
		}
	}

	std::vector <GLuint> ind;
	for (int i = 0; i < (((subdivisions+1) * (subdivisions+1))-(subdivisions+1)); i++)
	{
		if (i % (subdivisions +1) != 0)
		{
			ind.push_back(i);
			ind.push_back(i - 1);
			ind.push_back((i -1)+ (subdivisions + 1));


			ind.push_back(i);
			ind.push_back(i + (subdivisions + 1));
			ind.push_back((i-1) + (subdivisions + 1));

		}

	}
	
	int numObjects = numObjectsx * numObjectsy * numObjectsz;

	//this block of code handles starting the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //defines version we are using 3.3 so use 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); //defines verson... again
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //defines profile which is the functions we have
	GLFWwindow* window = glfwCreateWindow(width, height, "MyWindow", NULL, NULL); //create a window
	if (window == NULL) //error checking
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);  //make the context our current window



	gladLoadGL(); //puts opengl into the window

	glViewport(0, 0, width, height);		//set viewport to be size of window

		

	

	Shader shaderProgram("default.vert", "default.frag");
	Shader InstanceShader("defaultinstanced.vert", "default.frag");
	Shader TextureShader("TextureVert.vert", "TextureFrag.frag");
	Shader TextureInstanceShader("TextureVertInstanced.vert", "TextureFragInstanced.frag");
	Shader InterShader("intervert.vert", "interfrag.frag");
	/*
	Texture textures[]
	{
		Texture("Textures/obamasquare.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE)
	};
	*/


	//std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector <Texture> tex;
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	
	std::vector <GLuint> screenind(Screenindices, Screenindices + sizeof(Screenindices) / sizeof(GLuint));;
	std::vector <Texture> screentex;
	std::vector <Vertex> screenverts(Screenvertices, Screenvertices + sizeof(Screenvertices) / sizeof(Vertex));

	std::vector <glm::vec3> startingpos;
	for (float i = 0; i < numObjectsx; i++)
	{
		for (float j = 0; j < numObjectsy; j++)
		{
			for (float k = 0; k < numObjectsz; k++)
			{
				float xpos = (i / numObjectsx) * xscale;
				float ypos = (j / numObjectsy) * yscale;
				float zpos = (k / numObjectsz) * zscale;
				startingpos.push_back(glm::vec3(xpos, ypos, zpos ));
			}
		}

	}

	

	
	GLuint Framebuffer1;
	GLuint Framebuffer2;
	glGenFramebuffers(1, &Framebuffer1);
	glGenFramebuffers(1, &Framebuffer2);
	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer1);
	glViewport(0, 0, width, height);
	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);
	GLuint inputTexture;
	glGenTextures(1, &inputTexture);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	

	// Poor filtering. Needed !
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers1[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers1); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "FUCK\n";
		return false;
	}
		

	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer2);
	glBindTexture(GL_TEXTURE_2D, inputTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, inputTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers2[1] = { GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(1, DrawBuffers2); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "FUCK\n";
		return false;
	}
	glViewport(0, 0, width, height);
	

	

	

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_POLYGON_SMOOTH);
	Object ObamaPrism(verts, ind, tex, startingpos, numObjects);

	Object TextureScreen(screenverts, screenind, screentex, startingpos, 1);
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 1.0f));

	

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);

	
	
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	







	double lastTime = glfwGetTime();
	double frameTime = glfwGetTime();
	int nbFrames = 0;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		double currentFrameTime = glfwGetTime();
		if ( currentFrameTime - frameTime >= 0.0166)
		{
			frameTime = currentFrameTime;
			
			glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer1);

			
			glBindTexture(GL_TEXTURE_2D, inputTexture);
			camera.Inputs(window);
			camera.updateMatrix(90.0f, 0.1f, 10000.0f);
			
			
			
		    TextureScreen.Draw(TextureShader, camera, GL_TRIANGLES);
		
			glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer2);
			//glBindTexture(GL_TEXTURE_2D, inputTexture);
			glBindTexture(GL_TEXTURE_2D, renderedTexture);
			glClearColor(0.f, 0.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

			camera.Inputs(window);
			camera.updateMatrix(90.0f, 0.1f, 10000.0f);



			TextureScreen.Draw(InterShader, camera, GL_TRIANGLES);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClearColor(0.f, 0.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (numObjects == 1)
			{
				ObamaPrism.Draw(shaderProgram, camera, GL_TRIANGLES);	
			}
			else
			{
				ObamaPrism.Draw(InstanceShader, camera, GL_TRIANGLES);	
			}
			glBindTexture(GL_TEXTURE_2D, inputTexture);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,0);
			glfwSwapBuffers(window);
			// Take care of all GLFW events
			glfwPollEvents();
			
		}



		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f fps\n", double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
	}



	// Delete all the objects we've created
	glDeleteFramebuffers(1, &Framebuffer1);
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	
	return 0;
}