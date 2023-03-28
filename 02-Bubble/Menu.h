#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE



#include "ShaderProgram.h"
#include "Sprite.h"
#include "Texture.h"


#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

#include <iostream>
#include <string>


class Menu
{
public:
	enum class State { MENU, CONTR, CRED, END };

public:

	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();


private:

	void initShader();



private:

	Sprite* spriteMenu;
	Sprite* cursor;


	Texture textureMenu;
	Texture textureCursor;
	Texture textureControls;
	Texture textureCredits;
	Texture textureCongrats;
	glm::mat4 projection;
	ShaderProgram shader;
	Texture scene;
	glm::vec2 selectorPos = glm::vec2(50.f, 50.f);
};


#endif // _MENU_INCLUDE
