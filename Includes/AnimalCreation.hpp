#ifndef ANIMAL_CREATION_HPP
#define ANIMAL_CREATION_HPP

#include <random>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/Graphics/Sprite.hpp"

#include "Components/IAChoice.hpp"
#include "Components/FSM.hpp"

Gg::Entity generateRandomSpecies(Gg::GulgEngine &engine);

Gg::Entity createGrass(Gg::GulgEngine &engine);
Gg::Entity createWater(Gg::GulgEngine &engine);

void randomPositionForAgents(Gg::GulgEngine &engine, std::vector<Gg::Entity> animals, sf::FloatRect rectangle);

Gg::Entity reproduction(Gg::GulgEngine &engine, const Gg::Entity animal1, const Gg::Entity animal2);

#endif