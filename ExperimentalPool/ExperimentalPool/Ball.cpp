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
	if (active)
	window->draw(renderShape);
}

void Ball::Update()
{
	position = body->GetPosition();
	renderShape.setPosition(sf::Vector2f(position.x * 500, position.y * 500));

	if (body->GetLinearVelocity().Length() < 0.01)
	{
		body->SetLinearVelocity(b2Vec2(0, 0));
	}
}

void Ball::SetupSprite(sf::Color color)
{
	renderShape.setFillColor(color);
	renderShape.setRadius(shape.m_radius * 500);
	renderShape.setOrigin(sf::Vector2f(renderShape.getRadius(), renderShape.getRadius()));
	renderShape.setPosition(sf::Vector2f(position.x * 500, position.y * 500));
}

b2Vec2 Ball::getPosition()
{
	return position;
}