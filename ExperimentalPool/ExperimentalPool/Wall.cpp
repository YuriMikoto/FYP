#include "Wall.h"

/// <summary>
/// Default constructor. Not actually used.
/// </summary>
Wall::Wall() {}

/// <summary>
/// Manual constructor. 
/// </summary>
/// <param name="pos">Position of the top-left of the wall.</param>
/// <param name="width">X-axis width of this wall.</param>
/// <param name="height">Y-axis height of this wall.</param>
Wall::Wall(b2Vec2 pos, float width, float height) :
	position(pos), wallWidth(width), wallHeight(height)
{

}

/// <summary>
/// Destructor.
/// </summary>
Wall::~Wall()
{

}

void Wall::Update()
{
	position = body->GetPosition();
	renderShape.setPosition(sf::Vector2f(position.x * PIXEL_SCALER, position.y * PIXEL_SCALER));
}

/// <summary>
/// There seems to be a problem here, so for now, setup of Box2D shape is done in Game.cpp.
/// </summary>
/// <param name="world">Game world to create the object in.</param>
void Wall::SetupShape(b2World world)
{
	def.position.Set(position.x, -position.y);
	body = world.CreateBody(&def);
	shape.SetAsBox(wallWidth/2.0f, wallHeight/2.0f);
	body->CreateFixture(&shape, 0.0f);
}

/// <summary>
/// Currently sets up a basic SFML rectangle. Will later have textures added in.
/// </summary>
void Wall::SetupSprite()
{
	renderShape.setFillColor(sf::Color::Black);
	renderShape.setOrigin(sf::Vector2f(wallWidth * PIXEL_SCALER/2.0f, wallHeight * PIXEL_SCALER/2.0f));
	renderShape.setPosition(sf::Vector2f(body->GetPosition().x * PIXEL_SCALER, body->GetPosition().y * PIXEL_SCALER));
	renderShape.setSize(sf::Vector2f(wallWidth * PIXEL_SCALER, wallHeight * PIXEL_SCALER));
}

/// <summary>
/// Draw the wall on the render window.
/// </summary>
/// <param name="window">Window to draw on.</param>
void Wall::Draw(sf::RenderWindow* window)
{
	window->draw(renderShape);
}

b2Vec2 Wall::getPosition()
{
	return position;
}

float Wall::getWidth()
{
	return wallWidth;
}

float Wall::getHeight() 
{
	return wallHeight;
}