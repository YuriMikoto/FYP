#pragma once
#include "Box2D/Box2D.h"
#include <SFML\Graphics.hpp>

class Ball
{
public:
	Ball(sf::Vector2f position, bool cue);
	~Ball();
	void Draw(sf::RenderWindow &window);
	void Update();
	void SetupSprite();
private:
	//b2_pi is a thing.
	sf::Vector2f position;
	float velocity; //Current speed and direction.
	sf::Texture texture;
	sf::Sprite spr;
};
