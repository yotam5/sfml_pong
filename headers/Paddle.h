#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#define PADDLE_COLOR White
#define PADDLE_HEIGHT 120
#define PADDLE_WIDTH 10
#define PADDLE_Y_SPEED 12

#ifndef PADDLEDIRECTIONS
#define PADDLEDIRECTIONS
enum class PaddleDirections{UP,DOWN,NOT_MOVING};
#endif

class Paddle
{
public:
	Paddle(int max_height);
	Paddle();
	~Paddle();
	void render(sf::RenderTarget &target);
	void setPosition(int,int);
	sf::Vector2f getPosition() const;
	void updatePaddleLocation();
	void automatedMovment(sf::Vector2f ballpos);
	PaddleDirections getCurrentDirection() const;
	void incrementVelocity();
private:
	PaddleDirections currentDir;
	void moveUp();
	void moveDown(); 
	sf::RectangleShape paddle;
	void init();
	double yVelocity;
	double max_height;
};

