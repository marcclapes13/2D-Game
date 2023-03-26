#ifndef _PLAY_INCLUDE
#define _PLAY_INCLUDE

#include "TileMap.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"


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

	void initEnemies();

private:
	void initShaders();
	inline void updateState();
	

private:

	Play::State state;

	Level levels;
	int level = 1;
	TileMap* map;
	Player* player;
	Enemy* enemy;
	Enemy* enemy2;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture scene;
	vector<Enemy*> enemyList;

	ShaderProgram shader;


};
#endif // _PLAY_INCLUDE

