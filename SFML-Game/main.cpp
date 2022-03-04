#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	sf::Texture playerTexture;
	playerTexture.loadFromFile("tux.png");

	sf::Vector2u offset(0, 4);
	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.0f, offset);

	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f));

	float deltaTime = 0.0f;
    sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

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

		Collider playerCollider = player.GetCollider();

		platform1.GetCollider().CheckCollision(playerCollider, 0.9f);
		platform2.GetCollider().CheckCollision(playerCollider, 0.9f);

		view.setCenter(player.GetPosition());

		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		player.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);
		window.display();
	}

	return 0;
}