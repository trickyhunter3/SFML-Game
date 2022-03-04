#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT_X = 1024.0f;
static const float VIEW_HEIGHT_Y = 1024.0f;

void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

	view.setSize(1280 * aspectRatio, 720);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1280, 720));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("tux.png");

	sf::Vector2u offset(0, 4);
	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, offset, 200);

	std::vector<Platform> platforms;
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 000.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

	float deltaTime = 0.0f;
    sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 30.0f)
			deltaTime = 1.0f / 30.0f;

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				ResizeView(window, view);
				break;

			default:
				break;
			}
		}

		player.Update(deltaTime);

		sf::Vector2f direction;
		Collider playerCollider = player.GetCollider();

		for (Platform& platform : platforms)
			if (platform.GetCollider().CheckCollision(playerCollider, direction, 0.9f))
				player.OnCollision(direction);

		view.setCenter(player.GetPosition());

		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		player.Draw(window);

		for (Platform& platform : platforms)
			platform.Draw(window);
		window.display();
	}

	return 0;
}