#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Play.h"
#include "Level.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

Play::Play()
{
	map = NULL;
	player = NULL;
}

Play::~Play()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void Play::init()
{

		this->initShaders();
		switch (level)
		{
		case 1:
		{
			cout << "level1" << endl;
			this->state = Play::State::LEVEL1;
			map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		}
		case 2:
		{
			this->state = Play::State::LEVEL2;
			map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
			break;
		}
		case 3:
		{
			this->state = Play::State::LEVEL3;
			break;
		}
		default:
		{
			std::cerr << "[PLAY::init] wrong level number" << std::endl;
			exit(EXIT_FAILURE);
		}
		
		}
		
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setTileMap(map);
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;

}

void Play::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

}

void Play::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
}

void Play::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
inline void Play::updateState()
{
	if (this->state == Play::State::LEVEL1 && Game::instance().getSpecialKey(GLUT_KEY_F4))
	{
		cout << "aqui" << endl;
		this->state = Play::State::LEVEL2;
		level = 2;
		this->init();
	}

	else if (this->state == Play::State::LEVEL2 && Game::instance().getSpecialKey(GLUT_KEY_F5))
	{

		this->state = Play::State::LEVEL1;
		level = 1;
		this->init();
	}
}
