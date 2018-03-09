#include "Pocket.h"

Pocket::Pocket() {}

Pocket::Pocket(b2Vec2 pos) :
	position(pos)
{

}

Pocket::~Pocket()
{

}

void Pocket::Draw(sf::RenderWindow* window)
{
	window->draw(renderShape);
}

void Pocket::Update()
{
	position = body->GetPosition();
	renderShape.setPosition(sf::Vector2f(position.x * 500, position.y * 500));

	if (body->GetLinearVelocity().Length() < 0.01)
	{
		body->SetLinearVelocity(b2Vec2(0, 0));
	}
}

void Pocket::SetupSprite(sf::Color color)
{
	renderShape.setFillColor(color);
	renderShape.setRadius(shape.m_radius * 500);
	renderShape.setOrigin(sf::Vector2f(renderShape.getRadius(), renderShape.getRadius()));
	renderShape.setPosition(sf::Vector2f(position.x * 500, position.y * 500));
}

b2Vec2 Pocket::getPosition()
{
	return position;
}