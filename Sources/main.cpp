#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/AgentDraw.hpp"

#include "AnimalCreation.hpp"


int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{800, 800}, "Sociétés virtuelles", sf::Style::Default, settings};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("Datas/Signatures") && engine.loadTexture("Animal", "Datas/animal.png")) {

		std::vector<Gg::Entity> allAnimals;

		Gg::Entity beginAnimal{generateRandomSpecies(engine)};

		allAnimals.emplace_back(beginAnimal);

		for(unsigned int i{0}; i < 9; i++) {

			allAnimals.emplace_back(engine.cloneEntity(beginAnimal));
		}

		randomPositionForAnimals(engine, allAnimals, sf::FloatRect{100.f, 100.f, 600.f, 600.f});

		AgentDraw drawSystem{window, engine};

		for(Gg::Entity currentEntity: allAnimals) { drawSystem.addEntity(currentEntity); }

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }

			}

			//Update

			

			//Draw

	        window.clear(sf::Color::Black);
	        drawSystem.applyAlgorithms();
	        window.display();
	    }
	}

	return 0;
}