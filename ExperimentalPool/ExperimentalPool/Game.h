// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Box2d\Box2d.h"

#include "Wall.h"
#include "Ball.h"

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
	b2World world = b2World(b2Vec2(0, 0));
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void setupBoard();

	Wall northWall;
	Wall southWall;
	Wall eastWall;
	Wall westWall;

	Ball cueBall;

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

	//Box2D is tuned for meters, kilograms, and seconds. So you can consider the extents to be in meters.
	// Box2D generally works best when objects are the size of typical real world objects. For example, a barrel is about 1 meter tall.
	// -Box2D manual, section 2.2.

	//Board dimensions can be changed through the options menu, but require a new game before the changes can be applied.
	//The width and height can be changed separately; pool tables are traditionally 2:1 ratio, but what if they weren't?
	//Accepted tournament dimensions are 9ft (2.7m) and 8ft (2.4m) tables. The former will be the default value. 
	//Others are possible, and will be available in the options menu. For example, pub and home tables are typically 7ft (2.1m).

};

#endif // !GAME

