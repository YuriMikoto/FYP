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

	b2Vec2 getPosition();

	b2BodyDef def;
	b2Body* body;
	b2CircleShape shape;
	b2FixtureDef fdef;
	b2Fixture* fixt;

	sf::CircleShape renderShape;
private:
	//b2_pi is a thing.
	bool cue; //True if this is the cue ball, false otherwise. 
	b2Vec2 position;
	float velocity; //Current speed and direction.
	sf::Texture texture;
	sf::Sprite spr;

	bool active = true; //True until the ball is pocketed.
};
