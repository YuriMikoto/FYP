#include "Ball.h"

Ball::Ball() {}

Ball::Ball(b2Vec2 pos, bool isCue) : 
	position(pos)
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
	renderShape.setPosition(sf::Vector2f(position.x * PIXEL_SCALER, position.y * PIXEL_SCALER));

	if (body->GetLinearVelocity().Length() < 0.01)
	{
		body->SetLinearVelocity(b2Vec2(0, 0));
	}

	if (!active)
	{
		pocket();
	}
}

void Ball::SetupSprite(sf::Color color)
{
	renderShape.setFillColor(color);
	renderShape.setRadius(shape.m_radius * PIXEL_SCALER);
	renderShape.setOrigin(sf::Vector2f(renderShape.getRadius(), renderShape.getRadius()));
	renderShape.setPosition(sf::Vector2f(position.x * PIXEL_SCALER, position.y * PIXEL_SCALER));
}

void Ball::setActive(bool a)
{
	active = a;
	body->SetLinearVelocity(b2Vec2(0, 0));

}

void Ball::pocket()
{							//(ID * radius * 2   ) + radius,(Width * 1.2 )
	body->SetTransform(b2Vec2((id * 0.028f * 2.0f) + 0.028f, 1.35f * 1.2f), 0);
}

void Ball::setID(int val)
{
	id = val;
}

int Ball::getID()
{
	return id;
}

b2Vec2 Ball::getPosition()
{
	return position;
}