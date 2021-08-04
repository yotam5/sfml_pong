#pragma once

#include "../headers/Game.h"
#include <SFML/Window/Keyboard.hpp>

Game::Game() { this->init(); }

void Game::render() {
  this->window->clear();
  this->ball.render(*this->window);
  this->paddle.render(*this->window);
  this->window->display();
}

Game::~Game() { delete this->window; }

void Game::init() {
  this->initWindow();
  this->ballOutsideWindow = false;
}

void Game::update() {
  this->pollEvents();

  //update paddle location of player
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    this->paddle.moveDown();
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    this->paddle.moveUp();
  }
  this->ball.updatePosition();
  this->ballWallCollision();
}

bool Game::isOpen() const { return this->window->isOpen(); }

void Game::run() {
  while (this->isOpen()) {
    this->update();
    this->render();
  }
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

bool Game::outsideWindow() const {
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
  case 0:
  case 1:
    y -= RADIUS;
    break;
  case 2:
  case 3:
    y += RADIUS;
    break;
  }
  bool wallHit = (y >= SCREEN_HEIGHT || y <= 0);
  if (wallHit) {
    std::cout << "HIT WALL!" << std::endl;
    this->ball.changeYspeed();
    std::cout << this->ball.getVelocity().second << "\n";
  }
  return wallHit;
}