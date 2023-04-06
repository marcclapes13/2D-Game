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
#define INIT_PLAYER_Y_TILES_2 7

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
	agafat = false;
	portaOberta = false;
	porta = false;
	portaCoolDown = 0;
	eliminat = true;
	stopActive = false;
	countStop = 0;
	key = false;
	gema = false;
	gemmActive = false;
	stop = false;
	invulnerable = false;
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

	default:
	{
		std::cerr << "[PLAY::init] wrong level number" << std::endl;
		exit(EXIT_FAILURE);
	}
		
	}
	initEnemies();
	initElements();
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
	if (level == 1) {
		if (!stop && map->retPintat() >= 45) {
			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(19 * map->getTileSize(), 21 * map->getTileSize()));
			elementList.insert(elementList.begin(), element_aux);
			stop = true;
			eliminat = false;

		}
		if ((map->retPintat() == 70 || map->retPintat() == 71 || map->retPintat() == 72) && !eliminat && !agafat) {
			elementList.erase(elementList.begin());
			eliminat = true;
			countStop = 201;
		}
		
		if (!key && map->retPintat() >= 114) {
			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(19 * map->getTileSize(), 17 * map->getTileSize()));
			elementList.insert(elementList.begin(), element_aux);
			key = true;
			eliminat = false;
		}
	}
	else if (level == 2) {
		if (!gema && map->retPintat() >= 30) {
			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 3);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(13 * map->getTileSize(), 13 * map->getTileSize()));
			elementList.insert(elementList.begin(), element_aux);
			gema = true;
			eliminat = false;

		}
		if ((map->retPintat() == 50 || map->retPintat() == 51 || map->retPintat() == 52) && !eliminat) {
			elementList.erase(elementList.begin());
			eliminat = true;
		}
		if (!key && map->retPintat() >= 88) {
			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(4 * map->getTileSize(), 5 * map->getTileSize()));
			elementList.insert(elementList.begin(), element_aux);
			key = true;
			eliminat = false;
		}
	}
	else {
		if (!invulnerable && map->retPintat() >= 45) {
			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 2);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(13 * map->getTileSize(), 9 * map->getTileSize()));
			elementList.insert(elementList.begin(), element_aux);
			invulnerable = true;
			eliminat = false;
		}
		if ((map->retPintat() == 70 || map->retPintat() == 71 || map->retPintat() == 72) && !eliminat) {
			elementList.erase(elementList.begin());
			eliminat = true;
			countStop = 201;
		}
		if (!key && map->retPintat() >= 90) {
			Elements* element_aux;
			element_aux = new Elements();
			element_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
			element_aux->setTileMap(map);
			element_aux->setPosition(glm::vec2(8 * map->getTileSize(), 17 * map->getTileSize()));
			elementList.insert(elementList.begin(), element_aux);
			key = true;
			eliminat = false;
		}
	}
	for (int i = 0; i < int(elementList.size()); ++i)
		elementList[i]->update(deltaTime);

	//touchStop
	stopActive = touchStop();
	if (!stopActive && countStop == 0) {
		for (int i = 0; i < int(enemyList.size()); ++i)
			enemyList[i]->update(deltaTime);
	}
	else if (countStop == 201) {
		for (int i = 0; i < int(enemyList.size()); ++i)
			enemyList[i]->update(deltaTime);
	}
	else {
		++countStop;
		if (countStop == 1)
			elementList.erase(elementList.begin());
			
		if (countStop > 200) {
			stopActive = false;
			countStop = 201;
			agafat = true;
		}
	}
	//touchGemm
	gemmActive = touchGemm();
	if (gemmActive && gema) {
		//elementList.erase(elementList.begin());
	}
	
	// touchKey
	keyActive = touchKey();
	if (keyActive && key) {
		if (portaCoolDown == 0)
			elementList.erase(elementList.begin());
		else {
			if (portaCoolDown <= 10) {
				elementList[0]->setPorta1();
				elementList[0]->update(deltaTime);
			}
			else if (portaCoolDown <= 20) {
				elementList[0]->setPorta2();
				elementList[0]->update(deltaTime);
			}
			else if (portaCoolDown <= 30) {
				elementList[0]->setPorta3();
				elementList[0]->update(deltaTime);
			}
		}
		
		++portaCoolDown;
		
	}
	if (portaOberta) {
		porta = checkPorta();
	}
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
	else if (level == 2) {
		int number_of_enemies = 7;
		for (int i = 0; i < number_of_enemies; ++i) {
			int enemy_x;
			int enemy_y;
			int typeofEnemy;
			int direccio;
			switch (i + 1) { //enemy_list
			case 1:
				enemy_x = 8; enemy_y = 16; typeofEnemy = PUÑETAZOS, direccio = 0;
				break;
			case 2:
				enemy_x = 26; enemy_y = 16; typeofEnemy = PUÑETAZOS, direccio = 1;
				break;
			case 3:
				enemy_x = 8; enemy_y = 20; typeofEnemy = PUÑETAZOS, direccio = 0;
				break;
			case 4:
				enemy_x = 16; enemy_y = 4; typeofEnemy = ARMADO, direccio = 1;
				break;
			case 5:
				enemy_x = 18; enemy_y = 4; typeofEnemy = ARMADO, direccio = 0;
				break;
			case 6:
				enemy_x = 2; enemy_y = 24; typeofEnemy = ARMADO, direccio = 0;
				break;
			case 7:
				enemy_x = 32; enemy_y = 24; typeofEnemy = ARMADO, direccio = 1;
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
		int num_elem = 5+vides;
		
		for (int i = 4; i < num_elem; ++i) {
			switch (i + 1) {
			case 5:
				despx = 19, despy = 5;
				break;
			case 6:
				despx = 2, despy = 0;
				break;
			case 7:
				despx = 3, despy = 0;
				break;
			case 8:
				despx = 4, despy = 0;
				break;
			case 9:
				despx = 5, despy = 0;
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
	if (level == 2) {
		int despx = 25;
		int despy = 5;
		int num_elem = 5 + vides;
		for (int i = 4; i < num_elem; ++i) {
			switch (i + 1) {
			case 5:
				despx = 34, despy = 5;
				break;
			case 6:
				despx = 2, despy = 0;
				break;
			case 7:
				despx = 3, despy = 0;
				break;
			case 8:
				despx = 4, despy = 0;
				break;
			
			case 9: despx = 5, despy= 0;
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
	else if (level == 3) {
		int despx = 25;
		int despy = 5;
		int num_elem = 5+vides;
		for (int i = 4; i < num_elem; ++i) {
			switch (i + 1) {
			case 5:
				despx = 21, despy = 9;
				break;
			case 6:
				despx = 2, despy = 0;
				break;
			case 7:
				despx = 3, despy = 0;
				break;
			case 8:
				despx = 4, despy = 0;
				break;
			case 9:
				despx = 5, despy = 0;
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
	if (level == 2) {
		for (int j = 0; j < int(enemyList.size()); ++j) {
			vector<Bullet*> activeBullets = enemyList[j]->bulletList;
			for (int i = 0; i < activeBullets.size(); ++i) {
				int posBulletx = activeBullets[i]->ret_pos().x;
				int posBullety = activeBullets[i]->ret_pos().y;
				if (map->collisionMoveLeft(glm::ivec2(posBulletx-40, posBullety), glm::ivec2(8, 4)) || map->collisionMoveRight(glm::ivec2(posBulletx-20, posBullety), glm::ivec2(8, 4))) {
					activeBullets.erase(activeBullets.begin() + i);
					enemyList[j]->bulletList = activeBullets;
				}
			}
		}
	}
	if (level == 3) {
		for (int j = 0; j < int(enemyList.size()); ++j) {
			vector<Bullet*> activeBullets = enemyList[j]->bulletList;
			for (int i = 0; i < activeBullets.size(); ++i) {
				int posBulletx = activeBullets[i]->ret_pos().x;
				int posBullety = activeBullets[i]->ret_pos().y;
				if (map->collisionMoveLeft(glm::ivec2(posBulletx - 40, posBullety), glm::ivec2(8, 4)) || map->collisionMoveRight(glm::ivec2(posBulletx - 20, posBullety), glm::ivec2(8, 4))) {
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

void Play::addLives() {
	 ++vides;
}

void Play::setImmunitatFalse() {
	immunitat = false;
}
void Play::setImmunitatTrue() {
	immunitat = true;
}

bool Play::touchStop() {
		if (stop && player->ret_pos().x >= 18 * map->getTileSize() && player->ret_pos().x <= 20 * map->getTileSize() && player->ret_pos().y >= 20 * map->getTileSize() && player->ret_pos().y <= 22 * map->getTileSize()) {
		return true;
	}
	return false;
}
bool Play::touchKey() {
	if (level == 1) {
		if (key && player->ret_pos().x >= 18 * map->getTileSize() && player->ret_pos().x <= 20 * map->getTileSize() && player->ret_pos().y >= 16 * map->getTileSize() && player->ret_pos().y <= 18 * map->getTileSize()) {
			portaOberta= true;
			return true;
		}
	}
	else if (level == 2) {
		if (key && player->ret_pos().x >= 3 * map->getTileSize() && player->ret_pos().x <= 5 * map->getTileSize() && player->ret_pos().y >= 4 * map->getTileSize() && player->ret_pos().y <= 6 * map->getTileSize()) {
			portaOberta = true;
			return true;
		}
	}
	else if (level == 3) {
		if (key && player->ret_pos().x >= 7 * map->getTileSize() && player->ret_pos().x <= 9 * map->getTileSize() && player->ret_pos().y >= 16 * map->getTileSize() && player->ret_pos().y <= 18 * map->getTileSize()) {
			portaOberta = true;
			return true;
		}
	}
	return false;
}

bool Play::touchGemm() {
	
	if (level == 2) {
		if (gema && player->ret_pos().x >= 12 * map->getTileSize() && player->ret_pos().x <= 14 * map->getTileSize() && player->ret_pos().y >= 12 * map->getTileSize() && player->ret_pos().y <= 14 * map->getTileSize()) {
			//if (getLives() < 3) addLives();
			return true;
		}
	}
	return false;
}

bool Play::checkPorta() {
	if (level == 1) {
		if (player->ret_pos().x >= 18 * map->getTileSize() && player->ret_pos().x <= 20 * map->getTileSize() && player->ret_pos().y >= 4 * map->getTileSize() && player->ret_pos().y <= 6 * map->getTileSize()) {
			
			return true;
		}
	}
	else if (level == 2) {
		if (player->ret_pos().x >= 33 * map->getTileSize() && player->ret_pos().x <= 35 * map->getTileSize() && player->ret_pos().y >= 4 * map->getTileSize() && player->ret_pos().y <= 6 * map->getTileSize()) {

			return true;
		}
	}
	else if (level == 3) {
		if (player->ret_pos().x >= 20 * map->getTileSize() && player->ret_pos().x <= 22 * map->getTileSize() && player->ret_pos().y >= 8 * map->getTileSize() && player->ret_pos().y <= 10 * map->getTileSize()) {

			return true;
		}
	}
	return false;
}