#include <iostream>
#include <memory>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Systems/Graphics/AgentDraw.hpp"
#include "Systems/AnimalsUpdate.hpp"
#include "Systems/AnimalsIA.hpp"
#include "Systems/Statistics.hpp"

#include "EngineRequest.hpp"
#include "AnimalCreation.hpp"



void startWithWindow(Gg::GulgEngine &engine, std::vector<Gg::Entity> animals, std::vector<Gg::Entity> ressources, 
					 const unsigned int nbUpdatePerSecond, std::string statsFolderPath);

void startWithoutWindow(Gg::GulgEngine &engine, std::vector<Gg::Entity> animals, 
						const unsigned int nbUpdateMax, std::string statsFolderPath);


int main(int argc, char* argv[]) {

	if(argc != 1 && argc !=  3) {

		std::cout << "Invalid number of arguments, add option -n XXXX for the number of update you want without window." << std::endl;
		return -1;
	}

<<<<<<< HEAD
=======
	if(argc == 1) {

		startWithWindow(15, 15, 15, 200);
		system("gnuplot ./Stats/script_gnuplot.txt" );
	}

	else {

		std::string argument{argv[1]};
		if(argument == "-n") {

			std::string nbUpdateMax{argv[2]};
			startWithoutWindow(15, 15, 15, 500, static_cast<unsigned int>(std::stoi(nbUpdateMax)));


		}

		else { 

			std::cout << "Unknown argument \"" << argument  << "\"."<< std::endl; 
			return -1;
		}
	}

	return 0;
}

void startWithWindow(const unsigned int nbAnimal, const unsigned int nbGrass, const unsigned int nbWater, const unsigned int nbUpdatePerSecond) {


	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{800, 800}, "Sociétés virtuelles", sf::Style::Default, settings};

>>>>>>> b90141885fcc588c8a060331afe3494afb9357d0
	Gg::GulgEngine engine;

	const unsigned int nbAnimal{30}, nbGrass{15}, nbWater{15};

	if(engine.loadSignatures("Datas/Signatures") 
	&& engine.loadTexture("Animal", "Datas/Animal.png") 
	&& engine.loadTexture("Grass", "Datas/Grass.png")
	&& engine.loadTexture("Water", "Datas/Water.png")) {

		std::vector<Gg::Entity> allAnimals;

		Gg::Entity beginAnimal{generateRandomSpecies(engine)};

		allAnimals.emplace_back(beginAnimal);

		for(unsigned int i{0}; i < nbAnimal-1; i++) {

			allAnimals.emplace_back(engine.cloneEntity(beginAnimal));
		}

		std::vector<Gg::Entity> ressources;

		Gg::Entity firstGrass{createGrass(engine)};
		ressources.emplace_back(firstGrass);

		for(unsigned int i{0}; i < nbGrass; i++) {

			ressources.emplace_back(engine.cloneEntity(firstGrass));
		}

		Gg::Entity firstWater{createWater(engine)};
		ressources.emplace_back(firstWater);

		for(unsigned int i{0}; i < nbWater; i++) {

			ressources.emplace_back(engine.cloneEntity(firstWater));
		}

		std::vector<Gg::Entity> allAgents;

		allAgents.insert(allAgents.end(), allAnimals.begin(), allAnimals.end());
		allAgents.insert(allAgents.end(), ressources.begin(), ressources.end());

		randomPositionForAgents(engine, allAgents, sf::FloatRect{0.f, 0.f, 800.f, 800.f});

		

		if(argc == 1) {

			startWithWindow(engine, allAnimals, ressources, 200, "Stats/Window");
			//system("gnuplot ./Stats/script_gnuplot.txt" );
		}

		else {

			std::string argument{argv[1]};
			if(argument == "-n") {

				std::string nbUpdateMax{argv[2]};

				Gg::GulgEngine secondEngine{engine};
				std::vector<Gg::Entity> secondAnimals{allAnimals};

				startWithoutWindow(secondEngine, secondAnimals, static_cast<unsigned int>(std::stoi(nbUpdateMax)), "Stats/NoWindow1");

				startWithoutWindow(engine, allAnimals, static_cast<unsigned int>(std::stoi(nbUpdateMax)), "Stats/NoWindow2");


			}

			else { 

				std::cout << "Unknown argument \"" << argument  << "\"."<< std::endl; 
				return -1;
			}
		}
	}

	return 0;
}

void startWithWindow(Gg::GulgEngine &engine, std::vector<Gg::Entity> animals, std::vector<Gg::Entity> ressources,
					 const unsigned int nbUpdatePerSecond, std::string statsFolderPath) {


	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window{sf::VideoMode{800, 800}, "Sociétés virtuelles", sf::Style::Default, settings};

	AgentDraw drawSystem{window, engine};
	AnimalsUpdate animalsStatesUpdates{engine};

	AnimalsIA ia{engine};
	Statistics stats{engine, statsFolderPath};

	for(Gg::Entity currentEntity: animals) { 

		drawSystem.addEntity(currentEntity); 
		animalsStatesUpdates.addEntity(currentEntity);
		ia.addEntity(currentEntity);
		stats.addEntity(currentEntity);
	}

	for(Gg::Entity currentEntity: ressources) { 

		drawSystem.addEntity(currentEntity); 
	}

	std::vector<Gg::Entity> deadAnimals;
	std::vector<std::pair<Gg::Entity, Gg::Entity>> reproduceAnimals;

	const float timeBeetweenUpdate{1'000'000.f/static_cast<float>(nbUpdatePerSecond)};

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
			ia.applyAlgorithms();
			stats.applyAlgorithms();

			reproduceAnimals = ia.getAnimalsToReproduce();

			for(std::pair<Gg::Entity, Gg::Entity> currentPair: reproduceAnimals) {

				Gg::Entity newAnimal = reproduction(engine, currentPair.first, currentPair.second);

				drawSystem.addEntity(newAnimal); 
				animalsStatesUpdates.addEntity(newAnimal);
				ia.addEntity(newAnimal);
				stats.addEntity(newAnimal);
			}

			deadAnimals = animalsStatesUpdates.getEntitiesToKill();

			for(Gg::Entity currentEntity: deadAnimals) { 

				drawSystem.deleteEntity(currentEntity); 
				animalsStatesUpdates.deleteEntity(currentEntity);
				ia.deleteEntity(currentEntity);
				engine.deleteEntity(currentEntity);
				stats.deleteEntity(currentEntity);
			}
		}

			

		//Draw

	    window.clear(sf::Color::Black);
	    drawSystem.applyAlgorithms();
	    window.display();
	}
}

void startWithoutWindow(Gg::GulgEngine &engine, std::vector<Gg::Entity> animals, 
						const unsigned int nbUpdateMax, std::string statsFolderPath) {


	AnimalsUpdate animalsStatesUpdates{engine};

	AnimalsIA ia{engine};

	Statistics stats{engine, statsFolderPath};

	for(Gg::Entity currentEntity: animals) { 

		animalsStatesUpdates.addEntity(currentEntity);
		ia.addEntity(currentEntity);
		stats.addEntity(currentEntity);
	}

	std::vector<Gg::Entity> deadAnimals;
	std::vector<std::pair<Gg::Entity, Gg::Entity>> reproduceAnimals;

	unsigned int nbUpdate{0};

	while(nbUpdate < nbUpdateMax) {

		animalsStatesUpdates.applyAlgorithms();
		ia.applyAlgorithms();
		stats.applyAlgorithms();

		reproduceAnimals = ia.getAnimalsToReproduce();

		for(std::pair<Gg::Entity, Gg::Entity> currentPair: reproduceAnimals) {

			Gg::Entity newAnimal = reproduction(engine, currentPair.first, currentPair.second);

			animalsStatesUpdates.addEntity(newAnimal);
			ia.addEntity(newAnimal);
			stats.addEntity(newAnimal);
		}

		deadAnimals = animalsStatesUpdates.getEntitiesToKill();

		for(Gg::Entity currentEntity: deadAnimals) { 

			animalsStatesUpdates.deleteEntity(currentEntity);
			ia.deleteEntity(currentEntity);
			engine.deleteEntity(currentEntity);
			stats.deleteEntity(currentEntity);
		}

		nbUpdate++;
	}
}