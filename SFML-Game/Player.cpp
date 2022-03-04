#include "Player.h"

const float GRAVITY = 981.0f;

Player::Player(sf::Texture * texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2u textureOffset, float jumpHeight) : animation(texture, imageCount, switchTime, textureOffset)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x = 0.1f;//how fast to stop *

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		velocity.x -= speed;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
	{
		canJump = false;

		//squre root (2.0f * gravity * jumpheight)
		velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
	}

	velocity.y += GRAVITY * deltaTime;

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//collision of the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//collision of the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//collision of the bottom.
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//collision of the top.
		velocity.y = 0.0f;
	}
}
