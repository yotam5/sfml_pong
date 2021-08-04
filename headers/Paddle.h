#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#define PADDLE_COLOR White
#define PADDLE_HEIGHT 120
#define PADDLE_WIDTH 10
#define PADDLE_Y_SPEED 8

class Paddle
{
public:
	Paddle();
	~Paddle();
	void render(sf::RenderTarget &target);
	void moveUp();
	void moveDown();
private:
	sf::RectangleShape paddle;
	void init();
	int yVelocity;
};