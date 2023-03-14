#ifndef _PLAY_INCLUDE
#define _PLAY_INCLUDE

#include "TileMap.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"

#include "Player.h"


class Play
{


public:

	Play();
	~Play();

	void init();
	void update(int deltaTime);
	void render();
	

private:
	void initShaders();
	

private:

	TileMap* map;
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture scene;

	ShaderProgram shader;


};
#endif // _PLAY_INCLUDE

