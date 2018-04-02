#pragma once
#include "Box2D\Box2D.h"
#include <SFML\Graphics.hpp>
#include "System.h"

class Wall
{
public:
	Wall();
	Wall(b2Vec2 pos, float width, float height);
	~Wall();
	void SetupShape(b2World world);
	void SetupSprite();
	void Draw(sf::RenderWindow* window);
	void Update();

	b2Vec2 getPosition();
	float getWidth();
	float getHeight();

	b2BodyDef def;
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fdef;
	b2Fixture* fixt;

	sf::RectangleShape renderShape;
private:

	b2Vec2 position;
	float wallWidth;
	float wallHeight;
	//float restitution;
};