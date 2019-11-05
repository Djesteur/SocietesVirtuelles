#include "Systems/AnimalsUpdate.hpp"

AnimalsUpdate::AnimalsUpdate(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<NeedsUpdates>(gulgEngine));
	m_algorithms.emplace_back(std::make_unique<CheckDeath>(gulgEngine, m_entitiesToKill));
}

AnimalsUpdate::~AnimalsUpdate() {}

void AnimalsUpdate::applyAlgorithms() {

	m_entitiesToKill.clear();

	for(std::unique_ptr<Gg::Algorithm::AbstractAlgorithm> &currentAlgo: m_algorithms) { currentAlgo->apply(); }
}

std::vector<Gg::Entity> AnimalsUpdate::getEntitiesToKill() { return m_entitiesToKill; }