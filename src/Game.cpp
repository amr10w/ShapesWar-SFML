#include "Game.h"
#include <filesystem>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::run()
{
	// coding
	
	while (m_running)
	{

		m_entities.update();

		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		setPaused(m_paused);
		sLifespan();
		sTextSpawner();
		sRender();

	}
	

}

void Game::init(const std::string& config)
{
	int width_window =0, height_window= 0, FrameRate= 0;
	std::ifstream fin(config);
	std::string s;
	fin >> s;
	if (s == "Window")
	{
		fin >> width_window >> height_window >> FrameRate >> s>>s;
	}
	if (s == "Font")
	{
		
		fin >> m_TextConfig.font_file>>m_TextConfig.SS>> m_TextConfig.FR>> m_TextConfig.FG>> m_TextConfig.FB>>s;

	}
	if (s == "Player")
	{
		fin >> m_PlayerConfig.SR >> m_PlayerConfig.CR >> m_PlayerConfig.S >> m_PlayerConfig.FR >> m_PlayerConfig.FG >> m_PlayerConfig.FB
			>> m_PlayerConfig.OR >> m_PlayerConfig.OG >> m_PlayerConfig.OB >> m_PlayerConfig.OT
			>> m_PlayerConfig.V  >> m_PlayerConfig.LSW >>s;
	}
	if (s == "Enemy")
	{
		fin >> m_EnemyConfig.SR >> m_EnemyConfig.CR >> m_EnemyConfig.SMIN >> m_EnemyConfig.SMAX
			>> m_EnemyConfig.OR >> m_EnemyConfig.OG >> m_EnemyConfig.OB >> m_EnemyConfig.OT
			>> m_EnemyConfig.VMIN >> m_EnemyConfig.VMAX >> m_EnemyConfig.L >> m_EnemyConfig.SP
			>>m_EnemyConfig.SE>>m_EnemyConfig.SSE>> s;
	}
	if (s == "Bullet")
	{
		fin >> m_BulletConfig.SR >> m_BulletConfig.CR >> m_BulletConfig.S
			>> m_BulletConfig.FR >> m_BulletConfig.FG >> m_BulletConfig.FB
			>> m_BulletConfig.OR >> m_BulletConfig.OG >> m_BulletConfig.OB >> m_BulletConfig.OT
			>> m_BulletConfig.V >> m_BulletConfig.L;
	}

	
	
	m_window.create(sf::VideoMode(width_window, height_window), "Assignment 2");
	m_window.setFramerateLimit(FrameRate);
	spawnPlayer();
	spawnText();

}

void Game::spawnPlayer()
{
	auto Entity= m_entities.addEntity("Player");

	float pos_x = m_window.getSize().x / 2.f;
	float pos_y = m_window.getSize().y / 2.f;

	Entity->cTransform = std::make_shared<cTransform>(vec2(pos_x,pos_y),vec2(m_PlayerConfig.S, m_PlayerConfig.S), 1);

	Entity->cShape = std::make_shared<cShape>(m_PlayerConfig.SR, m_PlayerConfig.V, sf::Color(m_PlayerConfig.FR, m_PlayerConfig.FG, m_PlayerConfig.FB)
		,sf::Color(m_PlayerConfig.OR, m_PlayerConfig.OG, m_PlayerConfig.OB),m_PlayerConfig.OT);

	Entity->cInput = std::make_shared<cInput>();

	Entity->cCollision = std::make_shared<cCollision>(m_PlayerConfig.CR);

	m_player = Entity;

}



void Game::spawnEnemy()
{	
	auto Entity = m_entities.addEntity("Enemy");
	
//positon of enemy
	int max_x = m_window.getSize().x - m_EnemyConfig.CR;
	int min_x = m_EnemyConfig.CR;

	float randPos_x = 0;

	int max_y = m_window.getSize().y - m_EnemyConfig.CR;
	int min_y = m_EnemyConfig.CR;

	float randPos_y = 0;
	
	while (true)
	{
		randPos_x = min_x + (rand() % (int)(1 + max_x - min_x));
		randPos_y = min_y + (rand() % (int)(1 + max_y - min_y));

		float distance_x = abs(randPos_x - m_player->cTransform->pos.x);
		float distance_y = abs(randPos_y - m_player->cTransform->pos.y);

		if (distance_x > m_player->cCollision->radius * 2 && distance_y > m_player->cCollision->radius * 2)
		{
			break;
		}
	}
	

//Speed of enemy

	float S_rand_x = m_EnemyConfig.SMIN + (rand() % (int)(1 + m_EnemyConfig.SMAX - m_EnemyConfig.SMIN));
	float S_rand_y = m_EnemyConfig.SMIN + (rand() % (int)(1 + m_EnemyConfig.SMAX - m_EnemyConfig.SMIN));
	int rand_angle = 0 + (rand() & (int)(1 + 0 + 360));
	float rand_angleRad = rand_angle * (3.14f / 180.f);
	


	Entity->cTransform = std::make_shared<cTransform>(vec2(randPos_x, randPos_y)
	, vec2( S_rand_x * cos(rand_angleRad), S_rand_y * sin(rand_angleRad)), 1);
	
	int V_rand = m_EnemyConfig.VMIN + (rand() % (int)(1 + m_EnemyConfig.VMAX - m_EnemyConfig.VMIN));
	int F1_rand = 0+ (rand() % (int)(1 + 255 - 0));
	int F2_rand = 0 + (rand() % (int)(1 + 255 - 0));
	int F3_rand = 0 + (rand() % (int)(1 + 255 - 0));


	Entity->cShape = std::make_shared<cShape>(m_EnemyConfig.SR,V_rand,sf::Color(F1_rand, F2_rand, F3_rand)
	,sf::Color(m_EnemyConfig.OR, m_EnemyConfig.OG, m_EnemyConfig.OB),m_EnemyConfig.OT);

	Entity->cCollision = std::make_shared<cCollision>(m_EnemyConfig.CR);

	Entity->cScore = std::make_shared<cScore>(m_EnemyConfig.SE);

	m_lastEnemySpaenTime = m_currentFrame;

}

void::Game::sEnemySpawner()
{
	if (!m_paused)
	{
		if (m_currentFrame - m_lastEnemySpaenTime == m_EnemyConfig.SP)
		{
			spawnEnemy();
		}
	}
}

void Game::sRender()
{
	m_window.clear();
	
	for (auto& e : m_entities.get_Entities())
	{
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		e->cTransform->anagle += 1.5f;
		e->cShape->circle.setRotation(e->cTransform->anagle);

		m_window.draw(e->cShape->circle);
	}

	m_window.draw(m_text);

	m_window.display();
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const vec2& mousePos)
{
	auto Entity = m_entities.addEntity("Bullet");


	//std::cout << "\n " << " " << mousePos.x << " " << mousePos.y
	//	<< " " << dir_bullet.x << " " << dir_bullet.y;

	Entity->cTransform = std::make_shared<cTransform>(entity->cTransform->pos
		, mousePos * m_BulletConfig.S , 0);

	Entity->cShape = std::make_shared<cShape>(m_BulletConfig.SR, m_BulletConfig.V
		, sf::Color(m_BulletConfig.FR, m_BulletConfig.FG, m_BulletConfig.FB)
		, sf::Color(m_BulletConfig.OR, m_BulletConfig.OG, m_BulletConfig.OB), m_BulletConfig.OT);
	
	Entity->cCollision = std::make_shared<cCollision>(m_BulletConfig.CR);

	Entity->cLifespan = std::make_shared<cLifespan>(m_BulletConfig.L);

}

void Game::sUserInput()
{

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed )
		{
			m_running = false;
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:

				m_player->cInput->up = true;
				break;

			case sf::Keyboard::S:

				m_player->cInput->down = true;
				break;

			case sf::Keyboard::A:

				m_player->cInput->left = true;
				break;

			case sf::Keyboard::D:

				m_player->cInput->right = true;
				break;

			default: break;

			}
			
			if (event.key.code == sf::Keyboard::P)
			{
				m_paused = !m_paused;
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_running = false;
			}
			
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				
				m_player->cInput->up = false;
				break;

			case sf::Keyboard::S:

				m_player->cInput->down = false;
				break;

			case sf::Keyboard::A:

				m_player->cInput->left = false;
				break;

			case sf::Keyboard::D:

				m_player->cInput->right = false;
				break;

			default: break;

			}
		}
		if (event.type==sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				vec2 target(event.mouseButton.x - m_player->cTransform->pos.x
					, event.mouseButton.y - m_player->cTransform->pos.y);

				vec2 direction = target.normalization();
				if (!m_paused)
				{
					spawnBullet(m_player, direction);
				}
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (m_score > 0)
				{
					if (m_score > 200)
					{
						spawnSpecialWeapon(m_player);
						m_score -= 200;
					}
				}
				
			}

		}
	}
}

void Game::sMovement()
{
	if (!m_paused)
	{
		if (m_player->cInput->up)
		{
			m_player->cTransform->pos.y -= m_player->cTransform->velocity.y;

			if (m_player->cTransform->pos.y < m_player->cCollision->radius)
			{
				m_player->cTransform->pos.y = m_player->cShape->circle.getPosition().y;
			}
		}
		if (m_player->cInput->down)
		{
			m_player->cTransform->pos.y += m_player->cTransform->velocity.y;

			if (m_player->cTransform->pos.y > m_window.getSize().y - m_player->cCollision->radius)
			{
				m_player->cTransform->pos.y = m_player->cShape->circle.getPosition().y;
			}
		}
		if (m_player->cInput->right)
		{
			m_player->cTransform->pos.x += m_player->cTransform->velocity.x;

			if (m_player->cTransform->pos.x > m_window.getSize().x - m_player->cCollision->radius)
			{
				m_player->cTransform->pos.x = m_player->cShape->circle.getPosition().x;
			}
		}
		if (m_player->cInput->left)
		{
			m_player->cTransform->pos.x -= m_player->cTransform->velocity.x;

			if (m_player->cTransform->pos.x < m_player->cCollision->radius)
			{
				m_player->cTransform->pos.x = m_player->cShape->circle.getPosition().x;
			}
		}

		for (auto& e : m_entities.get_Entities("Bullet"))
		{
			e->cTransform->pos.x += e->cTransform->velocity.x;
			e->cTransform->pos.y += (e->cTransform->velocity.y);
		}

		for (auto& e : m_entities.get_Entities("Enemy"))
		{
			e->cTransform->pos.x += e->cTransform->velocity.x;
			e->cTransform->pos.y += e->cTransform->velocity.y;

			if (e->cTransform->pos.x < e->cCollision->radius)
			{
				e->cTransform->velocity.x *= -1;
			}
			if (e->cTransform->pos.x > m_window.getSize().x - e->cCollision->radius)
			{
				e->cTransform->velocity.x *= -1;
			}
			if (e->cTransform->pos.y < e->cCollision->radius)
			{
				e->cTransform->velocity.y *= -1;
			}
			if (e->cTransform->pos.y > m_window.getSize().y - e->cCollision->radius)
			{
				e->cTransform->velocity.y *= -1;
			}
		}
	}
}

void Game::sCollision()
{
	
	

	for (auto& e : m_entities.get_Entities("Bullet"))
		{
		if (e->cTransform->pos.x < e->cCollision->radius)
			{
			e->destroy();
			}
		if (e->cTransform->pos.x > m_window.getSize().x - e->cCollision->radius)
			{
			e->destroy();
			}
		if (e->cTransform->pos.y < e->cCollision->radius)
			{
			e->destroy();
			}
		if (e->cTransform->pos.y > m_window.getSize().y - e->cCollision->radius)
			{
			e->destroy();
			}
	}

	for (auto& e : m_entities.get_Entities("Bullet"))
	{
		for (auto& i : m_entities.get_Entities("Enemy"))
		{
			
			float distance = e->cTransform->pos.dist(i->cTransform->pos);

			if (distance < e->cCollision->radius + i->cCollision->radius)
			{
				e->destroy();
				i->destroy();

				if (i->cShape->circle.getRadius() == m_EnemyConfig.SR)
				{
					spawnSmallEnemies(i);
				}

				m_score += i->cScore->score;

			}
		}
	}
	
	for (auto& e : m_entities.get_Entities("Enemy"))
	{
		float distance = e->cTransform->pos.dist(m_player->cTransform->pos);

		if (distance < e->cCollision->radius + m_player->cCollision->radius)
		{
			e->destroy();

			if (e->cShape->circle.getRadius() == m_EnemyConfig.SR)
			{
				spawnSmallEnemies(e);
			}

			float pos_x = m_window.getSize().x / 2.f;
			float pos_y = m_window.getSize().y / 2.f;

			m_player->cTransform->pos.x = pos_x;
			m_player->cTransform->pos.y = pos_y;

			m_score = 0;

		}
	}
	
}

void Game::sLifespan()
{
	if (!m_paused) {
		for (auto& e : m_entities.get_Entities("Bullet"))
		{
			//if (e->cLifespan->total>0)
			//{	

			if (e->cLifespan->remaining < (e->cLifespan->total) / 2)
			{
				float lifespanRatio = static_cast<float> (e->cLifespan->remaining) / e->cLifespan->total;

				int alpha = static_cast<int> (lifespanRatio * 255);

				e->cShape->circle.setFillColor(sf::Color(e->cShape->circle.getFillColor().r
					, e->cShape->circle.getFillColor().g, e->cShape->circle.getFillColor().b, alpha));
				e->cShape->circle.setOutlineColor(sf::Color(e->cShape->circle.getOutlineColor().r
					, e->cShape->circle.getOutlineColor().g, e->cShape->circle.getOutlineColor().b, alpha));

			}

			if (e->cLifespan->remaining == 0)
			{
				e->destroy();
			}
			else
			{
				(e->cLifespan->remaining)--;
			}

			//}
		}

		for (auto& e : m_entities.get_Entities("Enemy"))
		{
			if (e->cShape->circle.getRadius() == m_EnemyConfig.SR / 2)
			{
				if (e->cLifespan->remaining < (e->cLifespan->total) / 2)
				{
					float lifespanRatio = static_cast<float> (e->cLifespan->remaining) / e->cLifespan->total;

					int alpha = static_cast<int> (lifespanRatio * 255);

					e->cShape->circle.setFillColor(sf::Color(e->cShape->circle.getFillColor().r
						, e->cShape->circle.getFillColor().g, e->cShape->circle.getFillColor().b, alpha));
					e->cShape->circle.setOutlineColor(sf::Color(e->cShape->circle.getOutlineColor().r
						, e->cShape->circle.getOutlineColor().g, e->cShape->circle.getOutlineColor().b, alpha));

				}

				if (e->cLifespan->remaining == 0)
				{
					e->destroy();
				}
				else
				{
					(e->cLifespan->remaining)--;
				}
			}
		}
	}
}

void Game::spawnText()
{	

	if (!m_font.loadFromFile(m_TextConfig.font_file))
	{
		std::cerr << "No font exist, please cheak again\n";
		std::cout << "Current path is: " << std::filesystem::current_path() << std::endl;
		exit(-1);
	}

	m_text.setCharacterSize(m_TextConfig.SS);
	m_text.setFillColor(sf::Color(m_TextConfig.FR, m_TextConfig.FG, m_TextConfig.FB));
	m_text.setFont(m_font);
	m_text.setPosition(0, 0);
	
	
}

void Game::sTextSpawner()
{	
	m_text.setString(" Score = " + std::to_string(m_score));
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{	
	size_t entityPoints = entity->cShape->circle.getPointCount();
	size_t anagleDirRatio = 360 / entityPoints;
	size_t anagleDir = 0;
	
	float radiusSmallEnemies = entity->cShape->circle.getRadius() / 2;

	for (int i = 0; i < entityPoints; i++)
	{
		auto Entity = m_entities.addEntity("Enemy");

		float anagleRad = anagleDir * (float)(3.14 / 180.f);

		Entity->cTransform = std::make_shared<cTransform>(entity->cTransform->pos
			,vec2(entity->cTransform->velocity.x * cos(anagleRad), entity->cTransform->velocity.x * sin(anagleRad))
			,entity->cTransform->anagle);

		Entity->cShape = std::make_shared<cShape>(radiusSmallEnemies, entityPoints
			, entity->cShape->circle.getFillColor(), entity->cShape->circle.getOutlineColor()
			, entity->cShape->circle.getOutlineThickness());

		Entity->cCollision = std::make_shared<cCollision>(radiusSmallEnemies);

		Entity->cScore = std::make_shared<cScore>(m_EnemyConfig.SSE);

		Entity->cLifespan = std::make_shared<cLifespan>(m_EnemyConfig.L);


		anagleDir += anagleDirRatio;

	}
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	size_t entityPoints = entity->cShape->circle.getPointCount()+6;
	size_t anagleDirRatio = 360 / entityPoints;
	size_t anagleDir = 0;

	float radiusSpecialWeapon = entity->cShape->circle.getRadius() / 3;

	for (int i = 0; i < entityPoints; i++)
	{
		auto Entity = m_entities.addEntity("Bullet");

		float anagleRad = anagleDir * (3.14f/ 180.f);

		Entity->cTransform = std::make_shared<cTransform>(entity->cTransform->pos
			, vec2(entity->cTransform->velocity.x * cos(anagleRad), entity->cTransform->velocity.x * sin(anagleRad))
			, entity->cTransform->anagle);

		Entity->cShape = std::make_shared<cShape>(radiusSpecialWeapon, entityPoints
			, entity->cShape->circle.getOutlineColor(), entity->cShape->circle.getOutlineColor()
			, entity->cShape->circle.getOutlineThickness());

		Entity->cCollision = std::make_shared<cCollision>(radiusSpecialWeapon);

		Entity->cLifespan = std::make_shared<cLifespan>(m_PlayerConfig.LSW);


		anagleDir += anagleDirRatio;

	}

}

void Game::setPaused(bool Paused)
{
	if (!m_paused)
	{
		m_currentFrame++;
	}
	

}
