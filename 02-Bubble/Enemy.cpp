#define PUÑETAZOS 0
#define DOCTOR 1
#define ARMADO 2

#include "Enemy.h"

enum EnemyAnims
{
	MOVE_RIGHT, MOVE_LEFT, TRANSFORM1, TRANSFORM2, TRANSFORM3, TRANSFORM4, MOVE_RIGHT_AVION, MOVE_LEFT_AVION
};
enum SoldierAnims
{
	STAND_RIGHT, STAND_LEFT
};

Enemy::~Enemy() {
	for (int i = 0; i < bulletList.size(); ++i) {
		delete bulletList[i];
	}
}

void Enemy::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, int direccio, BulletManager* bulletManager)
{
	dir = direccio;
	typeofEnemy = typeOf;
	cooldown = 50;
	aux = &shaderProgram;
	switch (typeofEnemy) {
	case PUÑETAZOS:
		
		spritesheet.loadFromFile("images/Personatges/Puñetazos.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.33f, 0.5f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);

			sprite->setAnimationSpeed(MOVE_RIGHT, 8);
			sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.0f));
			sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.33f, 0.0f));
			sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.67f, 0.0f));

			sprite->setAnimationSpeed(MOVE_LEFT, 8);
			sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.5f));
			sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.33f, 0.5f));
			sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.67f, 0.5f));

		if (dir == 0) {
			
			cooldown = 70;
		}
		else {

			cooldown = 0;
		}
		sprite->changeAnimation(0);
		size.x = 32;
		size.y = 32;
		health = 10;
		break;
	case DOCTOR:
		transform = 500;
		spritesheet.loadFromFile("images/Personatges/Doctor.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(9);
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.0f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.0f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.0f));

		sprite->setAnimationSpeed(TRANSFORM1, 8);
		sprite->addKeyframe(TRANSFORM1, glm::vec2(0.0f, 0.75f));

		sprite->setAnimationSpeed(TRANSFORM2, 8);
		sprite->addKeyframe(TRANSFORM2, glm::vec2(0.25f, 0.75f));

		sprite->setAnimationSpeed(TRANSFORM3, 8);
		sprite->addKeyframe(TRANSFORM3, glm::vec2(0.5f, 0.75));

		sprite->setAnimationSpeed(TRANSFORM4, 8);
		sprite->addKeyframe(TRANSFORM4, glm::vec2(0.75f, 0.75f));

		sprite->setAnimationSpeed(MOVE_LEFT_AVION, 8);
		sprite->addKeyframe(MOVE_LEFT_AVION, glm::vec2(0.0f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT_AVION, glm::vec2(0.25f, 0.25f));

		sprite->setAnimationSpeed(MOVE_RIGHT_AVION, 8);
		sprite->addKeyframe(MOVE_RIGHT_AVION, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT_AVION, glm::vec2(0.75f, 0.25f));


		if (dir == 0) {
			cooldown = 0;
		}
		else {
			cooldown = 85;
			
		}
		sprite->changeAnimation(0);
		size.x = 32;
		size.y = 32;
		health = 5;
		break;
	case ARMADO:
		spritesheet.loadFromFile("images/Personatges/Armado.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25f, 1.0f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(2);
			sprite->setAnimationSpeed(STAND_RIGHT, 8);
			sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.0f));

			sprite->setAnimationSpeed(STAND_LEFT, 8);
			sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.0f));

		if (dir == 0)
			sprite->changeAnimation(STAND_RIGHT);

		else 
			sprite->changeAnimation(STAND_LEFT);
		size.x = 32;
		size.y = 32;
		health = 7;
		break;
	}
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	bulletM = bulletManager;
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	switch (typeofEnemy) {
	case (PUÑETAZOS):
		if (cooldown > 0) {
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posEnemy.x += 2;
			cooldown--;
			
		}
		else {
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posEnemy.x -= 2;
			--cooldown;
		}
		if (cooldown == -70) {
			cooldown = 70;
		}
		break;
	case (DOCTOR):
		if (transform > 0) {
			if (cooldown > 0) {
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posEnemy.x += 2;
				cooldown--;
			}
			else {
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				posEnemy.x -= 2;
				--cooldown;
			}
			if (cooldown == -85) {
				cooldown = 85;
			}
			--transform;
		}
		else if (transform > -10) {
			if (sprite->animation() != TRANSFORM1) {
				sprite->changeAnimation(TRANSFORM1);
			}
			--transform;
		}
		else if (transform > -20) {
			if (sprite->animation() != TRANSFORM2) {
				sprite->changeAnimation(TRANSFORM2);
			}
			--transform;
		}
		else if (transform > -30) {
			if (sprite->animation() != TRANSFORM3) {
				sprite->changeAnimation(TRANSFORM3);
			}
			--transform;
		}
		else if (transform > -40) {
			if (sprite->animation() != TRANSFORM4) {
				sprite->changeAnimation(TRANSFORM4);
			}
			--transform;
		}
		else {
			if (cooldown > 0) {
				if (sprite->animation() != MOVE_RIGHT_AVION)
					sprite->changeAnimation(MOVE_RIGHT_AVION);
				posEnemy.x += 2;
				cooldown--;
			}
			else {
				if (sprite->animation() != MOVE_LEFT_AVION)
					sprite->changeAnimation(MOVE_LEFT_AVION);
				posEnemy.x -= 2;
				--cooldown;
			}
			if (cooldown == -85) {
				cooldown = 85;
			}
		}
		break;

	case (ARMADO):


		soldierShoot();
		for (int i = 0; i < bulletList.size(); ++i) {
			bulletList[i]->update(deltaTime);
		}
		break;

	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
	
}
void Enemy::render()
{		
	sprite->render();
	for (int i = 0; i < bulletList.size(); ++i) {
		bulletList[i]->render();
	}
}

void Enemy::soldierShoot() {
	if (cooldown <= 0) {
		if (dir == 0) {
			Bullet* new_bull;
			new_bull = new Bullet;
			new_bull->setTileMap(map);
			new_bull->createBullet(posEnemy.x+50, posEnemy.y+20, 1, *aux, 1.0f);
			bulletList.push_back(new_bull);
			cooldown = 150;
			
		}
		else {
			Bullet* new_bull;
			new_bull = new Bullet;
			new_bull->setTileMap(map);
			new_bull->createBullet(posEnemy.x+20, posEnemy.y+20, 0, *aux, 1.0f);
			bulletList.push_back(new_bull);
			cooldown = 150;
		}
	}
	else --cooldown;
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
glm::vec2 Enemy::ret_pos() {
	switch (typeofEnemy) {
	case PUÑETAZOS: 
		return glm::vec2(posEnemy.x + 32, posEnemy.y);
		break;
	case ARMADO:
		return glm::vec2(posEnemy.x + 32, posEnemy.y);
		break;
	case DOCTOR:
		
		return glm::vec2(posEnemy.x+32, posEnemy.y);
		break;
	}	
}

int Enemy::return_type() {
	return typeofEnemy;
}

