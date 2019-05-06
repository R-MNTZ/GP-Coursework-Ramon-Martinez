#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void setShader3rd();
	void setShader();
	void processInput();
	void gameLoop();
	void drawGame();
	void update();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);


	void setUniform(Shader currentShader, const char *name, float x, float y, float z);
	void setUniform(Shader currentShader, const char *name, const glm::vec3 & v);
	void setUniform(GLuint currentShader, glm::vec4 values, const GLchar *uniformName, const GLchar *uniformVarialbeName);
	void setUniform(Shader currentShader, const char *name, const glm::mat4 & m);
	void setUniform(Shader currentShader, const char *name, const glm::mat3 & m);
	void setUniform(Shader currentShader, const char *name, float val);
	void setUniform(Shader currentShader, const char *name, int val);
	void setUniform(Shader currentShader, const char *name, bool val);
	void printActiveUniforms(Shader currentShader);
	void printActiveAttribs(Shader currentShader);

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Texture texture;
	Texture texture1;
	Texture texture2;
	Shader shaderPass;

	Camera myCamera;

	float counter;

	void Skybox();

	void setRef();

	GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	vector<std::string> faces;
	Texture skybox;
	Shader shaderSkybox;
	Shader shaderRef;
	Shader shader3rd;

	int switch1;

	float counterR;
	float counterG;
	float counterB;
	bool addR;
	bool subtractR;
	bool addG;
	bool subtractG;
	bool addB;
	bool subtractB;
	glm::vec3 lightPos;
	



};

