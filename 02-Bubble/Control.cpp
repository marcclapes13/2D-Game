#include "Control.h"

Control::Control()
{
	this->spriteControls = NULL;
}

Control::~Control()
{

	if (this->spriteControls != NULL) delete this->spriteControls;
}

void Control::init() {

	this->initShader();
	projection = glm::ortho(0.f, float(800), float(750), 0.f);
	this->textureControls.loadFromFile("images/Menus/controls.png", TEXTURE_PIXEL_FORMAT_RGBA);
	this->spriteControls = Sprite::createSprite(glm::ivec2(800, 750), glm::vec2(1.f, 1.f), &this->textureControls, &this->shader);
	this->spriteControls->setNumberAnimations(0);
	this->spriteControls->setPosition(glm::vec2(0.f, 0.f));

}
void Control::update(int deltaTime)
{
	this->spriteControls->update(deltaTime);
}
void Control::render()
{
	glm::mat4 modelview;

	this->shader.use();
	this->shader.setUniformMatrix4f("projection", projection);
	this->shader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	this->shader.setUniformMatrix4f("modelview", modelview);
	this->shader.setUniform2f("texCoordDispl", 0.f, 0.f);
	this->spriteControls->render();
}
void Control::initShader()
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
