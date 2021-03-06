#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>



int main()
{
	//SEXE
	//Création de la fenêtre
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Assassin's Creed : Odyssey");
	//Création de l'énumération des 4 différentes directions + initialisation de l'animation vers "bas"
	enum Dir { Right, Left, Down, Up };
	sf::Vector2i anim(2, Down);

	//Initialisation et chargement du son
	sf::SoundBuffer xbox;
	if (!xbox.loadFromFile("sonxbox.flac"))
	{
		return -1;
	}
	sf::Sound sonXbox;
	sonXbox.setBuffer(xbox);

	sf::SoundBuffer issou;
	if (!issou.loadFromFile("issou.wav"))
	{
		return -1;
	}
	sf::Sound sonIssou;
	sonIssou.setBuffer(issou);

	//Initialisation et chargement de la texture personnage
	sf::Texture textureMecChelou;
	if (!textureMecChelou.loadFromFile("mecsitas.png"))
	{
		std::cout << "Erreur chargement de mecsitas.png" << std::endl;
	}

	sf::Sprite spriteMecChelou;
	spriteMecChelou.setTexture(textureMecChelou);
	spriteMecChelou.setScale(sf::Vector2f(4.f, 4.f));

	sf::Texture textureArme;
	if (!textureArme.loadFromFile("mas36test.png"))
	{
		std::cout << "Erreur chargement de mas36test.png" << std::endl;
	}

	sf::Sprite spriteArme;
	spriteArme.setTexture(textureArme);
	spriteArme.setScale(sf::Vector2f(4.f, 4.f));

	sf::Texture textureViseur;
	if (!textureViseur.loadFromFile("curseur.png"))
	{
		std::cout << "Erreur de chargement de curseur.png" << std::endl;
	}

	sf::Sprite spriteViseur;
	spriteViseur.setTexture(textureViseur);
	spriteViseur.setScale(sf::Vector2f(3.f, 3.f));

	sf::Texture textureBalle;
	if (!textureBalle.loadFromFile("balle.png"))
	{
		std::cout << "Erreur de chargement de balle.png" << std::endl;
	}

	sf::Sprite spriteBalle;
	spriteBalle.setTexture(textureBalle);
	spriteBalle.setScale(sf::Vector2f(2.f, 2.f));


	//Initialisation des variables vecteurs
	sf::Vector2i mousePosition;
	sf::Vector2i tirPosition;

	//Diverses variables
	int i = 10000;
	int limiteFPS = 0;
	int vitesseFPS = 200;
	float vitesse = 0.15;
	int longueurX = 0;
	int longueurY = 0;
	window.setMouseCursorVisible(false);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Début du code
		mousePosition = sf::Mouse::getPosition(window);
		spriteViseur.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));

		spriteArme.setPosition(spriteMecChelou.getPosition().x+40, spriteMecChelou.getPosition().y);

		longueurX = (mousePosition.x) - (spriteMecChelou.getPosition().x + 50);
		longueurY = (mousePosition.y) - (spriteMecChelou.getPosition().y + 50);

		limiteFPS++;

		window.clear(sf::Color::Red);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			vitesseFPS = 125;
			vitesse = 0.55;
		}
		else
		{
			vitesseFPS = 200;
			vitesse = 0.15;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			anim.y = Up;
			spriteMecChelou.move(sf::Vector2f(0, -vitesse));
			spriteArme.move(sf::Vector2f(0, -vitesse));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			anim.y = Down;
			spriteMecChelou.move(sf::Vector2f(0, vitesse));
			spriteArme.move(sf::Vector2f(0, vitesse));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			anim.y = Left;
			spriteMecChelou.move(sf::Vector2f(-vitesse, 0));
			spriteArme.move(sf::Vector2f(-vitesse, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			anim.y = Right;
			spriteMecChelou.move(sf::Vector2f(vitesse, 0));
			spriteArme.move(sf::Vector2f(vitesse, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			spriteMecChelou.setRotation(20.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			spriteMecChelou.setRotation(-20.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			sonIssou.play();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			spriteBalle.setPosition(spriteMecChelou.getPosition().x + 50, spriteMecChelou.getPosition().y + 50);
			sonXbox.play();
			i = 0;
		}
		if (i < 1500)
		{
			tirPosition.x = mousePosition.x;
			tirPosition.y = mousePosition.y;


			spriteBalle.move(sf::Vector2f(0.5, 0.1));


			i++;

		}

		if (limiteFPS >= vitesseFPS)
		{
			limiteFPS = 0;
			anim.x++;
			if (anim.x * 32 >= textureMecChelou.getSize().x)
			{
				anim.x = 0;
			}
		}



		spriteMecChelou.setTextureRect(sf::IntRect(anim.x * 32, anim.y * 32, 32, 32));

		window.draw(spriteMecChelou);
		window.draw(spriteViseur);
		window.draw(spriteBalle);
		window.draw(spriteArme);
		window.display();
	}

	return 0;
}