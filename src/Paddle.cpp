#pragma once
#include "../headers/Paddle.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Paddle::Paddle()
{
	this->init();
}

Paddle::~Paddle()
{

}

void Paddle::moveUp()
{
	this->paddle.move(0,-1 * this->yVelocity);
}

void Paddle::moveDown()
{
	this->paddle.move(0,this->yVelocity);
}

void Paddle::init()
{
	this->paddle = sf::RectangleShape(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	this->paddle.setPosition(5,0);
	this->yVelocity = PADDLE_Y_SPEED;
}

void Paddle::render(sf::RenderTarget &target)
{
	target.draw(this->paddle);
}