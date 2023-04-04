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
#include "Over.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:

	enum class State { MENU, PLAY, CONTR, CRED, OVER};

	Scene();
	~Scene();

	void init(int vides, int estat);
	void update(int deltaTime);
	void render();
	void setMenu();
private:
	
	void initPlay(int level, int lives);
	void initMenu();
	void initSelector();
	void initContr();
	void initCredits();
	void initOver();

	void updatePlay(int deltaTime);
	void updateMenu(int deltaTime);
	void updateContr(int deltaTime);
	void updateCredits(int deltaTime);
	void updateOver(int deltaTime);

	void renderPlay();
	void renderMenu();
	void renderContr();
	void renderCredits();
	void renderOver();

	inline void updateState();

private:

	bool immune;
	int lives;
	Menu* menu;
	Play* play;
	Control contr;
	Credits credits;
	Over over;
	Texture textura;
	Scene::State state;

};


#endif // _SCENE_INCLUDE

