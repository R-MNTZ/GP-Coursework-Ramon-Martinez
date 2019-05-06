#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>
using namespace std;


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
}

MainGame::~MainGame() 
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 

	texture.init("..\\res\\gradient.jpg"); //load texture
	texture1.init("..\\res\\water.jpg"); //load texture
	texture2.init("..\\res\\bricks.jpg");

	shaderPass.init("..\\res\\shaderGeoText.vert", "..\\res\\shaderGeoText.frag", "..\\res\\shaderGeoText.geom");
	shaderSkybox.init2("..\\res\\shaderSkybox.vert", "..\\res\\shaderSkybox.frag");
	shaderRef.init2("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	shader3rd.init2("..\\res\\shader3rd.vert", "..\\res\\shader3rd.frag");
	//Vertex2D vertices[] = { Vertex2D(glm::vec2(-0.5, 1.0), glm::vec2(0.0, 0.0)),
	//						Vertex2D(glm::vec2(0.5, 0.5), glm::vec2(1.0, 0.0)),
	//						Vertex2D(glm::vec2(0.5,-0.5), glm::vec2(1.0, 1.0)),
	//						Vertex2D(glm::vec2(-0.5,-0.5), glm::vec2(0.0, 1.0)) };


	mesh1.loadModel("..\\res\\cube.obj");
	mesh2.loadModel("..\\res\\candyCane.obj");
	mesh3.loadModel("..\\res\\monkey3.obj");
	
	myCamera.initCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
	switch1 = 0;
	counterR = 0;
	counterG = 0;
	counterB = 0;
	addR, addB, addG = true;
	subtractR, subtractG, subtractB = false;

	
	

	//Skybox stuff
	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};

	cubemapTexture = skybox.loadCubemap(faces); //Load the cubemap using "faces" into cubemapTextures

	float skyboxVertices[] = {
		// positions          
		-6.0f,  6.0f, -6.0f,
		-6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		-6.0f,  6.0f, -6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		6.0f, -6.0f,  6.0f
	};

	//use openGL functionality to generate & bind data into buffers
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}

void MainGame::setShader3rd() {
	shader3rd.setMat4("transform", transform.GetModel());
	shader3rd.setInt("switch1", switch1);
	shader3rd.setFloat("counterR", counterR);
	shader3rd.setFloat("counterG", counterG);
	shader3rd.setFloat("counterB", counterB);
	shader3rd.setMat4("view", myCamera.GetView());
	shader3rd.setMat4("projection", myCamera.GetProjection());
	shader3rd.setVec3("lightColor", 1.0f, 0.0f, 0.0f);
	shader3rd.setVec3("lightPos", lightPos);
	shader3rd.setVec3("cameraPos", myCamera.getPos());
	
	
}



void MainGame::setShader() {
	shaderPass.setMat4("transform", transform.GetModel());
	//shaderPass.setFloat("randColourX", 1.0);
	//shaderPass.setFloat("randColourY", 0.5);
	//shaderPass.setFloat("randColourZ", 0.5);
	shaderPass.setFloat("time", 0.1f + (counter*5.0f));
}

void MainGame::Skybox()
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.Bind();
	shaderSkybox.setInt("skybox", 0);
	//view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", myCamera.GetView());
	shaderSkybox.setMat4("projection", myCamera.GetProjection());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void MainGame::setRef()
{
	shaderRef.setMat4("model", transform.GetModel());
	shaderRef.setMat4("view", myCamera.GetView());
	shaderRef.setMat4("projection", myCamera.GetProjection());
	shaderRef.setVec3("cameraPos", myCamera.getPos());
	shaderRef.setInt("skybox", 0);
}



void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		update();
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_KEYDOWN: //Keyboard input to change effect
			if (evnt.key.keysym.sym == SDLK_d) {
				switch1++;

				if (switch1 > 7) {
					switch1 = 7;
				}

			}
			if (evnt.key.keysym.sym == SDLK_a) {

				switch1--;

				if (switch1 < 0) {
					switch1 = 0;
				}

			}
			

			break;

			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::printActiveUniforms(Shader currentShader)
{
	GLint maxLength, nAttribs;
	glGetProgramiv(currentShader.getProgram(), GL_ACTIVE_ATTRIBUTES, &nAttribs);
	glGetProgramiv(currentShader.getProgram(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

	GLchar * name = (GLchar *)malloc(maxLength);

	GLint written, size, location;
	GLenum type; printf(" Index | Name\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < nAttribs; i++)
	{
		glGetActiveAttrib(currentShader.getProgram(), i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(currentShader.getProgram(), name);
		printf(" %-5d | %s\n", location, name);
	}
	free(name);
}

void MainGame::printActiveAttribs(Shader currentShader)
{
	GLint nUniforms, maxLen;

	glGetProgramiv(currentShader.getProgram(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
	glGetProgramiv(currentShader.getProgram(), GL_ACTIVE_UNIFORMS, &nUniforms);

	GLchar * locationName = (GLchar *)malloc(maxLen);

	GLint uniformSize, uniformLocation;
	GLsizei writtenU; GLenum typeU; printf(" Location | Name\n");
	printf("------------------------------------------------\n");
	for (int i = 0; i < nUniforms; ++i)
	{
		glGetActiveUniform(currentShader.getProgram(), i, maxLen, &writtenU, &uniformSize, &typeU, locationName);
		uniformLocation = glGetUniformLocation(currentShader.getProgram(), locationName);
		printf(" %-8d | %s\n", uniformLocation, locationName);
	}
	free(locationName);
}


void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);


	transform.SetPos(glm::vec3(sinf(counter), 2.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shaderRef.Bind();
	setRef();
	shaderRef.Update(transform, myCamera);
	texture.Bind(0);
	//mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.62f);
	 
	

	transform.SetPos(glm::vec3(-sinf(counter), -1.0, -sinf(counter)*5));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shaderPass.Bind();
	setShader();


	shaderPass.Update(transform, myCamera);
	texture2.Bind(0);
	//mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);
	
	lightPos = glm::vec3(0.0f , -sinf(counter) * 4.0, 0.0f);
	transform.SetPos(glm::vec3(-sinf(counter), -sinf(counter), -sinf(counter)));
	transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	shader3rd.Bind();
	setShader3rd();
	shader3rd.Update(transform, myCamera);
	texture.Bind(0);
	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);

Skybox();
	

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 

void MainGame::update()
{
	
	counter = counter + 0.001f;

	counterR = abs(cosf(counter));
	counterG = abs(sinf(counter));
	counterB = abs(cosf(-counter));
	/*
	if (addR) {
		counterR += 0.01f;
	}
	else if (subtractR) {
		counterR -= 0.015f;
	}
	
	if (counterR > 0.99) {
		addR = false;
		subtractR = true;
	}
	else if (counterR < 0.01) {
		addR = true;
		subtractR = false;
	}

	if (addG) {
		counterG += 0.0024f;
	}
	else if (subtractG) {
		counterG -= 0.0027f;
	}

	if (counterG > 0.99) {
		addG = false;
		subtractG = true;
		
	}
	else if (counterG < 0.01) {
		addG = true;
		subtractG = false;
		
	}

	if (addB) {
		counterB += 0.00041f;
	}
	else if (subtractB) {
		counterB -= 0.00038f;
	}

	if (counterB > 0.99) {
		addB = false;
		subtractB = true;
		
	}
	else if (counterB < 0.01) {
		addB = true;
		subtractB = false;
		
	}
	*/
}