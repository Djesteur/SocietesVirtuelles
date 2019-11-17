#include "Systems/AnimalsIA.hpp"

AnimalsIA::AnimalsIA(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<AnimalsMakeChoices>(gulgEngine));
	m_algorithms.emplace_back(std::make_unique<ApplyChoices>(gulgEngine, m_animalsToReproduce));
}

AnimalsIA::~AnimalsIA() {}

void AnimalsIA::applyAlgorithms() {

	m_animalsToReproduce.clear();

	for(std::unique_ptr<Gg::Algorithm::AbstractAlgorithm> &currentAlgo: m_algorithms) { currentAlgo->apply(); }
}

std::vector<std::pair<Gg::Entity, Gg::Entity>> AnimalsIA::getAnimalsToReproduce() { return m_animalsToReproduce; }