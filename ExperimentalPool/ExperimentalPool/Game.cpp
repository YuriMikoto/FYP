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
	cueBall.Update();
	//northWall.Update();
	debugConsole();
}

void Game::debugConsole()
{
	//system("CLS");
	std::cout << "Ball position: (" << cueBall.body->GetPosition().x << ", " << cueBall.body->GetPosition().y << ")" << std::endl;
	std::cout << "Ball Velocity: (" << cueBall.body->GetLinearVelocity().x << ", " << cueBall.body->GetLinearVelocity().y << ")" << std::endl;

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

	cueBall.Draw(&m_window);

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
	//Uncomment the following to change the colours of each wall to be semi-transparent. This is to test that no walls are overlapping. 
	//northWall.renderShape.setFillColor(sf::Color(255, 0, 0, 128));
	//southWall.renderShape.setFillColor(sf::Color(0, 255, 0, 128));
	//westWall.renderShape.setFillColor(sf::Color(0, 0, 255, 128));
	//eastWall.renderShape.setFillColor(sf::Color(0, 0, 0, 128));

	cueBall.SetupSprite();
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
		//northWall = Wall(b2Vec2(wallDepth, 0), boardWidth, wallDepth);
		/*northWall.def.position.Set(northWall.getPosition().x, northWall.getPosition().y);
		northWall.body = world.CreateBody(&northWall.def);
		northWall.shape.SetAsBox(northWall.getWidth() / 2.0f, northWall.getHeight() / 2.0f);
		northWall.body->CreateFixture(&northWall.shape, 0.0f);*/
		
		//northWall.def.position.Set(1.4f, 0.625f);
		northWall = Wall(b2Vec2(1.4f, 1.25f), boardWidth, wallDepth);
		northWall.def.position.Set(1.4f, 1.25f);
		northWall.body = world.CreateBody(&northWall.def);
		northWall.shape.SetAsBox(2.7f / 2.0f, 0.1f / 2.0f);
		northWall.body->CreateFixture(&northWall.shape, 0.0f);
		/*northWall.fdef.shape = &northWall.shape;
		northWall.fdef.restitution = 1.0f;
		northWall.fixt = northWall.body->CreateFixture(&northWall.fdef);*/

		//southWall = Wall(b2Vec2(wallDepth, boardLength - wallDepth), boardWidth, wallDepth);
		/*southWall.def.position.Set(southWall.getPosition().x, southWall.getPosition().y);
		southWall.body = world.CreateBody(&southWall.def);
		southWall.shape.SetAsBox(southWall.getWidth() / 2.0f, southWall.getHeight() / 2.0f);
		southWall.body->CreateFixture(&southWall.shape, 0.0f);*/
		//southWall.def.position.Set(1.4f, -0.625f);

		southWall = Wall(b2Vec2(1.4f, 0), boardWidth, wallDepth);
		southWall.def.position.Set(1.4f, 0);
		southWall.body = world.CreateBody(&southWall.def);
		southWall.shape.SetAsBox(2.7f / 2.0f, 0.1f / 2.0f);
		southWall.body->CreateFixture(&southWall.shape, 0.0f);
		/*southWall.fdef.shape = &southWall.shape;
		southWall.fdef.restitution = 1.0f;
		southWall.fixt = southWall.body->CreateFixture(&southWall.fdef);*/

		//westWall = Wall(b2Vec2(0, 0), wallDepth, boardLength);
		//westWall = Wall(b2Vec2(0, 0.625f), wallDepth, boardLength);
		westWall = Wall(b2Vec2(0, 0), wallDepth, boardLength);
		westWall.def.position.Set(0, 0.625f);
		westWall.body = world.CreateBody(&westWall.def);
		westWall.shape.SetAsBox(0.1f / 2.0f, 1.35f / 2.0f);
		westWall.body->CreateFixture(&westWall.shape, 0.0f);
		/*westWall.fdef.shape = &westWall.shape;
		westWall.fdef.restitution = 1.0f;
		westWall.fixt = westWall.body->CreateFixture(&westWall.fdef);*/

		/*eastWall = Wall(b2Vec2(boardWidth + wallDepth, 0), wallDepth, boardLength);
		eastWall.def.position.Set(eastWall.getPosition().x, eastWall.getPosition().y);
		eastWall.body = world.CreateBody(&eastWall.def);
		eastWall.shape.SetAsBox(eastWall.getWidth() / 2.0f, eastWall.getHeight() / 2.0f);
		eastWall.body->CreateFixture(&eastWall.shape, 0.0f);*/
		eastWall = Wall(b2Vec2(2.8f, 0.625f), wallDepth, boardLength);
		eastWall.def.position.Set(2.8f, 0.625f);
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
		cueBall.def.type = b2_dynamicBody;
		cueBall.def.position.Set(1.35f, 0.625f);
		cueBall.body = world.CreateBody(&cueBall.def);
		//cbshape.m_p.Set(cueBall.getPosition().x, cueBall.getPosition().y);
		cueBall.shape.m_radius = 0.028f; //56mm diameter.
		cueBall.fdef.shape = &cueBall.shape;
		cueBall.fdef.density = 1848.88194565217f; //At least, I think that's the actual density of a pool cue ball.
		cueBall.fdef.restitution = 0.6f;
		cueBall.fdef.friction = 0.2f;
		cueBall.fixt = cueBall.body->CreateFixture(&cueBall.fdef); 
	}

	cueBall.body->ApplyLinearImpulseToCenter(b2Vec2(4.5f, 0), true); 
	//Apply an impulse of (4.5f, 0) to see an inelastic collision. Try (4.6f, 0) and higher and it'll bounce at least once.
}