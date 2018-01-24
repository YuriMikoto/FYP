#pragma once
#include "Box2D\Box2D.h"
#include <SFML\Graphics.hpp>

class Wall
{
public:
	Wall(b2Vec2 pos, float width, float height);
	~Wall();
	void SetupShape(b2World world);
	void SetupSprite();
	void Draw();
	
private:
	b2BodyDef def;
	b2Body* body;
	b2PolygonShape shape;

	b2Vec2 position;
	float wallWidth;
	float wallHeight;
	//float restitution;
};