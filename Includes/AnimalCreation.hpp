#ifndef ANIMAL_CREATION_HPP
#define ANIMAL_CREATION_HPP

#include <random>

#include <SFML/Graphics.hpp>

#include "GulgEngine/GulgEngine.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/Graphics/Sprite.hpp"

Gg::Entity generateRandomSpecies(Gg::GulgEngine &engine);

void randomPositionForAnimals(Gg::GulgEngine &engine, std::vector<Gg::Entity> animals, sf::FloatRect rectangle);

#endif