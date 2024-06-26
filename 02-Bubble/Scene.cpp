#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25



Scene::Scene()
{
	menu = new Menu;
	play = new Play;
	
}

Scene::~Scene()
{

}


void Scene::init(int vides, int estat, int lvl)
{
	level = lvl;
	immune = false;
	countEntry = 0;
	porta_oberta = false;
	enterCount = 0;
	switch (estat) {
	case 0:
		this->state = Scene::State::MENU;
		break;
	case 1:
		this->state = Scene::State::PLAY;
		break;
	case 2:
		this->state = Scene::State::CONTR;
		break;
	case 3:
		this->state = Scene::State::CRED;
		break;
	case 4:
		this->state = Scene::State::OVER;
		break;

	}
	
	lives = vides;
	switch (this->state)
	{
	case Scene::State::MENU:
	{
		this->initMenu();

		break;
	}
	case Scene::State::PLAY:
	{
		this->initPlay(1, lives);
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
	case Scene::State::OVER:
		this->initOver();
		break;
	default:
	{
		std::cerr << "[SCENE::init] wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
	}
}

void Scene::delay(int secs) {
	for (int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

void Scene::update(int deltaTime)
{
	if ((play->porta || porta_oberta) && play->getLevel() != 3) {
		if (play->player != NULL) {
			play->player->setPosition(glm::ivec2(2000, 2000));;
			porta_oberta = true;
		}
		if (countEntry <= 120) {
			play->setEntry(countEntry);
		}
		else {
			porta_oberta = false;
			countEntry = 0;
			initPlay(play->getLevel() + 1, play->getLives());
		}
		++countEntry;
	}
	else if (play->porta || porta_oberta) {
		if (play->player != NULL) {
			play->player->setPosition(glm::ivec2(2000, 2000));;
			porta_oberta = true;
		}
		if (countEntry <= 120) {
			play->setEntry(countEntry);
		}
		else {
			porta_oberta = false;
			countEntry = 0;
			Game::instance().init(3, 3);
		}
		++countEntry;
		
	}
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
	case Scene::State::OVER:
		this->updateOver(deltaTime);
		break;
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
	case Scene::State::OVER:
	{
		this->renderOver();
		break;
	}
	default:
	{
		std::cerr << "[SCENE::render] wrong game state: " << std::endl;
		exit(EXIT_FAILURE);
	}
	}
}

void Scene::initPlay(int level, int lives)
{
	this->play->init(level, lives);
}

void Scene::initMenu()
{
	menu->init();
}

void Scene::initContr()
{
	this->contr.init();
}

void Scene::initCredits()
{
	this->credits.init();
}

void Scene::initOver()
{
	this->over.init();
}


void Scene::updatePlay(int deltaTime)
{
	play->update(deltaTime);

}
void Scene::updateMenu(int deltaTime)
{
	menu->update(deltaTime);

}

void Scene::updateContr(int deltaTime)
{
	this->contr.update(deltaTime);

}
void Scene::updateCredits(int deltaTime)
{
	this->credits.update(deltaTime);

}

void Scene::updateOver(int deltaTime)
{
	this->over.update(deltaTime);

}
void Scene::renderPlay()
{
	play->render();

}
void Scene::renderMenu()
{
	menu->render();

}
void Scene::renderContr()
{
	this->contr.render();
}
void Scene::renderCredits()
{
	this->credits.render();
}
void Scene::renderOver()
{
	this->over.render();
}
void Scene::setMenu() {
	this->state = Scene::State::MENU;
}
inline void Scene::updateState() {
	if (this->state == Scene::State::PLAY) 
	{
		if (Game::instance().getKey((char)98)) //press b
		{
			Game::instance().keyReleased((char)98);
			this->state = Scene::State::MENU;
			this->initMenu();
		}
		else if (Game::instance().getKey((char)103)) //press g
		{
			Game::instance().keyReleased((char)103);
			immune = !immune;
			if (!immune) play->setImmunitatFalse();
			else play->setImmunitatTrue();
		}
		else if (Game::instance().getKey((char)107))
		{
			Game::instance().keyReleased((char)107);
			if (play->keyPressed == false)
				play->keyPressed = true;
		
		}
		else if (this->play->getLevel() == 1)
			
			{
			if (Game::instance().getKey((char)50)) //press 2
			{
				Game::instance().keyReleased((char)50);
				int v = play->getLives();
				
				this->initPlay(2, v);
			}
			else if (Game::instance().getKey((char)51)) //press 3
			{
				Game::instance().keyReleased((char)51);
				int v = play->getLives();
				this->initPlay(3, v);
			}
			
		}
		else if (this->play->getLevel() == 2) //press 2
		{
			if (Game::instance().getKey((char)49))
			{
				Game::instance().keyReleased((char)49);
				int v = play->getLives();
				this->initPlay(1, v);
			}
			else if (Game::instance().getKey((char)51))
			{
				Game::instance().keyReleased((char)51);
				int v = play->getLives();
				this->initPlay(3, v);
			}
			
		}
		else if (this->play->getLevel() == 3) //press 3
		{
			if (Game::instance().getKey((char)49))
			{
				Game::instance().keyReleased((char)49);
				int v = play->getLives();
				this->initPlay(1, v);
			}
			else if (Game::instance().getKey((char)50))
			{
				Game::instance().keyReleased((char)50);
				int v = play->getLives();
				this->initPlay(2, v);
			}
		}
	}

	else if (this->state == Scene::State::MENU)
	{
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) 
		{
			glm::ivec2 cursorPos = menu->cursorPos();
			if (cursorPos != glm::ivec2(220.f, 300.f)) {
				if (cursorPos == glm::ivec2(220.f, 430.f)) {
					Game::instance().specialKeyReleased(GLUT_KEY_UP);
					menu->cursorPlay();
					
				}
				else {
					Game::instance().specialKeyReleased(GLUT_KEY_UP);
					menu->cursorControl();
				}
			}
			
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			glm::ivec2 cursorPos = menu->cursorPos();
			if (cursorPos != glm::ivec2(220.f, 560.f)) {
				if (cursorPos == glm::ivec2(220.f, 300.f)) {
					Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
					menu->cursorControl();
				}
				else {
					Game::instance().specialKeyReleased(GLUT_KEY_DOWN);
					menu->cursorCredits();
				}
			
			}
			
		}
		else if (Game::instance().getKey(13)) {
			enterCount = 1;
			Game::instance().keyReleased(13);
		}
		if (enterCount > 0) {
			++enterCount;
			if (enterCount < 30) {
				menu->cursorSetSelect();
			}
			else {
				enterCount = 0;
				glm::ivec2 cursorPos = menu->cursorPos();
				if (cursorPos == glm::ivec2(220.f, 300.f)) {

					menu->cursorSetSelect();

					this->state = Scene::State::PLAY;
					this->initPlay(1, lives);
				}
				else if (cursorPos == glm::ivec2(220.f, 430.f)) {
					Game::instance().keyReleased(13);
					this->state = Scene::State::CONTR;
					this->initContr();
				}
				else {
					Game::instance().keyReleased(13);
					this->state = Scene::State::CRED;
					this->initCredits();

				}
			}
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
			Game::instance().init(3, 0);
		}
	}
	else if (this->state == Scene::State::OVER) 
	{
		if (Game::instance().getKey((char)98))
		{
			Game::instance().keyReleased((char)98);
			Game::instance().init(3, 0);
		}
	}
}



