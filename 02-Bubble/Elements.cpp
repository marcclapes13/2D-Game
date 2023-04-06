#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Elements.h"

enum animElem {
	DEFAULT
};

void Elements::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, int element) {
	
	if (element == 0) {
		spritesheet.loadFromFile("images/Objectes/Key.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(36, 36), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);
		size.x = 50;
		size.y = 45;
		sprite->setAnimationSpeed(DEFAULT, 6);
		sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

		sprite->changeAnimation(0);
	}
	else if (element == 1) {
		spritesheet.loadFromFile("images/Objectes/StopTime.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(28, 28), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);
		size.x = 50;
		size.y = 45;
		sprite->setAnimationSpeed(DEFAULT, 6);
		sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

		sprite->changeAnimation(0);
	}
	else if (element == 2) {
		spritesheet.loadFromFile("images/Objectes/Invulnerable.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(28, 28), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);
		size.x = 50;
		size.y = 45;
		sprite->setAnimationSpeed(DEFAULT, 6);
		sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

		sprite->changeAnimation(0);
	}
	else if (element == 3) {
		spritesheet.loadFromFile("images/Objectes/Gema.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(22, 22), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);
		size.x = 50;
		size.y = 45;
		sprite->setAnimationSpeed(DEFAULT, 6);
		sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

		sprite->changeAnimation(0);
	}
	else if (element == 4) {
		spritesheet.loadFromFile("images/Objectes/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33f, 0.25f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(12);
		size.x = 50;
		size.y = 45;
		sprite->setAnimationSpeed(0, 6);
		sprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));

		sprite->setAnimationSpeed(1, 6);
		sprite->addKeyframe(1, glm::vec2(0.0f, 0.25f));

		sprite->setAnimationSpeed(2, 6);
		sprite->addKeyframe(2, glm::vec2(0.0f, 0.5f));

		sprite->setAnimationSpeed(3, 6);
		sprite->addKeyframe(3, glm::vec2(0.0f, 0.75f));

		sprite->setAnimationSpeed(4, 6);
		sprite->addKeyframe(4, glm::vec2(0.33f, 0.0f));

		sprite->setAnimationSpeed(5, 6);
		sprite->addKeyframe(5, glm::vec2(0.33f, 0.25f));

		sprite->setAnimationSpeed(6, 6);
		sprite->addKeyframe(6, glm::vec2(0.33f, 0.5f));

		sprite->setAnimationSpeed(7, 6);
		sprite->addKeyframe(7, glm::vec2(0.33f, 0.75f));

		sprite->setAnimationSpeed(8, 6);
		sprite->addKeyframe(8, glm::vec2(0.66f, 0.0f));

		sprite->setAnimationSpeed(9, 6);
		sprite->addKeyframe(9, glm::vec2(0.66f, 0.25f));

		sprite->setAnimationSpeed(10, 6);
		sprite->addKeyframe(10, glm::vec2(0.66f, 0.5f));

		sprite->setAnimationSpeed(11, 6);
		sprite->addKeyframe(11, glm::vec2(0.66f, 0.75f));

		sprite->changeAnimation(0);
	}
	else {
		spritesheet.loadFromFile("images/Objectes/vida.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(1);
		size.x = 50;
		size.y = 45;
		sprite->setAnimationSpeed(DEFAULT, 6);
		sprite->addKeyframe(DEFAULT, glm::vec2(0.0f, 0.0f));

		sprite->changeAnimation(0);
	}

	
	
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

void Elements::setPorta0() {
	sprite->changeAnimation(0);
}
void Elements::setPorta1() {
	sprite->changeAnimation(1);
}
void Elements::setPorta2() {
	sprite->changeAnimation(2);
}
void Elements::setPorta3() {
	sprite->changeAnimation(3);
}
void Elements::setEntry1() {
	sprite->changeAnimation(4);
}
void Elements::setEntry2() {
	sprite->changeAnimation(5);
}
void Elements::setEntry3() {
	sprite->changeAnimation(6);
}
void Elements::setEntry4() {
	sprite->changeAnimation(7);
}
void Elements::setEntry5() {
	sprite->changeAnimation(8);
}
void Elements::setEntry6() {
	sprite->changeAnimation(9);
}
void Elements::setEntry7() {
	sprite->changeAnimation(10);
}
void Elements::setEntry8() {
	sprite->changeAnimation(11);
}