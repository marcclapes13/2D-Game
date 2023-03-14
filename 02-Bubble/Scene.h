#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Play.h"
#include "Menu.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:

	enum class State { MENU, PLAY };

	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	
	void initPlay();
	void initMenu();
	void updatePlay(int deltaTime);
	void updateMenu(int deltaTime);
	void renderPlay();
	void renderMenu();

	inline void updateState();

private:

	Menu menu;
	Play play;
	Texture textura;
	Scene::State state = Scene::State::PLAY;

};


#endif // _SCENE_INCLUDE

