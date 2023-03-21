#ifndef _PLAY_INCLUDE
#define _PLAY_INCLUDE

#include "TileMap.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "Player.h"


class Play
{
public: 
	enum class State { LEVEL1, LEVEL2, LEVEL3 };
	

public:

	Play();
	~Play();

	void init();
	void update(int deltaTime);
	void render();

	int getLevel();
	void setLevel(int lev);
	

private:
	void initShaders();
	inline void updateState();
	

private:

	Play::State state;

	Level levels;
	int level = 1;
	TileMap* map;
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture scene;

	ShaderProgram shader;


};
#endif // _PLAY_INCLUDE

