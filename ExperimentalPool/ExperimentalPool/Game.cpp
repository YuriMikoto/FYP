// author Peter Lowe

#include "Game.h"
#include <iostream>
#define b2_velocityThreshold 0; //This does not appear to be working. 

Game::Game() :
	m_window{ sf::VideoMode{ 1600, 900, 32 }, "Experimental Pool" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupBoard();
	setupSprite(); // load texture

}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world.
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	
	world.Step(timeStep, velocityIterations, positionIterations);
	balls[0].Update();
	balls[1].Update();
	//northWall.Update();
	//debugConsole();
}

void Game::debugConsole()
{
	//system("CLS");
	std::cout << "Ball position: (" << balls[0].body->GetPosition().x << ", " << balls[0].body->GetPosition().y << ")" << std::endl;
	std::cout << "Ball Velocity: (" << balls[0].body->GetLinearVelocity().x << ", " << balls[0].body->GetLinearVelocity().y << ")" << std::endl;
	std::cout << std::endl;
	//std::cout << "West wall body position: (" << westWall.body->GetPosition().x << ", " << westWall.body->GetPosition().y << ")" << std::endl;
	//std::cout << "West wall draw position: (" << westWall.renderShape.getPosition().x << ", " << westWall.renderShape.getPosition().y << ")" << std::endl;
	//std::cout << "West wall true position: (" << westWall.getPosition().x << ", " << westWall.getPosition().y << ")" << std::endl;
	//std::cout << std::endl;
	std::cout << "North wall body position: (" << northWall.body->GetPosition().x << ", " << northWall.body->GetPosition().y << ")" << std::endl;
	std::cout << "North wall draw position: (" << northWall.renderShape.getPosition().x << ", " << northWall.renderShape.getPosition().y << ")" << std::endl;
	std::cout << "North wall true position: (" << northWall.getPosition().x << ", " << northWall.getPosition().y << ")" << std::endl;

	std::cout << std::endl;
}

/// <summary>
/// Draw all renderable objects in the game from here.
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(42, 111, 77, 255));
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);

	/*northRect.setFillColor(sf::Color::Black);
	northRect.setPosition(sf::Vector2f(northWall.getPosition().x, northWall.getPosition().y));
	northRect.setSize(sf::Vector2f(northWall.getWidth() * 100, northWall.getHeight() * 100));
	m_window.draw(northRect);*/

	northWall.Draw(&m_window);
	southWall.Draw(&m_window);
	westWall.Draw(&m_window);
	eastWall.Draw(&m_window);

	balls[0].Draw(&m_window);
	balls[1].Draw(&m_window);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// Prepare sprites for every renderable object in the game from here.
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);

	northWall.SetupSprite();
	southWall.SetupSprite();
	westWall.SetupSprite();
	eastWall.SetupSprite();

	balls[0].SetupSprite(sf::Color(200, 200, 200, 255));
	balls[1].SetupSprite(sf::Color(128, 196, 255, 255));
}

/// <summary>
/// Creates the four walls of the board in Box2D.
/// </summary>
void Game::setupBoard()
{
	/*northWall = Wall(b2Vec2(wallDepth, 0), boardWidth, wallDepth);
	northWall.def.position.Set(northWall.getPosition().x, northWall.getPosition().y);
	northWall.body = world.CreateBody(&northWall.def);
	northWall.shape.SetAsBox(northWall.getWidth() / 2.0f, northWall.getHeight() / 2.0f);
	northWall.body->CreateFixture(&northWall.shape, 0.0f);

	southWall = Wall(b2Vec2(wallDepth, boardLength-wallDepth), boardWidth, wallDepth);
	southWall.def.position.Set(southWall.getPosition().x, southWall.getPosition().y);
	southWall.body = world.CreateBody(&southWall.def);
	southWall.shape.SetAsBox(southWall.getWidth() / 2.0f, southWall.getHeight() / 2.0f);
	southWall.body->CreateFixture(&southWall.shape, 0.0f);

	westWall = Wall(b2Vec2(0, 0), wallDepth, boardLength);
	westWall.def.position.Set(westWall.getPosition().x, westWall.getPosition().y);
	westWall.body = world.CreateBody(&westWall.def);
	westWall.shape.SetAsBox(westWall.getWidth() / 2.0f, westWall.getHeight() / 2.0f);
	westWall.body->CreateFixture(&westWall.shape, 0.0f);

	eastWall = Wall(b2Vec2(boardWidth+ wallDepth, 0), wallDepth, boardLength);
	eastWall.def.position.Set(eastWall.getPosition().x, eastWall.getPosition().y);
	eastWall.body = world.CreateBody(&eastWall.def);
	eastWall.shape.SetAsBox(eastWall.getWidth() / 2.0f, eastWall.getHeight() / 2.0f);
	eastWall.body->CreateFixture(&eastWall.shape, 0.0f);

	cueBall = Ball(b2Vec2(boardWidth / 2, boardLength / 2), true);
	cueBall.def.type = b2_dynamicBody;
	cueBall.def.position.Set(cueBall.getPosition().x, cueBall.getPosition().y);
	cueBall.body = world.CreateBody(&cueBall.def);
	cueBall.shape.m_p.Set(cueBall.getPosition().x, cueBall.getPosition().y);
	cueBall.shape.m_radius = 0.028f; //56mm diameter.
	cueBall.body->CreateFixture(&cueBall.shape, 1.7f); //Is that the actual density of a pool cue ball?*/

	//Walls
	{
		northWall = Wall(b2Vec2(1.4f, 1.25f), boardWidth, wallDepth);
		northWall.def.position.Set(1.4f+wallDepth / 2.0, 1.25f + wallDepth / 2.0);
		northWall.body = world.CreateBody(&northWall.def);
		northWall.shape.SetAsBox(2.7f / 2.0f, 0.1f / 2.0f);
		northWall.body->CreateFixture(&northWall.shape, 0.0f);

		southWall = Wall(b2Vec2(1.4f, 0), boardWidth, wallDepth);
		southWall.def.position.Set(1.4f + wallDepth / 2.0, 0 + wallDepth / 2.0);
		southWall.body = world.CreateBody(&southWall.def);
		southWall.shape.SetAsBox(2.7f / 2.0f, 0.1f / 2.0f);
		southWall.body->CreateFixture(&southWall.shape, 0.0f);

		westWall = Wall(b2Vec2(0, 0), wallDepth, boardLength);
		westWall.def.position.Set(0 + wallDepth / 2.0, 0.625f + wallDepth / 2.0);
		westWall.body = world.CreateBody(&westWall.def);
		westWall.shape.SetAsBox(0.1f / 2.0f, 1.35f / 2.0f);
		westWall.body->CreateFixture(&westWall.shape, 0.0f);

		eastWall = Wall(b2Vec2(2.8f, 0.625f), wallDepth, boardLength);
		eastWall.def.position.Set(2.8f + wallDepth/2.0, 0.625f + wallDepth/2.0);
		eastWall.body = world.CreateBody(&eastWall.def);
		eastWall.shape.SetAsBox(0.1f / 2.0f, 1.35f / 2.0f);
		eastWall.body->CreateFixture(&eastWall.shape, 0.0f);
		/*eastWall.fdef.shape = &eastWall.shape;
		eastWall.fdef.restitution = 1.0f;
		eastWall.fixt = eastWall.body->CreateFixture(&eastWall.fdef);*/
	}

	//Ball
	{
		//cueBall = Ball(b2Vec2(boardWidth / 2, boardLength / 2), true);
		balls[0].def.type = b2_dynamicBody;
		balls[0].def.position.Set(1.35f, 0.625f);
		balls[0].body = world.CreateBody(&balls[0].def);
		//cbshape.m_p.Set(cueBall.getPosition().x, cueBall.getPosition().y);
		balls[0].shape.m_radius = 0.028f; //56mm diameter.
		balls[0].fdef.shape = &balls[0].shape;
		balls[0].fdef.density = 1848.88194565217f; //At least, I think that's the actual density of a pool cue ball.
		balls[0].fdef.restitution = 0.6f;
		balls[0].fdef.friction = 0.2f;
		balls[0].fixt = balls[0].body->CreateFixture(&balls[0].fdef);

		//cueBall = Ball(b2Vec2(boardWidth / 2, boardLength / 2), true);
		balls[1].def.type = b2_dynamicBody;
		balls[1].def.position.Set(0.5f, 0.630f);
		balls[1].body = world.CreateBody(&balls[1].def);
		balls[1].shape.m_radius = 0.028f; //56mm diameter.
		balls[1].fdef.shape = &balls[1].shape;
		balls[1].fdef.density = 1848.88194565217f; //At least, I think that's the actual density of a pool cue ball.
		balls[1].fdef.restitution = 0.6f;
		balls[1].fdef.friction = 0.2f;
		balls[1].fixt = balls[1].body->CreateFixture(&balls[1].fdef);
	}

	balls[0].body->ApplyLinearImpulseToCenter(b2Vec2(4.5f, 0.0f), true);
	//Apply an impulse of (4.5f, 0) to see an inelastic collision. Try (4.6f, 0) and higher and it'll bounce at least once.
}