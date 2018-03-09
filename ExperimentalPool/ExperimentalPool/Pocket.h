#pragma once
#include "Box2D/Box2D.h"
#include <SFML\Graphics.hpp>

class Pocket
{
public:
	Pocket();
	Pocket(b2Vec2 pos);
	~Pocket();
	void Draw(sf::RenderWindow* window);
	void Update();
	void SetupSprite(sf::Color color);

	b2Vec2 getPosition();

	b2BodyDef def;
	b2Body* body;
	b2CircleShape shape;
	b2FixtureDef fdef;
	b2Fixture* fixt;

	sf::CircleShape renderShape;
private:
	b2Vec2 position;
	sf::Texture texture;
	sf::Sprite spr;
};
