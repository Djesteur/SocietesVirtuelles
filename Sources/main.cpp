#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/AgentDraw.hpp"

#include "AnimalCreation.hpp"

#include "Systems/AnimalsUpdate.hpp"

#include "Systems/AnimalsIA.hpp"

#include "EngineRequest.hpp"


int main() {

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{800, 800}, "Sociétés virtuelles", sf::Style::Default, settings};

	Gg::GulgEngine engine;

	if(engine.loadSignatures("Datas/Signatures") 
	&& engine.loadTexture("Animal", "Datas/Animal.png") 
	&& engine.loadTexture("Grass", "Datas/Grass.png")
	&& engine.loadTexture("Water", "Datas/Water.png")) {

		std::vector<Gg::Entity> allAnimals;

		Gg::Entity beginAnimal{generateRandomSpecies(engine)};

		allAnimals.emplace_back(beginAnimal);

		for(unsigned int i{0}; i < 14; i++) {

			allAnimals.emplace_back(engine.cloneEntity(beginAnimal));
		}

		std::vector<Gg::Entity> ressources;

		Gg::Entity firstGrass{createGrass(engine)};
		ressources.emplace_back(firstGrass);

		for(unsigned int i{0}; i < 7; i++) {

			ressources.emplace_back(engine.cloneEntity(firstGrass));
		}

		Gg::Entity firstWater{createWater(engine)};
		ressources.emplace_back(firstWater);

		for(unsigned int i{0}; i < 7; i++) {

			ressources.emplace_back(engine.cloneEntity(firstWater));
		}

		std::vector<Gg::Entity> allAgents;

		allAgents.insert(allAgents.end(), allAnimals.begin(), allAnimals.end());
		allAgents.insert(allAgents.end(), ressources.begin(), ressources.end());

		randomPositionForAgents(engine, allAgents, sf::FloatRect{100.f, 100.f, 600.f, 600.f});

		AgentDraw drawSystem{window, engine};
		AnimalsUpdate animalsStatesUpdates{engine};

		AnimalsIA ia{engine};

		for(Gg::Entity currentEntity: allAnimals) { 

			drawSystem.addEntity(currentEntity); 
			animalsStatesUpdates.addEntity(currentEntity);
			ia.addEntity(currentEntity);
		}

		for(Gg::Entity currentEntity: ressources) { 

			drawSystem.addEntity(currentEntity); 
		}

		std::vector<Gg::Entity> deadAnimals;

		const float nbUpdatePerSecond{20.f};
		const float timeBeetweenUpdate{1'000'000.f/nbUpdatePerSecond};

		sf::Time elapsedTime;
		sf::Clock clock;

		while(window.isOpen()) {

			//Event

	        sf::Event event;
	        while(window.pollEvent(event)) {

	            if(event.type == sf::Event::Closed) { window.close(); }
	            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { window.close(); }

			}

			//Update

			elapsedTime += clock.getElapsedTime();
			clock.restart();

			while(elapsedTime > sf::microseconds(timeBeetweenUpdate)) {

				elapsedTime -= sf::microseconds(timeBeetweenUpdate);

				animalsStatesUpdates.applyAlgorithms();
				deadAnimals = animalsStatesUpdates.getEntitiesToKill();

				for(Gg::Entity currentEntity: deadAnimals) { 

					drawSystem.deleteEntity(currentEntity); 
					animalsStatesUpdates.deleteEntity(currentEntity);
					ia.deleteEntity(currentEntity);
					engine.deleteEntity(currentEntity);
				}

				ia.applyAlgorithms();
			}


			//Draw

	        window.clear(sf::Color::Black);
	        drawSystem.applyAlgorithms();
	        window.display();
	    }
	}

	return 0;
}