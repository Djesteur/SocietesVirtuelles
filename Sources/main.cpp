#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"



int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{1280, 720}, "Sociétés virtuelles", sf::Style::Default, settings};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("Datas/Signatures")) {


		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

			}

			//Update

			

			//Draw

	        window.clear(sf::Color::Black);
	        window.display();
	    }
	}

	return 0;
}