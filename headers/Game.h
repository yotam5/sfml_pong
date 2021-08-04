#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include "../src/Ball.cpp"
#include "../src/Paddle.cpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Game{
public:
	Game();
	virtual ~Game();
	void update();
	bool isOpen() const;
	void run();
private:
	void init();
	void initWindow();
	void render();
	void pollEvents();
	bool ballWallCollision();
	bool ballPaddleCollision();
	bool outsideWindow() const;
	void updatePlayerPaddle();
	bool ballOutsideWindow;
    sf::RenderWindow *window;
    sf::Event event;
    sf::Font font;
    sf::Text uiText;
    sf::VideoMode videoMode;
    sf::Sprite background;
    Ball ball;
    Paddle paddle;
    Paddle bot_paddle;
};