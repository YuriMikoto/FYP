// author Peter Lowe

#include "Game.h"
#include <iostream>

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

		if (sf::Event::MouseButtonPressed == event.type)
		{
			if (sf::Mouse::Left == event.key.code)
			{
				//Displays a line that indicates the direction you'll be firing the cue ball.
				displayCueLine = true;
			}
		}

		if (sf::Event::MouseButtonReleased == event.type)
		{
			if (sf::Mouse::Left == event.key.code)
			{
				//Switches off the line display.
				displayCueLine = false;

				//Defines the maximum magnitude of the impulse velocity.
				const float MAX_SPEED = 30.0f;

				//Sets the impulse velocity based on mouse position in relation to cue ball position.
				sf::Vector2f direction(balls[0].renderShape.getPosition().x - sf::Mouse::getPosition(m_window).x,
					balls[0].renderShape.getPosition().y - sf::Mouse::getPosition(m_window).y);
				direction *= 0.1f;
				//Calculates the magnitude of the impulse velocity, then limits it if greater than the defined maximum.
				float length = sqrt((direction.x * direction.x) + (direction.y * direction.y));
				if (length > MAX_SPEED)
				{
					direction /= (length / MAX_SPEED);
				}
				//Finally, applies the calculated force.
				balls[0].body->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), true);
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
	for (int i = 0; i < 6; i++)
	{
		pockets[i].Update();
	}

	for (int i = 0; i < BALL_COUNT; i++)
	{
		balls[i].Update();
	}
	//debugConsole();
}

void Game::debugConsole()
{
	//system("CLS");
	std::cout << "Ball position: (" << balls[0].body->GetPosition().x << ", " << balls[0].body->GetPosition().y << ")" << std::endl;
	std::cout << "Ball Velocity: (" << balls[0].body->GetLinearVelocity().x << ", " << balls[0].body->GetLinearVelocity().y << ")" << std::endl;

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

	for (int i = 0; i < 6; i++)
	{
		pockets[i].Draw(&m_window);
	}

	for (int i = 0; i < BALL_COUNT; i++)
	{
		balls[i].Draw(&m_window);
	}

	if (displayCueLine)
	{
		//Creates and draws the "cue line" that appears when preparing a shot.
		sf::Vertex line[] =
		{
			sf::Vertex(balls[0].renderShape.getPosition()),
			sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y))
		};

		line[1].color = sf::Color::Red;

		m_window.draw(line, 2, sf::Lines);
	}

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

	for (int i = 0; i < 6; i++)
	{
		pockets[i].SetupSprite(sf::Color(64, 64, 64, 255));
	}

	balls[0].SetupSprite(sf::Color(240, 240, 240, 255));
	balls[1].SetupSprite(sf::Color(255, 255, 0, 255));
	balls[2].SetupSprite(sf::Color(0, 0, 255, 255));
	balls[3].SetupSprite(sf::Color(255, 0, 0, 255));
	balls[4].SetupSprite(sf::Color(192, 0, 192, 255));
	balls[5].SetupSprite(sf::Color(255, 128, 0, 255));
	balls[6].SetupSprite(sf::Color(0, 192, 0, 255));
	balls[7].SetupSprite(sf::Color(192, 0, 0, 255));
	balls[8].SetupSprite(sf::Color(0, 0, 0, 255));
	balls[9].SetupSprite(sf::Color(128, 128, 128, 255));
}

/// <summary>
/// Creates the four walls of the board in Box2D.
/// </summary>
void Game::setupBoard()
{
	//Walls
	{
		northWall = Wall(b2Vec2(1.4f, 1.25f), boardWidth, wallDepth);
		northWall.def.position.Set(1.4f+wallDepth / 2.0, 1.25f + wallDepth / 2.0);
		northWall.body = world.CreateBody(&northWall.def);
		northWall.shape.SetAsBox(boardWidth / 2.0f, wallDepth / 2.0f);
		northWall.body->CreateFixture(&northWall.shape, 0.0f);
		northWall.fdef.shape = &northWall.shape;
		northWall.fdef.filter.categoryBits = WALL;
		northWall.fdef.restitution = wallRestitution;
		northWall.fixt = northWall.body->CreateFixture(&northWall.fdef);

		southWall = Wall(b2Vec2(1.4f, 0), boardWidth, wallDepth);
		southWall.def.position.Set(1.4f + wallDepth / 2.0, 0 + wallDepth / 2.0);
		southWall.body = world.CreateBody(&southWall.def);
		southWall.shape.SetAsBox(boardWidth / 2.0f, wallDepth / 2.0f);
		southWall.body->CreateFixture(&southWall.shape, 0.0f);
		southWall.fdef.shape = &southWall.shape;
		southWall.fdef.filter.categoryBits = WALL;
		southWall.fdef.restitution = wallRestitution;
		southWall.fixt = southWall.body->CreateFixture(&southWall.fdef);

		westWall = Wall(b2Vec2(0, 0), wallDepth, boardLength);
		westWall.def.position.Set(0 + wallDepth / 2.0, 0.625f + wallDepth / 2.0);
		westWall.body = world.CreateBody(&westWall.def);
		westWall.shape.SetAsBox(wallDepth / 2.0f, boardLength / 2.0f);
		westWall.body->CreateFixture(&westWall.shape, 0.0f);
		westWall.fdef.shape = &westWall.shape;
		westWall.fdef.filter.categoryBits = WALL;
		westWall.fdef.restitution = wallRestitution;
		westWall.fixt = westWall.body->CreateFixture(&westWall.fdef);

		eastWall = Wall(b2Vec2(2.8f, 0.625f), wallDepth, boardLength);
		eastWall.def.position.Set(2.8f + wallDepth/2.0, 0.625f + wallDepth/2.0);
		eastWall.body = world.CreateBody(&eastWall.def);
		eastWall.shape.SetAsBox(wallDepth / 2.0f, boardLength / 2.0f);
		eastWall.body->CreateFixture(&eastWall.shape, 0.0f);
		eastWall.fdef.shape = &eastWall.shape;
		eastWall.fdef.filter.categoryBits = WALL;
		eastWall.fdef.restitution = wallRestitution;
		eastWall.fixt = eastWall.body->CreateFixture(&eastWall.fdef);
	}

	//Balls
	{
		for (int i = 0; i < BALL_COUNT; i++)
		{
			balls[i].def.type = b2_dynamicBody; 
			balls[i].def.linearDamping = ballLinearDamping;
			balls[i].def.angularDamping = ballAngularDamping;
			balls[i].body = world.CreateBody(&balls[i].def);
			balls[i].shape.m_radius = ballRadius;
			balls[i].fdef.shape = &balls[i].shape;
			balls[i].fdef.filter.categoryBits = BALL;
			balls[i].fdef.density = ballDensity;
			balls[i].fdef.restitution = ballRestitution;
			balls[i].fdef.friction = ballFriction;
			balls[i].fixt = balls[i].body->CreateFixture(&balls[i].fdef);
		}

		balls[0].body->SetTransform(b2Vec2(boardWidth*0.75f + wallDepth, boardLength / 2.0f), 0); //Cue ball.
		//9-Ball Rack: 1 at the front, closest to the cue; 9 in the middle. 
		balls[1].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth, boardLength / 2.0f), 0);
		balls[9].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 4), boardLength / 2.0f), 0);
		//9-Ball Rack: Other balls are placed randomly to make a diamond formation.
		balls[2].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 4), boardLength / 2.0f + (ballRadius*2)), 0);
		balls[3].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 4), boardLength / 2.0f - (ballRadius*2)), 0);
		balls[4].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 2), boardLength / 2.0f + (ballRadius)), 0);
		balls[5].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 2), boardLength / 2.0f - (ballRadius)), 0);
		balls[6].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 6), boardLength / 2.0f + (ballRadius)), 0);
		balls[7].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 6), boardLength / 2.0f - (ballRadius)), 0);
		balls[8].body->SetTransform(b2Vec2(boardWidth*0.25f + wallDepth - (ballRadius * 8), boardLength / 2.0f), 0);
	}

	//Pockets
	{
		for (int i = 0; i < 6; i++)
		{
			pockets[i].def.type = b2_staticBody;
			pockets[i].body = world.CreateBody(&pockets[i].def);
			pockets[i].shape.m_radius = ballRadius*2;
			pockets[i].fdef.shape = &pockets[0].shape;
			pockets[i].fdef.isSensor = true;
			pockets[i].fdef.filter.categoryBits = POCKET;
			pockets[i].fdef.filter.maskBits = BALL;
			pockets[i].fdef.density = ballDensity;
			pockets[i].fdef.restitution = ballRestitution;
			pockets[i].fdef.friction = ballFriction;
			pockets[i].fixt = pockets[i].body->CreateFixture(&pockets[i].fdef);
		}
		
		pockets[0].body->SetTransform(b2Vec2(wallDepth, wallDepth), 0);
		pockets[1].body->SetTransform(b2Vec2(boardWidth/2+wallDepth, wallDepth*0.75), 0);
		pockets[2].body->SetTransform(b2Vec2(boardWidth + wallDepth, wallDepth), 0);
		pockets[3].body->SetTransform(b2Vec2(wallDepth, boardLength-wallDepth), 0);
		pockets[4].body->SetTransform(b2Vec2(boardWidth/2+wallDepth, boardLength - wallDepth*0.75), 0);
		pockets[5].body->SetTransform(b2Vec2(boardWidth+wallDepth, boardLength - wallDepth), 0);
	}
}