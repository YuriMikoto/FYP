#include "Ball.h"

Ball::Ball() {}

Ball::Ball(b2Vec2 pos, bool isCue) : 
	position(pos), cue(isCue)
{

}

Ball::~Ball()
{

}

void Ball::Draw(sf::RenderWindow* window)
{
	window->draw(renderShape);
}

void Ball::Update()
{
	position = body->GetPosition();
	renderShape.setPosition(sf::Vector2f(position.x * 500, position.y * 500));
}

void Ball::SetupSprite()
{
	renderShape.setFillColor(sf::Color(200, 200, 200, 255));
	renderShape.setPosition(sf::Vector2f(position.x * 500, position.y * 500));
	renderShape.setRadius(shape.m_radius * 500);
}

b2Vec2 Ball::getPosition()
{
	return position;
}