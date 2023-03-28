#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Play.h"
#include "Menu.h"
#include "Control.h"
#include "Credits.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:

	enum class State { MENU, PLAY, CONTR, CRED};

	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	
	void initPlay(int level);
	void initMenu();
	void initSelector();
	void initContr();
	void initCredits();
	void updatePlay(int deltaTime);
	void updateMenu(int deltaTime);
	void updateContr(int deltaTime);
	void updateCredits(int deltaTime);
	void renderPlay();
	void renderMenu();
	void renderContr();
	void renderCredits();

	inline void updateState();

private:

	bool immune = false;
	Menu menu;
	Play play;
	Control contr;
	Credits credits;
	Texture textura;
	Scene::State state = Scene::State::MENU;

};


#endif // _SCENE_INCLUDE

