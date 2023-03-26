#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"


class Enemy
{
public:
	void init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, int direccio);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 ret_pos();
	glm::vec2 ret_size();
	~Enemy();

private:
	int typeofEnemy, health, cooldown;
	glm::vec2 posEnemy, size, tileMapDispl;
	Player* player;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	ShaderProgram* aux;
};

#endif
