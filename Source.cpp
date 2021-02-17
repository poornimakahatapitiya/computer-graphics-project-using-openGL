#include"Header.h"
#include "Shader.h"
#include"texture.h"
#include"Mesh1.h"
Vertex vertices[] = {
	//position                   //color                             //texcoords       //normal
	glm::vec3(0.0f,0.5f,0.f),       glm::vec3(1.f,0.f,0.f),      glm::vec2(0.f,1.f),  glm::vec3(0.f,0.f,-1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),   glm::vec3(0.f,1.f,0.f),      glm::vec2(0.f,0.f),  glm::vec3(0.f,0.f,-1.f),
	glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),    glm::vec2(1.f,0.f),  glm::vec3(0.f,0.f,-1.f)

	
	
};
unsigned noOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
	0, 1, 2// vertices to create a triangle
	
};
unsigned noOfIndices = sizeof(indices) / sizeof(GLuint);
void updateInput(GLFWwindow*window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE && GLFW_PRESS)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
void frameBufferResize(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint &program) {
	bool loadSucess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream inFile;

	inFile.open("vertexCore.glsl");

	if (inFile.is_open()) {
		while (std::getline(inFile, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERRO::COULD NOT OPEN VERTEX FILE" << "\n";
	}
	inFile.close();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader,1,&vertSrc,NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::COULD NOT COMPILE  VERTEX SHADER" << "\n";
		std::cout << infoLog << "\n";
	}
	

	temp = "";
	src = "";

	//fragment

	inFile.open("fragmentCore.glsl");

	if (inFile.is_open()) {
		while (std::getline(inFile, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERRO::COULD NOT OPEN   FRAGMENT FILE" << "\n";
		loadSucess = false;
	}
	inFile.close();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERRO::COULD NOT LOAD  FRAGMENT SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSucess = false;
	}

	//program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);


	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERRO::COULD NOT LINK program" << "\n";
		std::cout << infoLog << "\n";
		loadSucess = false;
	}

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSucess;
}

void updateInput(GLFWwindow*window,glm::vec3 position,glm::vec3& rotation,glm::vec3& scale) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position.x +=0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		rotation.y -= 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		rotation.y += 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		scale += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		scale -= 0.1f;
	}
}
int main() {
	// init GLFW
	glfwInit();

	//create window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int frameBufferWidth = 0;
	int frameBufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
	glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Project window",NULL,NULL);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glfwSetFramebufferSizeCallback(window, frameBufferResize);
	
	//glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	glfwMakeContextCurrent(window);



	//init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw"Error in GLEW INIT";
		glfwTerminate();
		
	}

	//openGL_options
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//if want out line change fill to GL_LINE

	
	//shader
	Shader  core_program("vertexCore.glsl","fragmentCore.glsl");
	//mesh class
	Mesh test(vertices,noOfVertices,indices,noOfIndices);
	//Vertex array object
	GLuint VAO; 
	glCreateVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	//vertex buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// element buffer
	GLuint EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	
	//vertex pointers input assembly
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);


	glBindVertexArray(0);
	
	//texture init
    Texture texture_0("img/metal.png",GL_TEXTURE_2D,0);
	
	//texture2
	

	//Matrix translation
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);

	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix,position);
	//rotation
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x),glm::vec3(1.f,0.f,0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	//scale
	ModelMatrix = glm::scale(ModelMatrix, scale);

	//prespective projection
	glm::vec3 camPostion(0.f,0.f,1.f);
	glm::vec3 worldUp = glm::vec3(0.f,1.f,0.f);
	glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	
	ViewMatrix = glm::lookAt(camFront, camPostion + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);

	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight,nearPlane,farPlane);
	
	//lights
	glm::vec3 lightPos0(0.f, 0.f, 2.f);

	// init uniforms
	core_program.setMat4fv(ModelMatrix,"ModelMatrix");
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	
	core_program.setVec3f(lightPos0, "lightPos0");
	//core_program.setVec3f(camPostion,"camPos");
	

	// main
	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();
		updateInput(window, position, rotation, scale);
		updateInput(window);
		//update input
		
		
		
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// program
		
		// update uniforms
		core_program.set1i(texture_0.getTextureUnit(),"texture0");
		
		//animation
		

		//matrix move rotate
		ModelMatrix = glm::mat4(1.f);
		ModelMatrix = glm::translate(ModelMatrix, position);
		//rotation
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		//scale
		ModelMatrix = glm::scale(ModelMatrix, scale);
		core_program.setMat4fv(ModelMatrix, "ModelMatrix");
		

		//perspective projecction
		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
		

		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);
		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
		
		core_program.use();
		//activate texture
		texture_0.bind();
		
		//bind object array
		glBindVertexArray(VAO);

		//draw
		//glDrawArrays(GL_TRIANGLES,0,noOfVertices);
		//glDrawElements(GL_TRIANGLES, noOfIndices, GL_UNSIGNED_INT, 0);
		test.render(&core_program);
		glfwSwapBuffers(window);
		glFlush();
	}

	glfwTerminate();
	
	system("PAUSE");
	return 0;
}


	
	