#pragma once

#include "../headers/Ball.h"

Ball::Ball() { this->init(); }

Ball::~Ball() {
  // delete this->ball;
}

sf::Vector2f Ball::getPosition() const { return this->ball.getPosition(); }

void Ball::changeYspeed() {
  this->yVelocity *= -1;
  this->updateDirection();
}

void Ball::changeXspeed() {
  this->xVelocity *= -1;
  this->updateDirection();
}

void Ball::updateDirection() {
  int dirIndex = 0;
  dirIndex += (this->yVelocity > 0) ? 2 : 0;
  dirIndex += (this->xVelocity > 0) ? 1 : 0;
  this->currentDirection = static_cast<BallDirection>(dirIndex);
}

void Ball::updatePosition() {
  auto myPos = this->ball.getPosition();
  this->ball.move(this->xVelocity, this->yVelocity);
}

void Ball::init() {
  this->ball = sf::CircleShape(RADIUS);
  this->ball.setOutlineColor(sf::Color::COLOR);
  this->ball.setOrigin(RADIUS, RADIUS);
  this->ball.setPosition(400,10);
  this->xVelocity = BALL_X_SPEED;
  this->yVelocity = BALL_Y_SPEED;
  this->setVelocity(BallDirection::DOWN_LEFT);
}

void Ball::render(sf::RenderTarget &target) { target.draw(ball); }

BallDirection Ball::getDirection() const { return this->currentDirection; }

void Ball::setVelocity(BallDirection balldir) {
  this->currentDirection = balldir;
  int dir = static_cast<int>(balldir);
  double ballxspeed = fabs(this->xVelocity);
  double ballyspeed = fabs(this->yVelocity);
  this->xVelocity = (dir % 2 == 0) ? (-1) * ballxspeed : ballxspeed;
  this->yVelocity = (dir > 1) ? ballyspeed : (-1) * ballyspeed;
}

std::pair<double, double> Ball::getVelocity() const {
  return std::make_pair(this->xVelocity, this->yVelocity);
}

void Ball::incrementVelocity()
{
  this->yVelocity *= 1.25; 
}

void Ball::decrementVelocity()
{
  double yVelocityDec = this->yVelocity;
  yVelocityDec *= 0.90;
  if(yVelocityDec > BALL_Y_SPEED)
  {
    this->yVelocity = yVelocityDec;
  }
}
