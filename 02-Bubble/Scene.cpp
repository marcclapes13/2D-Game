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
	case Scene::State::CONTR:
	{
		this->initContr();
		break;
	}
	case Scene::State::CRED:
	{
		this->initCredits();
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
	case Scene::State::CONTR:
	{
		this->updateContr(deltaTime);
		break;
	}
	case Scene::State::CRED:
	{
		this->updateCredits(deltaTime);
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
	case Scene::State::CONTR:
	{
		this->renderContr();
		break;
	}
	case Scene::State::CRED:
	{
		this->renderCredits();
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

void Scene::initContr()
{
	this->contr.init();
}

void Scene::initCredits()
{
	this->credits.init();
}


void Scene::updatePlay(int deltaTime)
{
	this->play.update(deltaTime);

}
void Scene::updateMenu(int deltaTime)
{
	this->menu.update(deltaTime);

}

void Scene::updateContr(int deltaTime)
{
	this->contr.update(deltaTime);

}
void Scene::updateCredits(int deltaTime)
{
	this->credits.update(deltaTime);

}

void Scene::renderPlay()
{
	this->play.render();

}
void Scene::renderMenu()
{
	this->menu.render();

}
void Scene::renderContr()
{
	this->contr.render();
}
void Scene::renderCredits()
{
	this->credits.render();
}
inline void Scene::updateState()
{
	if (this->state == Scene::State::PLAY) 
	{
		if (Game::instance().getKey((char)109)) //press m
		{
			Game::instance().keyReleased((char)109);
			this->state = Scene::State::MENU;
			this->initMenu();
		}
		else if (this->play.getLevel() == 1)
			
			{
			if (Game::instance().getKey((char)50)) //press 1
			{
				Game::instance().keyReleased((char)50);
				this->play.setLevel(2);
				this->play.init();
			}
		}
		else if (this->play.getLevel() == 2) //press 2
		{
			if (Game::instance().getKey((char)49))
			{
				Game::instance().keyReleased((char)50);
				this->play.setLevel(1);
				this->play.init();
			}
		}
	}

	else if (this->state == Scene::State::MENU)
	{
		if (Game::instance().getKey((char)112)) //press p
		{
			Game::instance().keyReleased((char)112);
			this->state = Scene::State::PLAY;
			this->initPlay();
		}
		else if (Game::instance().getKey((char)99)) //press c
		{
			Game::instance().keyReleased((char)99);
			this->state = Scene::State::CONTR;
			this->initContr();
		}
		else if (Game::instance().getKey((char)114)) //press r
		{
			Game::instance().keyReleased((char)114);
			this->state = Scene::State::CRED;
			this->initCredits();
		}
	}
	else if (this->state == Scene::State::CONTR)
	{
		if (Game::instance().getKey((char)98))
		{
			Game::instance().keyReleased((char)98);
			this->state = Scene::State::MENU;
			this->initMenu();
		}
	}
	else if (this->state == Scene::State::CRED)
	{
		if (Game::instance().getKey((char)98))
		{
			Game::instance().keyReleased((char)98);
			this->state = Scene::State::MENU;
			this->initMenu();
		}
	}
}



