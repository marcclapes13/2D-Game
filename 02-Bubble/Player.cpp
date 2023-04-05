#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	size.x = 22;
	size.y = 32;
	lifes = 3;
	spritesheet.loadFromFile("images/Personatges/Soldados1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.0f));

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75, 0.0f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(glm::ivec2(posPlayer.x, posPlayer.y), glm::ivec2(20, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(glm::ivec2(posPlayer.x+8, posPlayer.y), glm::ivec2(22, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (!map->collisionMoveUp(glm::ivec2(posPlayer.x + 8, posPlayer.y), glm::ivec2(22, 32))) {
			if (jumpAngle == 180)
			{
				bJumping = false;
					posPlayer.y = startY;
			}
			else
			{
				posPlayer.y = int(startY - 64 * sin(3.14159f * jumpAngle / 180.f));
					if (jumpAngle > 90)
						bJumping = !map->collisionMoveDown(glm::ivec2(posPlayer.x + 8, posPlayer.y), glm::ivec2(22, 32), &posPlayer.y);
			}
		}
		else {
			bJumping = false;
		}
		
	}
	else
	{

		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(20, 32), &posPlayer.y))
		{
			//map->collisionMoveDown(glm::ivec2(posPlayer.x+8, posPlayer.y+35), glm::ivec2(32,32));
			//setTileMap(map);
			
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
glm::vec2 Player::ret_pos() {
	glm::vec2 posaux = posPlayer;
	posaux.x += 32;
	return posaux;
}

glm::vec2 Player::ret_size() {
	glm::vec2 sizeaux = size;
	return sizeaux;
}
void Player::hit() {
	--lifes;
}
int Player::return_lifes() {
	return lifes;
}
void Player::touch() {
	map->collisionMoveDown(posPlayer, size);

}

bool Player::checkHitFloor() {
	if (map->deadMoveDown(glm::ivec2(posPlayer.x, posPlayer.y), size))
		return true;
	return false;
}


