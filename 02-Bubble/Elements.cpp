#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Elements.h"

enum animElem {
	DEFAULT
};

void Elements::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, int element) {
	spritesheet.loadFromFile("images/Objectes/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	size.x = 50;
	size.y = 45;
	sprite->setAnimationSpeed(DEFAULT, 6);
	sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

	sprite->changeAnimation(0);
}

Elements::~Elements()
{
}

void Elements::update(int deltaTime) {
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(posElem.x), float(posElem.y)));
}

void Elements::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

void Elements::setPosition(const glm::vec2& pos) {
	posElem = pos;
	sprite->setPosition(glm::vec2(float(posElem.x), float(posElem.y)));
}

glm::vec2 Elements::ret_pos() {
	return posElem;
}

glm::vec2 Elements::ret_size() {
	return size;
}

void Elements::render()
{
	sprite->render();
}
