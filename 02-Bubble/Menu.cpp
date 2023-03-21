#include "Menu.h"

Menu::Menu()
{
	this->spriteMenu = NULL;


}

Menu::~Menu()
{
	if (this->spriteMenu != NULL) delete this->spriteMenu;


}

void Menu::init() {

	this->initShader();
	projection = glm::ortho(0.f, float(800), float(750), 0.f);
	this->textureMenu.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteMenu = Sprite::createSprite(glm::ivec2(800, 750), glm::vec2(1.f, 1.f), &this->textureMenu, &this->shader);
	this->spriteMenu->setNumberAnimations(0);
	this->spriteMenu->setPosition(glm::vec2(0.f, 0.f));
	textureCursor.loadFromFile("images/cursor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cursor = Sprite::createSprite(glm::ivec2(100, 100), glm::vec2(1.0f, 1.0f), &textureCursor, &shader);
	cursor->setPosition(glm::vec2(250.0f, 300.0f));
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



