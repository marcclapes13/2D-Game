#ifndef _PLAY_INCLUDE
#define _PLAY_INCLUDE

#include "TileMap.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Elements.h"
#include "Bullet.h"


class Play
{
public: 
	enum class State { LEVEL1, LEVEL2, LEVEL3, GAME_OVER };
	

public:

	Play();
	~Play();

	void init(int lev, int lives);
	void update(int deltaTime);
	void render();

	int getLevel();
	void setLevel(int lev);

	void initEnemies();
	void initElements();
	void initVides();
	void checkHits();
	
	void setImmunitatFalse();
	void setImmunitatTrue();
	int getLives();
	bool porta;
	void addLives();
	void initBackground();

private:
	void initShaders();
	inline void updateState();
	void checkBullets();
	bool touchStop();
	bool touchKey();
	bool touchGemm();
	bool checkPorta();
	

private:

	bool agafat;
	bool portaOberta;
	bool eliminat;
	bool keyActive;
	bool stopActive;
	int countStop;
	int portaCoolDown;
	bool key;
	bool gema;
	bool invulnerable;
	bool stop;
	bool immunitat;



	bool gemmActive;

	Play::State state;
	BulletManager bulletManager;
	int vides;
	Level levels;
	int level = 1;
	TileMap* map;
	Player* player;
	Enemy* enemy;
	Enemy enemies;
	Elements* element;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Texture scene;
	Texture texturePuerta;
	Sprite* spritePuerta;
	Texture textureBackground;
	Sprite* spriteBackground;
	Texture textureOver;
	Sprite* spriteOver;
	vector<Enemy*> enemyList;
	vector<Elements*> elementList;
	Bullet bullet;

	ShaderProgram shader;


};
#endif // _PLAY_INCLUDE

