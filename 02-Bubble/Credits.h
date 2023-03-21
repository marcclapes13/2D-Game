#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE



#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"


#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

#include <iostream>
#include <string>

class Credits
{
public:

public:

	Credits();
	~Credits();

	void init();
	void update(int deltaTime);
	void render();


private:

	void initShader();


private:


	Sprite* spriteCredits;

	Texture textureCredits;

	glm::mat4 projection;
	ShaderProgram shader;
	Texture scene;
};


#endif // _MENU_INCLUDE