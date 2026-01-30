#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include <fstream>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, LSW; float S; };  
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SP, SE, SSE; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };
struct TextConfig { int SS=0, FR=0, FG=0, FB=0; std::string font_file; };

class Game
{
	sf::RenderWindow m_window;            // the window we will draw to
	EntityManager m_entities;           // vector of entities to maintain
	sf::Font m_font;                    // the font we will use to draw
	sf::Text m_text;                  // the score text to be drawn to the screen
	PlayerConfig m_PlayerConfig;
	EnemyConfig m_EnemyConfig;
	BulletConfig m_BulletConfig;
	TextConfig m_TextConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpaenTime = 0;
	bool m_paused = false;               // whether we update game logic
	bool m_running = true;               // whether the game is running

	std::shared_ptr<Entity> m_player;
	
	void init(const std::string& config);  // initialize the GameState with a config file path
	void setPaused(bool Paused);          // pause the game

	void sMovement();                     // System: Entity position / movement update
	void sUserInput();                   // System: User Input
	void sLifespan();                       // System: Lifespan
	void sRender();                       // System: Render / Drawing
	void sEnemySpawner();                // System: Spawns Enemies
	void sCollision();                  // System: Collisions
	void sTextSpawner();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const vec2 & mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
	void spawnText();

public:
	Game(const std::string& config);
	void run();

	
};

