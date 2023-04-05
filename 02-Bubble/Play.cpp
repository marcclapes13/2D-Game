#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Play.h"
#include "Level.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES_1 8
#define INIT_PLAYER_Y_TILES_1 3

#define INIT_PLAYER_X_TILES_2 8
#define INIT_PLAYER_Y_TILES_2 3

#define INIT_PLAYER_X_TILES_3 5
#define INIT_PLAYER_Y_TILES_3 19

#define INIT_ENEMY_X_TILES 20
#define INIT_ENEMY_Y_TILES 25

#define PUÑETAZOS 0
#define DOCTOR 1
#define ARMADO 2

enum {
	Vida
};

Play::Play()
{
	map = NULL;
	player = NULL;
	
	for (int i = 0; i < enemyList.size(); ++i) {
		if (enemyList[i] != NULL) {
			enemyList[i]->~Enemy();
		}
	}
	enemyList.clear();
	elementList.clear();
}

Play::~Play()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;

	for (int i = 0; i < enemyList.size(); ++i){
		if (enemyList[i] != NULL)
			enemyList[i]->~Enemy();
	}
	for (int i = 0; i < elementList.size(); ++i) {
		if (elementList[i] != NULL)
			elementList[i]-> ~Elements();
	}
	
	//if (spriteBackground != NULL)
		//delete spriteBackground;

}

void Play::init(int i, int lives)
{
	immunitat = false;
	vides = lives;
	map = NULL;
	player = NULL;
	spritePuerta = NULL;
	for (int i = 0; i < enemyList.size(); ++i) {
		if (enemyList[i] != NULL) {
			enemyList[i]->~Enemy();
		}
	}
	enemyList.clear();
	elementList.clear();
		
	level = i;
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
		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		break;
	}
	case 4:
		player->setPosition(glm::vec2(50, 50));
		break;
	default:
	{
		std::cerr << "[PLAY::init] wrong level number" << std::endl;
		exit(EXIT_FAILURE);
	}
		
	}

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	if (level == 1) {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_1 * map->getTileSize(), INIT_PLAYER_Y_TILES_1 * map->getTileSize()));
	}
	else if (level == 2) {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_2 * map->getTileSize(), INIT_PLAYER_Y_TILES_2 * map->getTileSize()));
	}
	else {
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_3 * map->getTileSize(), INIT_PLAYER_Y_TILES_3 * map->getTileSize()));
	}
	player->setTileMap(map);
	initEnemies();
	initElements();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Play::update(int deltaTime)
{
	currentTime += deltaTime;
	
	map->collisionMoveDown(glm::ivec2(player->ret_pos().x-22, player->ret_pos().y), glm::ivec2(player->ret_size().x - 10, player->ret_size().y));
	
	if (!immunitat) {
		checkHits();
	}
	checkBullets();
	player->update(deltaTime);
	
	for (int i = 0; i < int(elementList.size()); ++i)
		elementList[i]->update(deltaTime);
	
	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i]->update(deltaTime);


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

	for (int i = 0; i < int(elementList.size()); ++i)
		elementList[i]->render();
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

int Play::getLevel() {
	return level;
}
void Play::setLevel(int lev) {
	level = lev;

}

void Play::initEnemies() {
	if (level == 1) {
		int number_of_enemies = 5;
		for (int i = 0; i < number_of_enemies; ++i) {
			int enemy_x;
			int enemy_y;
			int typeofEnemy;
			int direccio;
			switch (i + 1) {
			case 1:
				enemy_x = 2; enemy_y = 24; typeofEnemy = PUÑETAZOS, direccio = 0;
				break;
			case 2:
				enemy_x = 32; enemy_y = 24; typeofEnemy = PUÑETAZOS, direccio = 1;
				break;
			case 3:
				enemy_x = 6; enemy_y = 16; typeofEnemy = PUÑETAZOS, direccio = 1;
				break;
			case 4:
				enemy_x = 9; enemy_y = 8; typeofEnemy = PUÑETAZOS, direccio = 1;
				break;
			case 5:
				enemy_x = 19; enemy_y = 12; typeofEnemy = PUÑETAZOS, direccio = 1;
				break;
			}
			Enemy* enemy_aux;
			enemy_aux = new Enemy();
			enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy, direccio, level, i, &bulletManager);
			enemy_aux->setTileMap(map);
			enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
			enemyList.push_back(enemy_aux);
		}
	}
	else if (level == 3) {
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
			enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy, direccio, level, i, &bulletManager);
			enemy_aux->setTileMap(map);
			enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
			enemyList.push_back(enemy_aux);
		}
	}
}
void Play::initElements() {
	if (level == 1) {
		int despx = 25;
		int despy = 5;
		int num_elem = 1+vides;
		for (int i = 0; i < num_elem; ++i) {
			switch (i + 1) {
			case 1:
				despx = 25, despy = 5;
				break;
			case 2:
				despx = 2, despy = 0;
				break;
			case 3:
				despx = 3, despy = 0;
				break;
			case 4:
				despx = 4, despy = 0;
				break;
			}

			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, i);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(despx * map->getTileSize(), despy * map->getTileSize()));
			elementList.push_back(element_aux);
		}
	}
	if (level == 3) {
		int despx = 25;
		int despy = 5;
		int num_elem = 1+vides;
		for (int i = 0; i < num_elem; ++i) {
			switch (i + 1) {
			case 1:
				despx = 25, despy = 5;
				break;
			case 2:
				despx = 2, despy = 0;
				break;
			case 3:
				despx = 3, despy = 0;
				break;
			case 4:
				despx = 4, despy = 0;
				break;

			}

			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, i);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(despx * map->getTileSize(), despy * map->getTileSize()));
			elementList.push_back(element_aux);
		}
	}
}

void Play::checkHits() {
	for (int j = 0; j < int(enemyList.size()); ++j) {
		if (enemyList[j]->return_type() != 2) {
			bool xocaX = (((enemyList[j]->ret_pos().x + enemyList[j]->ret_size().x) >= player->ret_pos().x) &&
				((player->ret_pos().x + player->ret_size().x) >= enemyList[j]->ret_pos().x));
			bool xocaY = (((enemyList[j]->ret_pos().y + enemyList[j]->ret_size().y) >= (player->ret_pos().y)) &&
				(((player->ret_pos().y) + player->ret_size().y) >= enemyList[j]->ret_pos().y));;
			if (xocaX && xocaY) {
				--vides;
				if (vides == 0) {
					Game::instance().init(vides, 4);
				}
				else {
					elementList.erase(elementList.end()-1);
					player = new Player();
					player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
					if (level == 1) {
						player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_1 * map->getTileSize(), INIT_PLAYER_Y_TILES_1 * map->getTileSize()));
					}
					else if (level == 2) {
						player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_2 * map->getTileSize(), INIT_PLAYER_Y_TILES_2 * map->getTileSize()));
					}
					else {
						player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_3 * map->getTileSize(), INIT_PLAYER_Y_TILES_3 * map->getTileSize()));
					}
					player->setTileMap(map);
				}
			}

		}
		else {
			vector<Bullet*> activeBullets = enemyList[j]->bulletList;
			for (int i = 0; i < activeBullets.size(); ++i) {
				bool balaX = (((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x) >= player->ret_pos().x) &&
					((player->ret_pos().x + player->ret_size().x) >= activeBullets[i]->ret_pos().x));
				bool balaY = (((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y) >= (player->ret_pos().y)) &&
					(((player->ret_pos().y) + player->ret_size().y) >= activeBullets[i]->ret_pos().y));
				if (balaX && balaY) {
					--vides;
					if (vides == 0) {
						Game::instance().init(vides, 4);
					}
					else {
						elementList.erase(elementList.end()-1);
						player = new Player();
						player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
						if (level == 1) {
							player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_1 * map->getTileSize(), INIT_PLAYER_Y_TILES_1 * map->getTileSize()));
						}
						else if (level == 2) {
							player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_2 * map->getTileSize(), INIT_PLAYER_Y_TILES_2 * map->getTileSize()));
						}
						else {
							player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_3 * map->getTileSize(), INIT_PLAYER_Y_TILES_3 * map->getTileSize()));
						}
						player->setTileMap(map);
					}
					activeBullets.erase(activeBullets.begin() + i);
					enemyList[j]->bulletList = activeBullets;
				}
			}
		}
	}
	if (player->checkHitFloor()) {
		--vides;
		if (vides == 0) {
			Game::instance().init(vides, 4);
		}
		else {
			
			elementList.erase(elementList.end() - 1);
			player = new Player();
			player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			if (level == 1) {
				player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_1 * map->getTileSize(), INIT_PLAYER_Y_TILES_1 * map->getTileSize()));
			}
			else if (level == 2) {
				player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_2 * map->getTileSize(), INIT_PLAYER_Y_TILES_2 * map->getTileSize()));
			}
			else {
				player->setPosition(glm::vec2(INIT_PLAYER_X_TILES_3 * map->getTileSize(), INIT_PLAYER_Y_TILES_3 * map->getTileSize()));
			}
			player->setTileMap(map);
		}

	}

}

void Play::checkBullets() {
	
	if (level == 3) {
		for (int j = 0; j < int(enemyList.size()); ++j) {
			vector<Bullet*> activeBullets = enemyList[j]->bulletList;
			for (int i = 0; i < activeBullets.size(); ++i) {
				if ((activeBullets[i]->ret_pos().x > 18* map->getTileSize()) && (activeBullets[i]->ret_pos().x < 22* map->getTileSize())) {
					activeBullets.erase(activeBullets.begin() + i);
					enemyList[j]->bulletList = activeBullets;
				}
			}
		}
	}

}

int Play::getLives() {
	return vides;
}

void Play::setImmunitatFalse() {
	immunitat = false;
}
void Play::setImmunitatTrue() {
	immunitat = true;
}