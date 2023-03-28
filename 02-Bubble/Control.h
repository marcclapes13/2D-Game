#ifndef _CONTROL_INCLUDE
#define _CONTROL_INCLUDE



#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"


#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

#include <iostream>
#include <string>

class Control
{
public:

public:

	Control();
	~Control();

	void init();
	void update(int deltaTime);
	void render();


private:

	void initShader();


private:


	Sprite* spriteControls;

	Texture textureControls;

	glm::mat4 projection;
	ShaderProgram shader;
	Texture scene;
	glm::vec2 selectorPos = glm::vec2(50.f, 50.f);
};


#endif // _MENU_INCLUDE

