#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <bits/stdc++.h>

#define RADIUS 10
#define COLOR White
#define BALL_X_SPEED 0
#define BALL_Y_SPEED 5

#ifndef BALLDIR
#define BALLDIR
 enum class BallDirection{UP_LEFT,UP_RIGHT,DOWN_LEFT,DOWN_RIGHT};
#endif

class Ball
{
public:
	Ball();
	~Ball();
	void render(sf::RenderTarget &target);
	sf::Vector2f getPosition() const;
	BallDirection getDirection() const;
	void changeYspeed(); 
	void changeXspeed();
	void updatePosition();
	void updateDirection();
	std::pair<int,int> getVelocity() const;
private:
	sf::CircleShape ball;
	BallDirection currentDirection;
	int xVelocity;
	int yVelocity;
	void init();
};