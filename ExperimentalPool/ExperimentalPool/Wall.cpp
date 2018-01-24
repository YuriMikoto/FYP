#include "Wall.h"

Wall::Wall(b2Vec2 pos, float width, float height) :
	position(pos), wallWidth(width), wallHeight(height)
{

}

Wall::~Wall()
{

}

void Wall::SetupShape(b2World world)
{
	def.position.Set(position.x, position.y);
	body = world.CreateBody(&def);
	shape.SetAsBox(wallWidth/2.0f, wallHeight/2.0f);
	body->CreateFixture(&shape, 0.0f);
}

void Wall::SetupSprite()
{

}

void Wall::Draw()
{

}