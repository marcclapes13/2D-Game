#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Play.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:

	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	
	void initPlay();
	void updatePlay(int deltaTime);
	void renderPlay();

private:

	Play play;

};


#endif // _SCENE_INCLUDE

