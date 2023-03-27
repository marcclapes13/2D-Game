#define PUÑETAZOS 0
#define DOCTOR 1
#define ARMADO 2

#include "Enemy.h"

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

enum SoldierAnims
{
	DEFAULT
};

void Enemy::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, int direccio)
{
	typeofEnemy = typeOf;
	cooldown = 50;
	aux = &shaderProgram;
	switch (typeofEnemy) {
	case PUÑETAZOS:
		spritesheet.loadFromFile("images/Personatges/Puñetazos.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(0.33f, 0.5f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.0f, 0.0f));

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.5f));

		if (direccio == 0)
			sprite->changeAnimation(STAND_RIGHT);

		else
			sprite->changeAnimation(STAND_LEFT);
		size.x = 20;
		size.y = 20;
		health = 10;
		break;
	case DOCTOR:
		spritesheet.loadFromFile("images/Personatges/Doctor.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.5f, 0.0f));

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.0f));

		if (direccio == 0)
			sprite->changeAnimation(STAND_RIGHT);

		else
			sprite->changeAnimation(STAND_LEFT);
		size.x = 34;
		size.y = 64;
		health = 5;
		break;
	case ARMADO:
		spritesheet.loadFromFile("images/Personatges/Armado.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(0.25f, 1.0f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);
			sprite->setAnimationSpeed(STAND_RIGHT, 8);
			sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.0f));

			sprite->setAnimationSpeed(STAND_LEFT, 8);
			sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.0f));

		if (direccio == 0)
			sprite->changeAnimation(STAND_RIGHT);

		else 
			sprite->changeAnimation(STAND_LEFT);
		size.x = 23;
		size.y = 64;
		health = 7;
		break;
	}
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	player = target;
}

void Enemy::update(int deltaTime)
{

		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}
void Enemy::render()
{
	sprite->render();
}
void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}
void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

glm::vec2 Enemy::ret_size() {
	if (this != NULL)
		return size;
	return glm::vec2(0.0f, 0.0f);
}

