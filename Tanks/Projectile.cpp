#include "Projectile.h"

#include <iostream>
using namespace std;
Projectile::Projectile(SDL_Texture* texture, Constants::Direction dir, int x, int y, Constants::ProjectileOwner owner)
{
	this->texture = texture;
	active = true;
	this->owner = owner;

	this->x = x;
	this->y = y;

	drawRect = new SDL_Rect();
	drawRect->x = this->x;
	drawRect->y = this->y;
	
	SDL_QueryTexture(texture, NULL, NULL, &drawRect->w, &drawRect->h);

	switch (dir)
	{
	case Constants::Up:
		speedy = -Constants::PROJECTILE_SPEED;
		break;
	case Constants::Down:
		speedy = Constants::PROJECTILE_SPEED;
		break;
	case Constants::Left:
		speedx = -Constants::PROJECTILE_SPEED;
		break;
	case Constants::Right:
		speedx = Constants::PROJECTILE_SPEED;
		break;
	}
}


Projectile::~Projectile()
{
	//SDL_DestroyTexture(texture);
	delete drawRect;
}

void Projectile::Update(Uint32 deltaTime)
{
	float dx = speedx * deltaTime;
	float dy = speedy * deltaTime;

	x += dx;
	y += dy;
	drawRect->x = x;
	drawRect->y = y;

	if (drawRect->x >= Constants::SCREEN_WIDTH || drawRect->x+drawRect->h <= 0 || drawRect->y <= 0 || drawRect->y >= Constants::SCREEN_HEIGHT)
		active = false;
}

void Projectile::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, drawRect);
}
