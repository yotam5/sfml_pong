#pragma once
#include "../headers/Paddle.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Paddle::Paddle(int max_height) {
  this->max_height = max_height;
  this->init();
}

Paddle::Paddle() {}

Paddle::~Paddle() {}

void Paddle::moveUp() {
  this->paddle.move(0, -1 * this->yVelocity);
  this->currentDir = PaddleDirections::UP;
}

void Paddle::moveDown() {
  this->paddle.move(0, this->yVelocity);
  this->currentDir = PaddleDirections::DOWN;
}

void Paddle::init() {
  this->paddle = sf::RectangleShape(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
  this->yVelocity = PADDLE_Y_SPEED;
  this->currentDir = PaddleDirections::NOT_MOVING;
}

void Paddle::automatedMovment(sf::Vector2f ballpos) {
  auto myRecPos = this->paddle.getPosition();
  double max_y = myRecPos.y + PADDLE_HEIGHT;
  double min_y = myRecPos.y;
  double ball_y = ballpos.y;
  if (max_y < ball_y) {
    this->moveDown();
  } else if (ball_y < min_y) {
    this->moveUp();
  }
  else {
  	this->currentDir = PaddleDirections::NOT_MOVING;
  }
}

void Paddle::setPosition(int x, int y) { this->paddle.setPosition(x, y); }

void Paddle::updatePaddleLocation() {
  auto paddlePos = this->paddle.getPosition();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
      paddlePos.y + PADDLE_HEIGHT < this->max_height) {
    this->moveDown();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddlePos.y > 0) {
    this->moveUp();
  }
}

void Paddle::render(sf::RenderTarget &target) { target.draw(this->paddle); }

sf::Vector2f Paddle::getPosition() const { return this->paddle.getPosition(); }
