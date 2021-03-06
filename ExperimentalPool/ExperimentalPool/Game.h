// author Peter Lowe
#ifndef GAME
#define GAME

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Box2d\Box2d.h"

#include "Wall.h"
#include "Ball.h"
#include "Pocket.h"
#include "System.h"

class NewContactListener : public b2ContactListener
{
	bool checkContactComponents(b2Contact* contact, Ball*& ball, Ball*& pocket)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		//Make sure one and only one of the fixtures is a sensor using bitwise XOR.
		if (!(fixtureA->IsSensor() ^ fixtureB->IsSensor()))
			return false;

		Ball* entityA = static_cast<Ball*>(fixtureA->GetBody()->GetUserData());
		Ball* entityB = static_cast<Ball*>(fixtureB->GetBody()->GetUserData());

		if (fixtureA->IsSensor()) { //...then fixtureA must be the pocket.
			pocket = entityA;
			ball = entityB;
		}
		else { //...fixtureB must be the pocket.
			pocket = entityB;
			ball = entityA;
		}
		return true;
	}

	void BeginContact(b2Contact* contact) {
		Ball* ball;
		Ball* pocket;
		if (checkContactComponents(contact, ball, pocket))
		{
			ball->setActive(false);
			//ball->body->SetTransform(b2Vec2(ball->getID() * ball->renderShape.getRadius() * 1.2f, 1.35f * 1.2f), 0);
			//Maybe a ball's "active" variable shouldn't determine whether or not it draws, but instead...
			//If "active" == false, it is queued up to be moved outside the board on the next update.
			std::cout << "Ball-pocket contact begin." << std::endl;
		}
	}

	void EndContact(b2Contact* contact) {
		Ball* ball;
		Ball* pocket;
		if (checkContactComponents(contact, ball, pocket))
		{
			std::cout << "Ball-pocket contact end." << std::endl;
		}
	}
};

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	static const int BALL_COUNT = 10;

	b2World world = b2World(b2Vec2(0, 0));
	const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 8;
	const int32 positionIterations = 3;
	bool displayCueLine = false;

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void setupBoard();
	void resetGame();

	NewContactListener conlistInstance;

	Wall northWall;
	Wall southWall;
	Wall eastWall;
	Wall westWall;

	//Ball cueBall;
	Ball balls[BALL_COUNT];
	Ball pockets[6];

	enum EntityTypes {
		WALL = 0x0001,
		BALL = 0x0002,
		POCKET = 0x0004
	};

	void debugConsole();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game



	float boardWidth = 2.7f; //North/South walls' width.
	float boardLength = 1.35f; //East/West walls' height.
	float wallDepth = 0.1f; //Width of each wall between the inner boundary and the outer edge of the board.
	float wallRestitution = 0.6f;

	float ballRadius = 0.028f;
	float ballRestitution = 0.96f;
	float ballFriction = 0.0f; //0.2f;
	float ballDensity = 1848.88194565217f;
	float ballLinearDamping = 0.5f;
	float ballAngularDamping = 0.01f;

	//Box2D is tuned for meters, kilograms, and seconds. So you can consider the extents to be in meters.
	// Box2D generally works best when objects are the size of typical real world objects. For example, a barrel is about 1 meter tall.
	// -Box2D manual, section 2.2.

	//Board dimensions can be changed through the options menu, but require a new game before the changes can be applied.
	//The width and height can be changed separately; pool tables are traditionally 2:1 ratio, but what if they weren't?
	//Accepted tournament dimensions are 9ft (2.7m) and 8ft (2.4m) tables. The former will be the default value. 
	//Others are possible, and will be available in the options menu. For example, pub and home tables are typically 7ft (2.1m).

};

#endif // !GAME

