#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


Scene::Scene()
{

}

Scene::~Scene()
{

}


void Scene::init()
{
	this->initPlay();
}

void Scene::update(int deltaTime)
{
	this->updatePlay(deltaTime);
	
}

void Scene::render()
{
	this->renderPlay();
	
}

void Scene::initPlay()
{
	this->play.init();
}

void Scene::updatePlay(int deltaTime)
{
	this->play.update(deltaTime);

}

void Scene::renderPlay()
{
	this->play.render();

}



