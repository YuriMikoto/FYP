#pragma once
#include "Box2D/Box2D.h"
#include <SFML\Graphics.hpp>
#include "System.h"

class Ball
{
public:
	Ball();
	Ball(b2Vec2 pos, bool isCue = false);
	~Ball();
	void Draw(sf::RenderWindow* window);
	void Update();
	void SetupSprite(sf::Color color);

	void setActive(bool a);
	void pocket();
	void setID(int val);
	int getID();

	b2Vec2 getPosition();

	b2BodyDef def;
	b2Body* body;
	b2CircleShape shape;
	b2FixtureDef fdef;
	b2Fixture* fixt;

	sf::CircleShape renderShape;
private:
	//b2_pi is a thing.
	int id; //Indicates the number of the ball. 
			//Array ID is not sufficient due to the way collision callbacks work.
			//However, this ID value for a ball will match its entry in the array.
	b2Vec2 position;
	float velocity; //Current speed and direction.
	sf::Texture texture;
	sf::Sprite spr;

	bool active = true; //True until the ball is pocketed.
};
