#pragma once

#include "../headers/Game.h"
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Keyboard.hpp>

Game::Game() { this->init(); }

void Game::render() {
  this->window->clear();
  this->ball.render(*this->window);
  this->paddle.render(*this->window);
  this->bot_paddle.render(*this->window);
  this->window->display();
}

Game::~Game() { delete this->window; }

void Game::init() {
  this->initWindow();
  this->initVariables();
}

void Game::initVariables() {
  this->winner = false;
  this->paddle = Paddle(SCREEN_HEIGHT);
  this->bot_paddle = Paddle(SCREEN_HEIGHT);
  this->paddle.setPosition(10, SCREEN_HEIGHT / 2.0);
  this->bot_paddle.setPosition(SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2.0);
  this->winner = false;
}

void Game::update() {
  this->pollEvents();
  this->updatePlayerPaddle();
  this->ball.updatePosition();
  this->bot_paddle.automatedMovment(this->ball.getPosition());
  this->ballPaddleCollision();
  this->ballWallCollision();
  this->winner = this->ballOutsideWindow();
}

void Game::updatePlayerPaddle() { this->paddle.updatePaddleLocation(); }
bool Game::isOpen() const { return this->window->isOpen(); }

void Game::run() {
  while (this->isOpen() && !this->winner) {
    this->update();
    this->render();
  }
  sf::sleep(sf::seconds(3));
}

void Game::initWindow() {
  this->videoMode.height = SCREEN_HEIGHT;
  this->videoMode.width = SCREEN_WIDTH;
  this->window = new sf::RenderWindow(this->videoMode, "Pong",
                                      sf::Style::Titlebar | sf::Style::Close);
  // init frame rate
  this->window->setFramerateLimit(60); // limit frame rate and make game
                                       // playable

  // center
  auto desktop = sf::VideoMode::getDesktopMode();
  auto center =
      sf::Vector2i(desktop.width / 4,
                   desktop.height / 4); // for center becuse it set top left
  window->setPosition(center);
}

void Game::pollEvents() {
  while (this->window->pollEvent(this->event)) {
    int eventType = this->event.type;
    switch (eventType) {
    case sf::Event::Closed:
      this->window->close();
      break;
    }
  }
}

bool Game::ballOutsideWindow() const {
  bool outsideWall = false;
  auto ballPos = this->ball.getPosition();
  if (ballPos.x < 0 || ballPos.x > SCREEN_WIDTH) {
    outsideWall = true;
  } else if (ballPos.y > SCREEN_HEIGHT || ballPos.y < 0) {
    outsideWall = true;
  }
  return outsideWall;
}

bool Game::ballWallCollision() {
  auto ballPos = this->ball.getPosition();
  auto ballDir = this->ball.getDirection();
  int dirInt = static_cast<int>(ballDir); // 0-3
  int y = ballPos.y;

  switch (dirInt) {
  case 0: // up
  case 1:
    y -= RADIUS;
    break;
  case 2: // down
  case 3:
    y += RADIUS;
    break;
  }
  bool wallHit = (y >= SCREEN_HEIGHT || y <= 0);
  if (wallHit) {
    DEBUG("HIT WALL!");
    this->ball.changeYspeed();
    std::cout << this->ball.getVelocity().second << "\n";
  }
  return wallHit;
}

bool Game::ballPaddleCollision() {
  auto ballPos = this->ball.getPosition();
  auto ballDir = this->ball.getDirection();
  int dirInt = static_cast<int>(ballDir); // 0-3
  int x = ballPos.x;
  switch (dirInt) {
  case 0: // left
  case 2:
    x -= RADIUS;
    break;
  case 1: // right
  case 3:
    x += RADIUS;
    break;
  }
  // currently only to left paddle
  auto paddlePos = this->paddle.getPosition();
  auto botPaddlePos = this->bot_paddle.getPosition();
  paddlePos.x += PADDLE_WIDTH;

  bool hitLeft = paddlePos.x >= x && paddlePos.y <= ballPos.y &&
                 paddlePos.y + PADDLE_HEIGHT >= ballPos.y;

  bool hitRight = x >= botPaddlePos.x && botPaddlePos.y <= ballPos.y &&
                  botPaddlePos.y + PADDLE_HEIGHT >= ballPos.y;

  if (hitLeft || hitRight) {
    auto &paddleHit = (hitLeft) ? this->paddle : this->bot_paddle;

    BallDirection ballDirection = this->ball.getDirection();
    int ballDirectionValue = static_cast<int>(ballDirection);
    int paddleDirectionValue =
        static_cast<int>(paddleHit.getCurrentDirection());
    DEBUG(this->ball.getVelocity().second);
    this->paddle.incrementVelocity();
    this->bot_paddle.incrementVelocity();
    switch (ballDirectionValue) {
    case 0: // up
    case 1:
      DEBUG("BALL UP");
      switch (paddleDirectionValue) {
      case 0:
        this->ball.incrementVelocity();
        break;
      case 1:
        this->ball.decrementVelocity();
        break;
      }
      break;
    case 2: // down
    case 3:
      DEBUG("BALL DOWN");
      switch (paddleDirectionValue) {
      case 0:
        this->ball.decrementVelocity();
        break;
      case 1:
        this->ball.incrementVelocity();
        break;
      }
      break;
    }
    DEBUG(this->ball.getVelocity().second);
    ballDirectionValue += (ballDirectionValue % 2 == 0) ? 1 : -1;
    BallDirection newDir = static_cast<BallDirection>(ballDirectionValue);
    this->ball.setVelocity(newDir);
  }
}
