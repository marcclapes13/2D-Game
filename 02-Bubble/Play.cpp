#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Play.h"
#include "Level.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 8
#define INIT_PLAYER_Y_TILES 3

#define INIT_ENEMY_X_TILES 20
#define INIT_ENEMY_Y_TILES 25

#define PUÑETAZOS 0
#define DOCTOR 1
#define ARMADO 2

Play::Play()
{
	map = NULL;
	player = NULL;
	//spriteBackground = NULL;
}

Play::~Play()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	//if (spriteBackground != NULL)
		//delete spriteBackground;
}

void Play::init()
{
		this->initShaders();

		switch (level)
		{
		case 1:
		{
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
		initEnemies();
		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
		currentTime = 0.0f;
}

void Play::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i]->update(deltaTime);
	//spriteBackground->update(deltaTime);

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
	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i]->render();
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
	if (Game::instance().getKey((char)50))
	{
		this->state = Play::State::LEVEL2;
		level = 2;
		this->init();
	}

	else if ( Game::instance().getKey((char)49))
	{

		this->state = Play::State::LEVEL1;
		level = 1;
		this->init();
	}
}

int Play::getLevel() {
	return level;
}
void Play::setLevel(int lev) {
	level = lev;

}

void Play::initEnemies() {
	if (level == 1) {
		int number_of_enemies = 6; //cuantos enemigos hay en el nivel
		for (int i = 0; i < number_of_enemies; ++i) {
			int enemy_x;
			int enemy_y;
			int typeofEnemy;
			int direccio;
			switch (i + 1) { //enemy_list
			case 1:
				enemy_x = 2; enemy_y = 24; typeofEnemy = PUÑETAZOS, direccio = 0;
				break;
			case 2:
				enemy_x = 32; enemy_y = 24; typeofEnemy = PUÑETAZOS, direccio = 1;
				break;
			case 3:
				enemy_x = 15; enemy_y = 12; typeofEnemy = DOCTOR, direccio = 0;
				break;
			case 4:
				enemy_x = 19; enemy_y = 12; typeofEnemy = DOCTOR, direccio = 1;
				break;
			case 5:
				enemy_x = 2; enemy_y = 8; typeofEnemy = ARMADO, direccio = 0;
				break;
			case 6:
				enemy_x = 32; enemy_y = 8; typeofEnemy = ARMADO, direccio = 1;
				break;
			}
			Enemy* enemy_aux;
			enemy_aux = new Enemy();
			enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy, direccio);
			enemy_aux->setTileMap(map);
			enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
			enemyList.push_back(enemy_aux);
		}
	}
}
