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
	switch (this->state)
	{
	case Scene::State::MENU:
	{
		this->initMenu();
		break;
	}
	case Scene::State::PLAY:
	{
		this->initPlay();
		break;
	}
	default:
	{
		std::cerr << "[SCENE::init] wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
	}
}

void Scene::update(int deltaTime)
{
	this->updateState();
	switch (this->state)
	{
	case Scene::State::MENU:
	{
		this->updateMenu(deltaTime);
		break;
	}
	case Scene::State::PLAY:
	{
		this->updatePlay(deltaTime);
		break;
	}
	default:
	{
		std::cerr << "[SCENE::update] wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
	}
	
}

void Scene::render()
{
	switch (this->state)
	{
	case Scene::State::MENU:
	{
		this->renderMenu();
		break;
	}
	case Scene::State::PLAY:
	{
		this->renderPlay();
		break;
	}
	default:
	{
		std::cerr << "[SCENE::render] wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
	}
}

void Scene::initPlay()
{
	this->play.init();
}

void Scene::initMenu()
{
	this->menu.init();
}

void Scene::updatePlay(int deltaTime)
{
	this->play.update(deltaTime);

}
void Scene::updateMenu(int deltaTime)
{
	this->menu.update(deltaTime);

}

void Scene::renderPlay()
{
	this->play.render();

}
void Scene::renderMenu()
{
	this->menu.render();

}
inline void Scene::updateState()
{
	if (this-> state == Scene::State::PLAY && Game::instance().getSpecialKey(GLUT_KEY_F1))
	{
		
		this->state = Scene::State::MENU;
		this->initMenu();
	}

	else if (this->state == Scene::State::MENU && Game::instance().getSpecialKey(GLUT_KEY_F1))
	{

		this->state = Scene::State::PLAY;
		this->initPlay();
	}
}



