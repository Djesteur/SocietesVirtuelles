#include "Systems/AnimalsIA.hpp"

AnimalsIA::AnimalsIA(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<AnimalsMakeChoices>(gulgEngine));
	m_algorithms.emplace_back(std::make_unique<ApplyChoices>(gulgEngine));
}

AnimalsIA::~AnimalsIA() {}