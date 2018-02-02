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
}

/// <summary>
/// Draw all renderable objects in the game from here.
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
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
}

/// <summary>
/// Creates the four walls of the board in Box2D.
/// </summary>
void Game::setupBoard()
{
	northWall = Wall(b2Vec2(wallDepth, 0), boardWidth, wallDepth);
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
	northWall.def.position.Set(northWall.getPosition().x, northWall.getPosition().y);
	northWall.body = world.CreateBody(&northWall.def);
	northWall.shape.SetAsBox(northWall.getWidth() / 2.0f, northWall.getHeight() / 2.0f);
	northWall.body->CreateFixture(&northWall.shape, 0.0f);
}