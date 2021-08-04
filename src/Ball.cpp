#pragma once

#include "../headers/Ball.h"

Ball::Ball()
{
	this->init();
}


Ball::~Ball()
{
	//delete this->ball;
}

sf::Vector2f Ball::getPosition() const
{
	return this->ball.getPosition();
}

void Ball::changeYspeed()
{
	this->yVelocity*=-1;
	this->updateDirection();

}

void Ball::changeXspeed()
{
	this->xVelocity*=-1;
	this->updateDirection();
}

void Ball::updateDirection()
{
	int dirIndex = 0;
	dirIndex += (this->yVelocity > 0 ) ? 2 : 0;
	dirIndex += (this->xVelocity > 0 ) ? 1 : 0;
	this->currentDirection = static_cast<BallDirection>(dirIndex);
}

void Ball::updatePosition()
{
	auto myPos = this->ball.getPosition();
	this->ball.move(this->xVelocity,this->yVelocity);
}

void Ball::init()
{
	this->ball = sf::CircleShape(RADIUS);
	this->ball.setOutlineColor(sf::Color::COLOR);
	this->ball.setOrigin(RADIUS,RADIUS);
	this->ball.setPosition(40,40);
	this->currentDirection = BallDirection::DOWN_RIGHT;
	this->xVelocity = BALL_X_SPEED;
	this->yVelocity = BALL_Y_SPEED;
}

void Ball::render(sf::RenderTarget &target)
{
    target.draw(ball);
}

BallDirection Ball::getDirection() const
{
	return this->currentDirection;
}

std::pair<int,int> Ball::getVelocity() const
{
	return std::make_pair(this->xVelocity,this->yVelocity);
}