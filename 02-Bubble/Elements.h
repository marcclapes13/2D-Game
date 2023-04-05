#pragma once
#include <glm/glm.hpp>
#include "Sprite.h"
#include "TileMap.h"

class Elements
{
public:
	void init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, int element);
	~Elements();
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void update(int deltaTime);
	void render();
	glm::vec2 ret_pos();
	glm::vec2 ret_size();

	void setPorta1();
	void setPorta2();
	void setPorta3();

private:
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::vec2 posElem, size;
};


