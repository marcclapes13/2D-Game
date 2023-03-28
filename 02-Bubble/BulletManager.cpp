#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BulletManager.h"
#include "Scene.h"

void BulletManager::createBullet(float posEnemyx, float posEnemyy, int direction, ShaderProgram& shaderProgram, float speed) {
	Bullet* new_bull;
	new_bull = new Bullet;
	new_bull->setTileMap(map);
	new_bull->createBullet(posEnemyx, posEnemyy, direction, shaderProgram, speed);
	activeBullets.emplace_back(new_bull);
}

void BulletManager::update(int deltaTime) {
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		activeBullets[i]->update(deltaTime);
	}
}

void BulletManager::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void BulletManager::render() {
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		activeBullets[i]->render();
	}
}

void BulletManager::set_actBullets(vector<Bullet*> bullets) {
	activeBullets = bullets;
}

vector<Bullet*> BulletManager::ret_actBullets() {
	return activeBullets;
}