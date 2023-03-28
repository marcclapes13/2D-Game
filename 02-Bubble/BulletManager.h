#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE

#include "Bullet.h"


class BulletManager
{
public:
	void createBullet(float posEnemyx, float posEnemyy, int direction, ShaderProgram& shaderProgram, float speed);
	void setTileMap(TileMap* tileMap);
	void update(int deltaTime);
	void render();

	void set_actBullets(vector<Bullet*> bullets);
	vector<Bullet*> ret_actBullets();


private:
	vector<Bullet*> activeBullets;
	TileMap* map;
};

#endif


