#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
	//player.setFillColor(sf::Color::Blue);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("textu.png");
	player.setTexture(&playerTexture);

	Animation animation(&playerTexture, sf::Vector2u(4, 2), 0.3f);
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

			//case sf::Event::Resized:
			//	std::cout << "New Window width: " << evnt.size.width << " New Window Height: " << evnt.size.height << std::endl;
			//	break;

			case sf::Event::TextEntered:
				if(evnt.text.unicode < 128)
					printf("%c", evnt.text.unicode);
				break;

			default:
				break;
			}
		}
		//check for input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.move(0.0f, 0.1f);
		}

		//mouse input 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}

		animation.Update(1, deltaTime);
		player.setTextureRect(animation.uvRect);

		window.clear(sf::Color::White);
		window.draw(player);
		window.display();
	}

	return 0;
}