#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"



enum anim
{
	MOVE_RIGHT, MOVE_LEFT
};


void Bullet::createBullet(float posx, float posy, int direction, ShaderProgram& shaderProgram, float speedy) {
	dir = direction;
	posBullet = glm::vec2(float(posx), float(posy));
	speed = speedy;
	size.x = 8;
	size.y = 8;
	spritesheet.loadFromFile("images/Objectes/bala.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 4), glm::vec2(0.5f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.0f));
	if (dir == 1)
		sprite->changeAnimation(MOVE_RIGHT);

	else
		sprite->changeAnimation(MOVE_LEFT);
	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
}

void Bullet::update(int deltaTime) {
	switch (dir) {
	case (0):
		
		posBullet.x -= 4 * speed;
		
		break;
	case (1):
		
		posBullet.x += 4 * speed;
		
		break;
	}
	sprite->update(deltaTime);
}

void Bullet::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bullet::render() {
	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
	sprite->render();
}

Bullet::~Bullet() {
	
}

glm::vec2 Bullet::ret_pos() {
	if (dir == 0)
		return glm::vec2(posBullet.x+8, posBullet.y);
	else 
		return glm::vec2(posBullet.x -8, posBullet.y);
}

glm::vec2 Bullet::ret_size() {
	if (this != NULL)
		return size;
	return glm::vec2(0.0f, 0.0f);
}
