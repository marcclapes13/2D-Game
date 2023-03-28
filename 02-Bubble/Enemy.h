#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"



class Enemy
{
	
public:
	void init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, int direccio, BulletManager* bulletManager);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void soldierShoot();
	glm::vec2 ret_pos();
	glm::vec2 ret_size();
	vector<Bullet*> ret_actBullets();
	void set_actBullets(vector<Bullet*> bullets);
	vector<Bullet*> bulletList;
	int return_type();

private:
	int typeofEnemy, health, cooldown, dir, transform;
	glm::vec2 posEnemy, size, tileMapDispl;
	Player* player;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	ShaderProgram* aux;
	Bullet* bullet;
	BulletManager* bulletM;
	
	
};

#endif
