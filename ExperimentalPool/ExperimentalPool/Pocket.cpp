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
	renderShape.setPosition(sf::Vector2f(position.x * PIXEL_SCALER, position.y * PIXEL_SCALER));

	if (body->GetLinearVelocity().Length() < 0.01)
	{
		body->SetLinearVelocity(b2Vec2(0, 0));
	}
}

void Pocket::SetupSprite(sf::Color color)
{
	renderShape.setFillColor(color);
	renderShape.setRadius(shape.m_radius * PIXEL_SCALER);
	renderShape.setOrigin(sf::Vector2f(renderShape.getRadius(), renderShape.getRadius()));
	renderShape.setPosition(sf::Vector2f(position.x * PIXEL_SCALER, position.y * PIXEL_SCALER));
}

b2Vec2 Pocket::getPosition()
{
	return position;
}