#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <GL/glut.h>

#include <iostream>
#include <fstream>
#include <vector>


class Level
{
public:

	Level();
	~Level();

	void setPath(const std::string& path);

	void init();
	void update(int deltaTime);
	void render();

private:

	bool loadMap();
	void cleanMap();
	void updateLava();
	void assignBehaviours();
	void winLevel();

private:

	bool updateBehaviour = false;
	bool win = false;

	std::string path;

};


#endif // _LEVEL_INCLUDE
