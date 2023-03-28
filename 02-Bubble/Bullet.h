#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void createBullet(float posx, float posy, int direction, ShaderProgram& shaderProgram, float speedy);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	~Bullet();
	glm::vec2 ret_pos();
	glm::vec2 ret_size();


private:
	float speed;
	glm::vec2 posBullet, size;
	int dir;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};