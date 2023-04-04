#define PUÑETAZOS 0
#define DOCTOR 1
#define ARMADO 2

#include "Enemy.h"

enum EnemyAnims
{
	MOVE_RIGHT, MOVE_LEFT, TRANSFORM1, TRANSFORM2, TRANSFORM3, TRANSFORM4, MOVE_RIGHT_AVION, MOVE_LEFT_AVION, MOVE_UP_AVION, MOVE_DOWN_AVION
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

void Enemy::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, int direccio, int level, int nEnemy, BulletManager* bulletManager)
{
	lvl = level;
	numEnemy = nEnemy;
	dir = direccio;
	typeofEnemy = typeOf;
	cooldown = 75;
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

		if (lvl == 1) {
			switch (numEnemy) {
			case 0:
				cooldown = 70;
				
				break;
			case 1:
				cooldown = 0;
				break;
			case 2:
				cooldown = 180;
				break;
			case 3:
				cooldown = 45;
				break;
			case 4:
				cooldown = 45;
				break;

			}

		}
		else if (lvl == 2) {

		}
		else {
			if (dir == 0) {

				cooldown = 70;
			}
			else {

				cooldown = 0;
			}
		}
		
		sprite->changeAnimation(0);
		size.x = 22;
		size.y = 32;
		health = 10;
		break;
	case DOCTOR:
		cooldownAvio = 0;
		first = false;
		moveDown = false;
		moveUp = false;
		moveLeft = false;
		moveRight = false;
		transformado = false;
		transform = 70; //630
		spritesheet.loadFromFile("images/Personatges/Doctor.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25f, 0.20f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(11);
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.0f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, 0.0f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f, 0.0f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.0f));

		sprite->setAnimationSpeed(TRANSFORM1, 8);
		sprite->addKeyframe(TRANSFORM1, glm::vec2(0.0f, 0.6f));

		sprite->setAnimationSpeed(TRANSFORM2, 8);
		sprite->addKeyframe(TRANSFORM2, glm::vec2(0.25f, 0.6f));

		sprite->setAnimationSpeed(TRANSFORM3, 8);
		sprite->addKeyframe(TRANSFORM3, glm::vec2(0.5f, 0.6));

		sprite->setAnimationSpeed(TRANSFORM4, 8);
		sprite->addKeyframe(TRANSFORM4, glm::vec2(0.75f, 0.6f));

		
		sprite->setAnimationSpeed(MOVE_LEFT_AVION, 8);
		sprite->addKeyframe(MOVE_LEFT_AVION, glm::vec2(0.0f, 0.2f));
		sprite->addKeyframe(MOVE_LEFT_AVION, glm::vec2(0.25f, 0.2f));

		sprite->setAnimationSpeed(MOVE_RIGHT_AVION, 8);
		sprite->addKeyframe(MOVE_RIGHT_AVION, glm::vec2(0.5f, 0.2f));
		sprite->addKeyframe(MOVE_RIGHT_AVION, glm::vec2(0.75f, 0.2f));

		sprite->setAnimationSpeed(MOVE_UP_AVION, 8);
		sprite->addKeyframe(MOVE_UP_AVION, glm::vec2(0.0f, 0.8f));
		sprite->addKeyframe(MOVE_UP_AVION, glm::vec2(0.25f, 0.8f));

		sprite->setAnimationSpeed(MOVE_DOWN_AVION, 8);
		sprite->addKeyframe(MOVE_DOWN_AVION, glm::vec2(0.5f, 0.8f));
		sprite->addKeyframe(MOVE_DOWN_AVION, glm::vec2(0.75f, 0.8f));

		
			if (dir == 0) {
				cooldown = 0;
			}
			else {
				cooldown = 70;

			}
		
		sprite->changeAnimation(0);
		size.x = 22;
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
	bulletM = bulletManager;
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (lvl == 1) {
		switch (numEnemy) {
		case 0:
			if (cooldown > 0) {
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				posEnemy.x += 2;
				cooldown--;
				dir = 0;

			}
			else {
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posEnemy.x -= 2;
				--cooldown;
				dir = 1;
			}
			if (cooldown == -70) {
				cooldown = 70;
			}
			break;
		case 1:
			if (cooldown > 0) {
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				posEnemy.x += 2;
				cooldown--;
				dir = 0;

			}
			else {
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
				posEnemy.x -= 2;
				--cooldown;
				dir = 1;
			}
			if (cooldown == -70) {
				cooldown = 70;
			}
			break;
		case 2:
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
			if (cooldown == -180) {
				cooldown = 180;
			}
			break;
		case 3:
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
			if (cooldown == -45) {
				cooldown = 45;
			}
			break;
		case 4:
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
			if (cooldown == -45) {
				cooldown = 45;
			}
			break;
		}
	}
	else if (lvl == 2) {

	}
	else {
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
					dir = 0;
				}
				else {
					if (sprite->animation() != MOVE_RIGHT)
						sprite->changeAnimation(MOVE_RIGHT);
					posEnemy.x -= 2;
					--cooldown;
					dir = 1;
				}
				if (cooldown == -70) {
					cooldown = 70;
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
				first = true;
				--transform;
			}
			else {
				if (numEnemy == 2) { // avió esquerra
					size.y = 22;
					transformado = true;
					if (first == true) {
						if (!moveDown) {
							if (sprite->animation() != MOVE_LEFT_AVION)
								sprite->changeAnimation(MOVE_LEFT_AVION);
							posEnemy.x -= 2;
							++cooldownAvio;
							if (cooldownAvio == 15) {
								moveDown = true;
								cooldownAvio = 0;
							}
						}
						else {
							if (sprite->animation() != MOVE_DOWN_AVION)
								sprite->changeAnimation(MOVE_DOWN_AVION);
							posEnemy.y += 2;
							++cooldownAvio;
							if (cooldownAvio == 30) {
								moveDown = false;
								moveRight = true;
								cooldownAvio = 0;
								first = false;
							}
						}

					}
					else {
						if (moveDown) {
							if (sprite->animation() != MOVE_DOWN_AVION)
								sprite->changeAnimation(MOVE_DOWN_AVION);
							posEnemy.y += 2;
							++cooldownAvio;
							if (cooldownAvio == 95) {
								moveDown = false;
								moveRight = true;
								cooldownAvio = 0;
							}
						}
						else if (moveRight) {
							if (sprite->animation() != MOVE_RIGHT_AVION)
								sprite->changeAnimation(MOVE_RIGHT_AVION);
							posEnemy.x += 2;
							++cooldownAvio;
							if (cooldownAvio == 200) {
								moveRight = false;
								moveUp = true;
								cooldownAvio = 0;
							}
						}
						else if (moveUp) {
							if (sprite->animation() != MOVE_UP_AVION)
								sprite->changeAnimation(MOVE_UP_AVION);
							posEnemy.y -= 2;
							++cooldownAvio;
							if (cooldownAvio == 95) {
								moveUp = false;
								moveLeft = true;
								cooldownAvio = 0;
							}
						}
						else if (moveLeft) {
							if (sprite->animation() != MOVE_LEFT_AVION)
								sprite->changeAnimation(MOVE_LEFT_AVION);
							posEnemy.x -= 2;
							++cooldownAvio;
							if (cooldownAvio == 200) {
								moveLeft = false;
								moveDown = true;
								cooldownAvio = 0;
							}
						}
					}
				}
				else if (numEnemy == 3) { // avió dreta
					size.y = 22;
					transformado = true;
					if (first == true) {
						if (!moveDown) {
							if (sprite->animation() != MOVE_RIGHT_AVION)
								sprite->changeAnimation(MOVE_RIGHT_AVION);
							posEnemy.x += 2;
							++cooldownAvio;
							if (cooldownAvio == 15) {
								moveDown = true;
								cooldownAvio = 0;
							}
						}
						else {
							if (sprite->animation() != MOVE_DOWN_AVION)
								sprite->changeAnimation(MOVE_DOWN_AVION);
							posEnemy.y += 2;
							++cooldownAvio;
							if (cooldownAvio == 30) {
								moveDown = false;
								moveLeft = true;
								cooldownAvio = 0;
								first = false;
							}
						}

					}
					else {
						if (moveDown) {
							if (sprite->animation() != MOVE_DOWN_AVION)
								sprite->changeAnimation(MOVE_DOWN_AVION);
							posEnemy.y += 2;
							++cooldownAvio;
							if (cooldownAvio == 95) {
								moveDown = false;
								moveLeft = true;
								cooldownAvio = 0;
							}
						}
						else if (moveRight) {
							if (sprite->animation() != MOVE_RIGHT_AVION)
								sprite->changeAnimation(MOVE_RIGHT_AVION);
							posEnemy.x += 2;
							++cooldownAvio;
							if (cooldownAvio == 200) {
								moveRight = false;
								moveDown = true;
								cooldownAvio = 0;
							}
						}
						else if (moveUp) {
							if (sprite->animation() != MOVE_UP_AVION)
								sprite->changeAnimation(MOVE_UP_AVION);
							posEnemy.y -= 2;
							++cooldownAvio;
							if (cooldownAvio == 95) {
								moveUp = false;
								moveRight = true;
								cooldownAvio = 0;
							}
						}
						else if (moveLeft) {
							if (sprite->animation() != MOVE_LEFT_AVION)
								sprite->changeAnimation(MOVE_LEFT_AVION);
							posEnemy.x -= 2;
							++cooldownAvio;
							if (cooldownAvio == 200) {
								moveLeft = false;
								moveUp = true;
								cooldownAvio = 0;
							}
						}
					}
				}
			}
			break;

		case (ARMADO):

			soldierShoot();
			for (int i = 0; i < bulletList.size(); ++i) {
				if (bulletList[i] != NULL)
					bulletList[i]->update(deltaTime);
			}
			break;

		}
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
			new_bull->createBullet(posEnemy.x+64, posEnemy.y+20, 1, *aux, 1.0f);
			bulletList.push_back(new_bull);
			cooldown = 150;
			
		}
		else {
			Bullet* new_bull;
			new_bull = new Bullet;
			new_bull->setTileMap(map);
			new_bull->createBullet(posEnemy.x+22, posEnemy.y+20, 0, *aux, 1.0f);
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
		if (dir == 0) // dreta
			return glm::vec2(posEnemy.x +34, posEnemy.y);
		else 
			return glm::vec2(posEnemy.x + 30, posEnemy.y);
		break;
	case ARMADO:
		if (dir == 0) // dreta
			return glm::vec2(posEnemy.x + 18, posEnemy.y);
		else 
			return glm::vec2(posEnemy.x + 18, posEnemy.y);
		break;
	case DOCTOR:
		if (dir == 0) { // esquerra
			if (!transformado)
				return glm::vec2(posEnemy.x + 38, posEnemy.y);
			else
				return glm::vec2(posEnemy.x + 38, posEnemy.y+6);
		}
		else {
			if (!transformado)
				return glm::vec2(posEnemy.x + 30, posEnemy.y);
			else
				return glm::vec2(posEnemy.x + 30, posEnemy.y+6);
		}
		break;
	}	
}

int Enemy::return_type() {
	return typeofEnemy;
}

