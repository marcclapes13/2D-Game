#include "Menu.h"
#include <cmath>
#include <ctime>

enum Cursor{
	NORMAL, SELECT
};

void delay(int secs) {
	for (int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

Menu::Menu()
{
	this->spriteMenu = NULL;
	cursor = NULL;
	cursorPosition.x = 0;
	cursorPosition.y = 0;
}

Menu::~Menu()
{
	if (this->spriteMenu != NULL) delete this->spriteMenu;


}

void Menu::init() {

	this->initShader();
	projection = glm::ortho(0.f, float(800), float(750), 0.f);
	this->textureMenu.loadFromFile("images/Menus/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteMenu = Sprite::createSprite(glm::ivec2(800, 750), glm::vec2(1.f, 1.f), &this->textureMenu, &this->shader);
	this->spriteMenu->setNumberAnimations(0);
	this->spriteMenu->setPosition(glm::vec2(0.f, 0.f));
	textureCursor.loadFromFile("images/cursor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cursor = Sprite::createSprite(glm::ivec2(120, 100), glm::vec2(1.f, 0.5f), &textureCursor, &shader);
	cursor->setNumberAnimations(2);

	cursor->setAnimationSpeed(NORMAL, 8);
	cursor->addKeyframe(NORMAL, glm::vec2(0.0f, 0.5f));

	cursor->setAnimationSpeed(SELECT, 8);
	cursor->addKeyframe(SELECT, glm::vec2(0.0f, 0.f));

	cursor->changeAnimation(0);

	cursorPosition.x = 220.f;
	cursorPosition.y = 300.f;
	cursor->setPosition(cursorPosition);
}

void Menu::update(int deltaTime)
{

	this->spriteMenu->update(deltaTime);
	cursor->update(deltaTime);
}
void Menu::render()
{
	glm::mat4 modelview;

	this->shader.use();
	this->shader.setUniformMatrix4f("projection", projection);
	this->shader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	this->shader.setUniformMatrix4f("modelview", modelview);
	this->shader.setUniform2f("texCoordDispl", 0.f, 0.f);
	this->spriteMenu->render();
	cursor->render();
}

void Menu::initShader()
{
	Shader vShader;
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		std::cout << "Vertex Shader Error" << std::endl;
		std::cout << "" << vShader.log() << std::endl << std::endl;
	}

	Shader fShader;
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		std::cout << "Fragment Shader Error" << std::endl;
		std::cout << "" << fShader.log() << std::endl << std::endl;
	}

	this->shader.init();
	this->shader.addShader(vShader);
	this->shader.addShader(fShader);
	this->shader.link();
	if (!this->shader.isLinked())
	{
		std::cout << "Shader Linking Error" << std::endl;
		std::cout << "" << this->shader.log() << std::endl << std::endl;
	}
	this->shader.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
}

void Menu::cursorPlay() {
	cursorPosition.x = 220.f;
	cursorPosition.y = 300.f;
	cursor->setPosition(cursorPosition);
}

void Menu::cursorControl() {
	cursorPosition.x = 220.f;
	cursorPosition.y = 430.f;
	cursor->setPosition(cursorPosition);
}

void Menu::cursorCredits() {
	cursorPosition.x = 220.f;
	cursorPosition.y = 560.f;
	cursor->setPosition(cursorPosition);
}

glm::ivec2 Menu::cursorPos() {
	return glm::ivec2(cursorPosition.x,cursorPosition.y);
}

void Menu::cursorSetSelect() {
	cursor->changeAnimation(SELECT);
	
}


